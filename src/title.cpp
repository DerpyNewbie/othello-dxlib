//
// Created by derpy on 2024/09/15.
//

#include <format>
#include "title.h"
#include "othello_ai.h"
#include "input_manager.h"
#include "DxLib.h"

enum TitleCursor {
    kPlay,
    kExit,
    kBlackPlayer,
    kWhitePlayer,
    kStartPlaying,
    kReturn,
};

void Title::update() {
    if (main_cursor_ <= kExit) {
        if (g_inputs->getKeyDown(KEY_INPUT_W)) {
            main_cursor_ = kPlay;
        }

        if (g_inputs->getKeyDown(KEY_INPUT_S)) {
            main_cursor_ = kExit;
        }
    } else {
        if (g_inputs->getKeyDown(KEY_INPUT_W)) {
            --main_cursor_;
            if (main_cursor_ < kBlackPlayer) main_cursor_ = kBlackPlayer;
        }

        if (g_inputs->getKeyDown(KEY_INPUT_S)) {
            ++main_cursor_;
            if (main_cursor_ > kReturn) main_cursor_ = kReturn;
        }
    }

    if (g_inputs->getKeyDown(KEY_INPUT_SPACE)) {
        switch (main_cursor_) {
            case kPlay:
                main_cursor_ = kBlackPlayer;
                break;
            case kExit:
                has_selected_exit_ = true;
                break;
            case kBlackPlayer:
                is_black_player_cpu_ = !is_black_player_cpu_;
                has_player_state_changed_ = true;
                break;
            case kWhitePlayer:
                is_white_player_cpu_ = !is_white_player_cpu_;
                has_player_state_changed_ = true;
                break;
            case kStartPlaying:
                has_confirmed_game_ = true;
                break;
            case kReturn:
                main_cursor_ = kPlay;
                break;
        }
    }
}

void Title::draw() {
    int starting_index = main_cursor_ <= kExit ? 0 : 2;
    int ending_index = (main_cursor_ <= kExit ? kExit : kReturn) + 1;
    if (has_player_state_changed_) {
        has_player_state_changed_ = false;
        highlightable_texts_[2]->text_ = std::format("{}: {}", text_black_,
                                                     is_black_player_cpu_ ? text_cpu_ : text_human_);
        highlightable_texts_[3]->text_ = std::format("{}: {}", text_white_,
                                                     is_white_player_cpu_ ? text_cpu_ : text_human_);
    }

    for (int i = starting_index; i < ending_index; i++) {
        highlightable_texts_[i]->is_highlighted_ = main_cursor_ == i;
        highlightable_texts_[i]->draw();
    }
}

Othello *Title::getNewGame() {
    Board *board = new Board;
    OthelloPlayer *black = is_black_player_cpu_ ? new OthelloAIPlayer(board, kBlack) : new OthelloPlayer;
    OthelloPlayer *white = is_white_player_cpu_ ? new OthelloAIPlayer(board, kWhite) : new OthelloPlayer;

    main_cursor_ = 0;
    has_confirmed_game_ = false;
    has_selected_exit_ = false;

    return new Othello(board, black, white);
}

bool Title::shouldExit() {
    return has_selected_exit_;
}

bool Title::hasNewGame() {
    return has_confirmed_game_;
}
