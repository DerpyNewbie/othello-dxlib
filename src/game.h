//
// Created by derpy on 2024/09/14.
//

#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H

#include "othello.h"
#include "title.h"

class Game {
    enum GameState {
        kTitle,
        kInGame,
        kResult,
        kExiting
    };

    GameState current_state_;
    Title *title_;
    Othello *othello_;

public:
    Game();

    void update();

    void draw() const;

    bool isExiting() const;
};


#endif //OTHELLO_GAME_H
