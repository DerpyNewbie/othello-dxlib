//
// Created by derpy on 2024/09/14.
//

#include <DxLib.h>
#include "stone.h"

Stone::StoneType Stone::getType() const {
    return type_;
}

void Stone::setType(StoneType type) {
    type_ = type;
}

void Stone::draw(int screen_x, int screen_y) const {
    DrawCircle(screen_x, screen_y, kStoneRadius, kStoneColors[type_]);
    if (can_place_) DrawCircle(screen_x, screen_y, kStoneRadius - 35, kPlaceableHighlightedColor);
    if (has_cursor_) DrawCircle(screen_x, screen_y, kStoneRadius - 25, kCursorHighlightedColor, false, 25);
}

void Stone::setCursor(bool cursor) {
    has_cursor_ = cursor;
}

void Stone::setPlaceable(bool placeable) {
    can_place_ = placeable;
}

bool Stone::canPlace() const {
    return can_place_;
}
