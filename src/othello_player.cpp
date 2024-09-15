//
// Created by derpy on 2024/09/14.
//

#include "DxLib.h"
#include "othello_player.h"
#include "input_manager.h"
#include "board.h"

bool OthelloPlayer::hasNextPlacement() {
    int vx = 0, vy = 0;
    if (g_inputs->getKeyDown(KEY_INPUT_W)) {
        --vy;
    }
    if (g_inputs->getKeyDown(KEY_INPUT_S)) {
        ++vy;
    }
    if (g_inputs->getKeyDown(KEY_INPUT_A)) {
        --vx;
    }
    if (g_inputs->getKeyDown(KEY_INPUT_D)) {
        ++vx;
    }

    cursor_x_ += vx;
    cursor_y_ += vy;

    if (cursor_x_ < 0) cursor_x_ = Board::kWidth - 1;
    if (cursor_y_ < 0) cursor_y_ = Board::kHeight - 1;

    if (cursor_x_ >= Board::kWidth) cursor_x_ = 0;
    if (cursor_y_ >= Board::kHeight) cursor_y_ = 0;

    return g_inputs->getKeyDown(KEY_INPUT_SPACE);
}

void OthelloPlayer::getNextPlacement(int &x, int &y) {
    x = cursor_x_;
    y = cursor_y_;
}

void OthelloPlayer::getCurrentCursor(int &x, int &y) {
    x = cursor_x_;
    y = cursor_y_;
}
