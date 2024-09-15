//
// Created by derpy on 2024/09/14.
//

#include <DxLib.h>
#include "stone.h"
#include "board.h"

Board::Board() {
    for (auto &stone: stones_) {
        stone = new Stone;
    }

    setStoneType(3, 3, StoneType::kBlack);
    setStoneType(4, 3, StoneType::kWhite);
    setStoneType(3, 4, StoneType::kWhite);
    setStoneType(4, 4, StoneType::kBlack);
}

void Board::draw() const {
    int screen_x, screen_y;
    const int stone_radius_doubled = kStoneRadius * 2;
    GetDrawScreenSize(&screen_x, &screen_y);
    int x_offset = (screen_x / 2) - stone_radius_doubled * (kWidth / 2);
    int y_offset = (screen_y / 2) - stone_radius_doubled * (kHeight / 2);

    for (int y = 0; y < kHeight; y++) {
        for (int x = 0; x < kWidth; x++) {
            auto stone = getStone(x, y);
            stone->draw(x * stone_radius_doubled + x_offset, y * stone_radius_doubled + y_offset);
        }
    }
}

Stone *Board::getStone(int x, int y) const {
    return stones_[x + (kWidth * y)];
}

StoneType Board::getStoneType(int x, int y) const {
    return getStone(x, y)->getType();
}

void Board::setStoneType(int x, int y, StoneType type) const {
    getStone(x, y)->setType(type);
}

int Board::updatePlaceableState(StoneType type) {
    int result = 0;
    for (int y = 0; y < kHeight; y++) {
        for (int x = 0; x < kWidth; x++) {
            bool can_place = canPlace(x, y, type);
            getStone(x, y)->setPlaceable(can_place);
            if (can_place) result++;
        }
    }

    return result;
}

bool Board::canPlace(int x, int y, StoneType type) {
    if (getStoneType(x, y) != StoneType::kEmpty) {
        return false;
    }

    return !getFlippableStones(x, y, type).empty();
}

void Board::place(int x, int y, StoneType type) {
    getStone(x, y)->setType(type);

    auto flippable_stones = getFlippableStones(x, y, type);
    for (auto stone: flippable_stones) {
        stone->setType(type);
    }
}

std::vector<Stone *> Board::getFlippableStones(int x, int y, StoneType type) const {
    std::vector<Stone *> result;
    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dy == 0 && dx == 0) continue;
            int cx = x + dx, cy = y + dy;
            bool can_flip = false;
            while (0 <= cx && 0 <= cy && cx < kWidth && cy < kHeight) {
                auto checking_stone = getStoneType(cx, cy);
                if (checking_stone == StoneType::kEmpty) {
                    break;
                }

                if (checking_stone == type) {
                    can_flip = cx != x + dx || cy != y + dy;
                    break;
                }

                cx += dx;
                cy += dy;
            }

            if (!can_flip) continue;

            do {
                cx -= dx;
                cy -= dy;

                result.push_back(getStone(cx, cy));
            } while (cx != x || cy != y);
        }
    }

    return result;
}

void Board::setCursor(int x, int y) {
    getStone(highlighted_x_, highlighted_y_)->setCursor(false);
    getStone(x, y)->setCursor(true);

    highlighted_x_ = x;
    highlighted_y_ = y;
}

void Board::getCursor(int &x, int &y) const {
    x = highlighted_x_;
    y = highlighted_y_;
}

void Board::getScores(int &black, int &white) const {
    black = 0;
    white = 0;
    for (auto stone: stones_) {
        switch (stone->getType()) {
            case StoneType::kBlack:
                black++;
                break;
            case StoneType::kWhite:
                white++;
                break;
            case StoneType::kEmpty:
                break;
        }
    }
}

std::vector<Point *> Board::getPlaceablePoints() const {
    auto result = std::vector<Point *>();
    for (int y = 0; y < kHeight; y++) {
        for (int x = 0; x < kWidth; x++) {
            if (getStone(x, y)->canPlace())
                result.push_back(new Point{x, y});
        }
    }

    return result;
}
