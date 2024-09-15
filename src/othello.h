//
// Created by derpy on 2024/09/14.
//

#ifndef OTHELLO_OTHELLO_H
#define OTHELLO_OTHELLO_H


#include "stone.h"
#include "board.h"
#include "othello_player.h"

class Othello {
private:
    Board *board_ = new Board();
    Stone::StoneType current_type_ = Stone::StoneType::kBlack;
    OthelloPlayer* player_black_;
    OthelloPlayer* player_white_;
    OthelloPlayer* current_player_;

    bool has_game_ended_ = false;

    void flipTurn();

public:

    Othello(Board* board, OthelloPlayer* black_player_, OthelloPlayer* white_player_);

    void update();

    void draw();

    bool hasGameEnded();

    void getScores(int &black, int &white);
};


#endif //OTHELLO_OTHELLO_H
