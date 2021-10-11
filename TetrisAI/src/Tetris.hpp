#pragma once
#include "Stage.hpp"

class Tetris {
public:
    Tetris();
    ~Tetris();

    void draw() const;
private:
    Stage m_stage;
};
