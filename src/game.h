//
// Created by derpy on 2024/09/14.
//

#ifndef OTHELLO_GAME_H
#define OTHELLO_GAME_H

#include "othello.h"

class Game {
    enum GameState {
        kTitle,
        kInGame,
        kResult
    };

    GameState current_state_;
    Othello *othello_;

public:
    Game();

    void update();

    void draw();
};


#endif //OTHELLO_GAME_H
