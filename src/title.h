//
// Created by derpy on 2024/09/15.
//

#ifndef OTHELLO_TITLE_H
#define OTHELLO_TITLE_H


#include "othello.h"
#include "highlightable_text.h"

class Title {
private:
    int main_cursor_ = 0;

    bool is_white_player_cpu_ = false;
    bool is_black_player_cpu_ = false;

    bool has_player_state_changed_ = false;

    bool has_confirmed_game_ = false;
    bool has_selected_exit_ = false;

    std::string text_white_ = "White";
    std::string text_black_ = "Black";
    std::string text_human_ = "Player";
    std::string text_cpu_ = "CPU";

    HighlightableText *highlightable_texts_[6] = {
            new HighlightableText{"Play", 500, 500, 40, 24},
            new HighlightableText{"Exit", 600, 500, 40, 24},
            new HighlightableText{"Black: Player", 500, 500, 40, 24},
            new HighlightableText{"White: Player", 600, 500, 40, 24},
            new HighlightableText{"Start", 700, 500, 40, 24},
            new HighlightableText{"Return", 800, 500, 40, 24},
    };
public:

    void update();

    void draw();

    bool hasNewGame();

    bool shouldExit();

    Othello *getNewGame();

};


#endif //OTHELLO_TITLE_H
