//
// Created by derpy on 2024/09/14.
//

#include "othello_ai.h"
#include "DxLib.h"

bool OthelloAIPlayer::hasNextPlacement() {
    if (!has_placeable_cached) {
        placeable_points_ = board_->getPlaceablePoints();
        placement_score_.clear();
        has_placeable_cached = true;
        search_begin_time_ = GetNowCount();
        current_search_path_ = 0;
    }

    for (int i = current_search_path_; i < placeable_points_.size(); i++) {
        if (GetNowCount() - last_searched_time_ > 500) {
            current_search_path_ = i;
            last_searched_time_ = GetNowCount();
            printfDx("Yield returning at %d out of %d\n", i, placeable_points_.size());
            return false;
        }

        printf("%d, %zu\n", i, placeable_points_.size());

        auto point = placeable_points_.at(i);
        placement_score_.emplace(point, board_->getFlippableStones(point->x, point->y, type_).size());
        WaitTimer(100);
    }

    if (GetNowCount() - search_begin_time_ < 1000) {
        return false;
    }

    return true;
}

void OthelloAIPlayer::getNextPlacement(int &x, int &y) {
    printf("placing next\n");

    int max_score = 0;
    Point *max_point;
    for (auto pair: placement_score_) {
        printf("p: %d, (%d, %d)\n", pair.second, pair.first->x, pair.first->y);
        if (max_score < pair.second) {
            max_score = pair.second;
            max_point = pair.first;
        }
    }

    x = max_point->x;
    y = max_point->y;

    has_placeable_cached = false;
}

void OthelloAIPlayer::getCurrentCursor(int &x, int &y) {
    if (!has_placeable_cached) {
        x = 0;
        y = 0;
        return;
    }

    auto p = placeable_points_[current_search_path_];
    x = p->x;
    y = p->y;
}

OthelloAIPlayer::OthelloAIPlayer(Board *board, Stone::StoneType type) {
    board_ = board;
    type_ = type;
}