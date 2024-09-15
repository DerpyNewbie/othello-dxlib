//
// Created by derpy on 2024/09/15.
//

#include "highlightable_text.h"

#include <utility>
#include "DxLib.h"

HighlightableText::HighlightableText(std::string text, float x, float y, float w, float h, int font_size) {
    text_ = std::move(text);
    x_ = x;
    y_ = y;
    w_ = w;
    h_ = h;
    font_size_ = font_size;
}

HighlightableText::HighlightableText(std::string text, float y, float w, float h, int font_size) {
    text_ = std::move(text);
    x_ = (1980 / 2) - w * 0.5;
    y_ = y;
    w_ = w;
    h_ = h;
    font_size_ = font_size;
}

void HighlightableText::draw() {
    SetFontSize(font_size_);

    auto half_text_width = GetDrawStringWidth(text_.c_str(), text_.length()) * 0.5F;
    auto half_font_size = font_size_ * 0.5F;

    if (is_highlighted_) {
        DrawBox(x_, y_, x_ + w_, y_ + h_, highlight_color_, true);
    }

    DrawStringF(
            x_ + 10,
            y_ + half_font_size,
            text_.c_str(),
            is_highlighted_ ? highlighted_text_color_ : text_color_
    );
}
