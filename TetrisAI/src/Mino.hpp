#pragma once
#include "Common.hpp"

class Mino {
public:
    Mino();
    ~Mino();

    bool update();
    void draw() const;

private:
    Point m_pos;
    uint32 m_type;
    uint32 m_angle;
};
