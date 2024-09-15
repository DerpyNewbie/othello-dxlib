//
// Created by derpy on 2024/09/09.
//

#include <DxLib.h>
#include <stdexcept>
#include "input_manager.h"

void InputManager::updateInputs() {
    std::copy(std::begin(onKey), std::end(onKey), std::begin(prevOnKey));

    if (GetHitKeyStateAll(onKey) != 0) {
        throw std::runtime_error("Could not get key state");
    }

    for (int i = 0; i < kKeyStateBufferSize; i++) {
        auto has_diff = prevOnKey[i] != onKey[i];
        onKeyDown[i] = has_diff && onKey[i];
        onkeyUp[i] = has_diff && !onKey[i];
    }
}

bool InputManager::getPreviousFrameKey(int key_code) const {
    return prevOnKey[key_code];
}

bool InputManager::getKey(int key_code) const {
    return onKey[key_code];
}

bool InputManager::getKeyDown(int key_code) const {
    return onKeyDown[key_code];
}

bool InputManager::getKeyUp(int key_code) const {
    return onkeyUp[key_code];
}
