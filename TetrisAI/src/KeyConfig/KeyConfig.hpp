#pragma once
#include "Common.hpp"
#include "Tetris.hpp"

class KeyConfig {
public:
    KeyConfig();
    ~KeyConfig();

    void update();
    operator uint8();

private:
    uint8 m_state;
    // Array<Array<InputGroup>> m_key;
};
