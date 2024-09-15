//
// Created by derpy on 2024/09/14.
//

#ifndef OTHELLO_BOARD_H
#define OTHELLO_BOARD_H

#include <vector>
#include "stone.h"

struct Point {
    int x, y;
};

class Board {
public:
    constexpr static int kWidth = 8;
    constexpr static int kHeight = 8;

private:
    int highlighted_x_ = 0;
    int highlighted_y_ = 0;

    Stone *stones_[kWidth * kHeight] = {};

public:
    Board();

    bool canPlace(int x, int y, Stone::StoneType type);

    void place(int x, int y, Stone::StoneType type);

    std::vector<Stone *> getFlippableStones(int x, int y, Stone::StoneType type) const;

    Stone *getStone(int x, int y) const;

    Stone::StoneType getStoneType(int x, int y) const;

    void setStoneType(int x, int y, Stone::StoneType type) const;

    void setCursor(int x, int y);

    void getCursor(int &x, int &y) const;

    void getScores(int &black, int &white) const;

    int updatePlaceableState(Stone::StoneType type);

    std::vector<Point*> getPlaceablePoints() const;

    void draw() const;

};


#endif //OTHELLO_BOARD_H
