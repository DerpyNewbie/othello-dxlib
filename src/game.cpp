//
// Created by derpy on 2024/09/14.
//

#include "input_manager.h"
#include "DxLib.h"
#include "game.h"
#include "othello_ai.h"

Game::Game() {
    current_state_ = kTitle;
    title_ = new Title();
    othello_ = nullptr;
}

void Game::update() {
    if (g_inputs->getKeyDown(KEY_INPUT_ESCAPE)) {
        current_state_ = kExiting;
        return;
    }

    switch (current_state_) {
        case kTitle: {
            title_->update();
            if (title_->hasNewGame()) {
                othello_ = title_->getNewGame();
                current_state_ = kInGame;
            }

            if (title_->shouldExit()) {
                current_state_ = kExiting;
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

void Game::draw() const {
    switch (current_state_) {
        case kTitle: {
//            DrawString(100, 100, "ぷれす すぺーす とぅ すたーと", 0xFFFFFFFF);

            title_->draw();
            break;
        }
        case kInGame: {
            othello_->draw();
            break;
        }
        case kResult: {
            othello_->draw();
            int black, white;
            othello_->getScores(black, white);
            DrawString(100, 100, "げーむず えんど ぷれす すぺーす とぅ こんちにゅー", 0xFFFFFFFF);
            DrawFormatString(100, 200, 0xFFFFFFFF, "くろ: %d, しろ: %d", black, white);
            break;
        }
    }
}

bool Game::isExiting() const {
    return current_state_ == kExiting;
}
