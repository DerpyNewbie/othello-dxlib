//
// Created by derpy on 2024/09/14.
//

#ifndef OTHELLO_STONE_H
#define OTHELLO_STONE_H

#include "stone_type.h"

const static int kStoneRadius = 50;
constexpr static unsigned int kStoneColors[3] = {
        0xFF444444, 0xFFFFFFFF, 0xFF000000
};
const static unsigned int kCursorHighlightedColor = 0xFFFFFF00;
const static unsigned int kPlaceableHighlightedColor = 0xFF50AA50;


class Stone {
public:
    StoneType getType() const;

    void setType(StoneType type);

    void draw(int screen_x, int screen_y) const;

    void setCursor(bool cursor);

    void setPlaceable(bool placeable);

    bool canPlace() const;

private:
    StoneType type_ = kEmpty;
    bool has_cursor_ = false;
    bool can_place_ = false;
};


#endif //OTHELLO_STONE_H
