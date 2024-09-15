//
// Created by derpy on 2024/09/15.
//

#ifndef OTHELLO_HIGHLIGHTABLE_TEXT_H
#define OTHELLO_HIGHLIGHTABLE_TEXT_H


#include <string>

class HighlightableText {
public:
    HighlightableText(std::string text, float x, float y, float w, float h, int font_size);
    HighlightableText(std::string text, float y, float w, float h, int font_size);

    std::string text_;
    bool is_highlighted_;
    float x_, y_, w_, h_;
    int font_size_;
    unsigned int text_color_ = 0xFFFFFFFF, highlight_color_ = 0xFFFFFF00, highlighted_text_color_ = 0xFF000000;

    void draw();
};


#endif //OTHELLO_HIGHLIGHTABLE_TEXT_H
