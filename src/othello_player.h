//
// Created by derpy on 2024/09/14.
//

#ifndef OTHELLO_OTHELLO_PLAYER_H
#define OTHELLO_OTHELLO_PLAYER_H

#include "stone.h"

class OthelloPlayer {
private:
    int cursor_x_ = 0, cursor_y_ = 0;

public:
    virtual bool hasNextPlacement();

    virtual void getNextPlacement(int &x, int &y);

    virtual void getCurrentCursor(int &x, int &y);
};


#endif //OTHELLO_OTHELLO_PLAYER_H
