//
// Created by derpy on 2024/09/14.
//

#ifndef OTHELLO_OTHELLO_AI_H
#define OTHELLO_OTHELLO_AI_H

#include <map>
#include "othello_player.h"
#include "board.h"

class OthelloAIPlayer : public OthelloPlayer {
private:

    bool has_placeable_cached = false;
    Board* board_;
    Stone::StoneType type_;
    std::vector<Point*> placeable_points_ = {};
    std::map<Point*, int> placement_score_ = {};
    int current_search_path_ = 0;
    int search_begin_time_ = {};
    int last_searched_time_ = {};

public:
    OthelloAIPlayer(Board* board, Stone::StoneType type);

    bool hasNextPlacement() override;

    void getNextPlacement(int &x, int &y) override;

    void getCurrentCursor(int &x, int &y) override;
};


#endif //OTHELLO_OTHELLO_AI_H
