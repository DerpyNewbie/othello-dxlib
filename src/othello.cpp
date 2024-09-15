//
// Created by derpy on 2024/09/14.
//

#include "othello.h"

Othello::Othello(Board* board, OthelloPlayer *black_player, OthelloPlayer *white_player) {
    board_ = board;

    player_black_ = black_player;
    player_white_ = white_player;
    current_player_ = black_player;

    board_->updatePlaceableState(current_type_);
}

void Othello::update() {
    int x, y;
    if (current_player_->hasNextPlacement()) {
        current_player_->getNextPlacement(x, y);
        if (board_->canPlace(x, y, current_type_)) {
            board_->place(x, y, current_type_);
            flipTurn();
            int placeable_spots = board_->updatePlaceableState(current_type_);
            if (placeable_spots <= 0) {
                flipTurn();
                placeable_spots = board_->updatePlaceableState(current_type_);
                if (placeable_spots <= 0) {
                    has_game_ended_ = true;
                }
            }
        }
    }

    current_player_->getCurrentCursor(x, y);
    board_->setCursor(x, y);
}

void Othello::draw() {
    board_->draw();
}

bool Othello::hasGameEnded() {
    return has_game_ended_;
}

void Othello::getScores(int &black, int &white) {
    return board_->getScores(black, white);
}

void Othello::flipTurn() {
    current_type_ = current_type_ == StoneType::kBlack ? StoneType::kWhite : StoneType::kBlack;
    current_player_ = current_type_ == kBlack ? player_black_: player_white_;
}
