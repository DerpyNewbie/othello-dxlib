//
// Created by derpy on 2024/09/09.
//

#ifndef VAMPIRE_GAME_INPUT_MANAGER_H
#define VAMPIRE_GAME_INPUT_MANAGER_H


class InputManager {

public:
    void updateInputs();

    bool getPreviousFrameKey(int key_code) const;

    bool getKey(int key_code) const;

    bool getKeyDown(int key_code) const;

    bool getKeyUp(int key_code) const;


private:
    static const int kKeyStateBufferSize = 256;

    char prevOnKey[kKeyStateBufferSize];
    char onKey[kKeyStateBufferSize];
    char onkeyUp[kKeyStateBufferSize];
    char onKeyDown[kKeyStateBufferSize];

    int prevMouse;
    int currentMouse;
    int currentMouseUp;
    int currentMouseDown;

};

extern InputManager* g_inputs;
#endif //VAMPIRE_GAME_INPUT_MANAGER_H
