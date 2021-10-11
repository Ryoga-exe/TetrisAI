#pragma once
#include "Stage.hpp"
#include "Block.hpp"

class Tetris {
public:
    Tetris();
    ~Tetris();

    void init();

    bool update();
    void draw() const;
private:
    Stage m_stage;

};
