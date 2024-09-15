//
// Created by derpy on 2024/09/14.
//

#include "othello_ai.h"
#include "DxLib.h"

bool OthelloAIPlayer::hasNextPlacement() {
    if (!has_placeable_cached_) {
//        printfDx("caching placeable points\n");
        placeable_points_ = board_->getPlaceablePoints();
        placement_score_.clear();
        has_placeable_cached_ = true;
        search_begin_time_ = GetNowCount();
        current_search_path_ = 0;
        current_highest_point_ = nullptr;
        current_highest_score_ = -1;
    }

    int step = 0;
    for (int i = current_search_path_; i < placeable_points_.size(); i++) {
        auto time_diff = GetNowCount() - last_searched_time_;
        if (time_diff > 1000 || step >= 1) {
            current_search_path_ = i;
            last_searched_time_ = GetNowCount();
//            printfDx("Yield returning at %d out of %d. time diff is %d. current: %d\n", i, placeable_points_.size(),
//                     time_diff, last_searched_time_);
            return false;
        }


        auto point = placeable_points_.at(i);
        int score = board_->getFlippableStones(point->x, point->y, type_).size();
        placement_score_.emplace(point, score);
        if (current_highest_score_ <= score) {
//            printfDx("found better choice: %d, %d for %zu\n", point->x, point->y, score);
            if (current_highest_point_ == nullptr || GetRand(100) < 95) {
                current_highest_point_ = new Point{point->x, point->y};
                current_highest_score_ = score;
//                printfDx("assigned new point: %d, %d\n", point->x, point->y);
            }
            else {
                printfDx("intentionally ignored better choice\n");
            }
        }

        ++step;
        WaitTimer(50);
    }

    if (GetNowCount() - search_begin_time_ < 1000) {
//        printfDx("waiting for ai thinking time...\n");
        WaitTimer(GetNowCount() - search_begin_time_);
        return false;
    }

    return true;
}

void OthelloAIPlayer::getNextPlacement(int &x, int &y) {
    printf("placing next\n");

//    int max_score = 0;
//    Point *max_point;
//    for (auto pair: placement_score_) {
//        printf("p: %d, (%d, %d)\n", pair.second, pair.first->x, pair.first->y);
//        if (max_score < pair.second) {
//            max_score = pair.second;
//            max_point = pair.first;
//        }
//    }

    x = current_highest_point_->x;
    y = current_highest_point_->y;

    printf("decided at %d, %d which has score of %d\n", x, y, current_highest_score_);

    has_placeable_cached_ = false;
    current_highest_point_ = nullptr;
    current_highest_score_ = -1;
}

void OthelloAIPlayer::getCurrentCursor(int &x, int &y) {
    if (current_highest_point_ == nullptr) {
        x = 0;
        y = 0;
        return;
    }

    x = current_highest_point_->x;
    y = current_highest_point_->y;
}

OthelloAIPlayer::OthelloAIPlayer(Board *board, StoneType type) {
    board_ = board;
    type_ = type;
}