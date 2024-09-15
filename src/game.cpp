//
// Created by derpy on 2024/09/14.
//

#include "input_manager.h"
#include "DxLib.h"
#include "game.h"
#include "othello_ai.h"

Game::Game() {
    current_state_ = kTitle;
    othello_ = nullptr;
}

void Game::update() {
    switch (current_state_) {
        case kTitle: {
            if (g_inputs->getKeyDown(KEY_INPUT_SPACE)) {
                delete othello_;
                auto board = new Board();
                othello_ = new Othello(board, new OthelloPlayer(), new OthelloAIPlayer(board, Stone::kWhite));
                current_state_ = kInGame;
            }

            break;
        }
        case kInGame: {
            othello_->update();
            if (othello_->hasGameEnded()) current_state_ = kResult;
            break;
        }
        case kResult: {
            if (g_inputs->getKeyDown(KEY_INPUT_SPACE)) {
                delete othello_;
                othello_ = nullptr;
                current_state_ = kTitle;
            }
            break;
        }
    }
}

void Game::draw() {
    switch (current_state_) {
        case kTitle: {
            DrawString(100, 100, "ぷれす すぺーす とぅ すたーと", 0xFFFFFFFF);
            break;
        }
        case kInGame: {
            othello_->draw();
            break;
        }
        case kResult: {
            othello_->draw();
            DrawString(100, 100, "げーむず えんど ぷれす すぺーす とぅ こんちにゅー", 0xFFFFFFFF);
            break;
        }
    }
}
