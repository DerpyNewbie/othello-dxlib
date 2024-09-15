//
// Created by derpy on 2024/08/26.
//

#pragma comment(linker, "/subsystem:windows")

#include "DxLib.h"
#include "board.h"
#include "input_manager.h"
#include "game.h"

InputManager *g_inputs;

int WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
    ChangeWindowMode(TRUE); // Windowed/Fullscreenの設定、Windowedにする
    if (DxLib_Init() != 0) { //DxLibの初期化
        return -1;
    }
    SetDrawScreen(DX_SCREEN_BACK); //裏画面に描画する
    SetGraphMode(1920, 1080, 32); //画面の大きさ
    SetBackgroundColor(100, 100, 100);
    SetAlwaysRunFlag(TRUE);

    g_inputs = new InputManager();
    auto game = new Game();
    while (ProcessMessage() == 0 && !game->isExiting()) {
        g_inputs->updateInputs();
        game->update();
        ClearDrawScreen();
        game->draw();
        ScreenFlip();
    }

    DxLib_End();

    return 0;
}