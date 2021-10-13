#pragma once
#include "Common.hpp"
#include "Block.hpp"
#include "Mino.hpp"

class Stage {
public:
    Stage();
    ~Stage();

    void clear();
    void draw(int x, int y, int w, int h, double gridSize = 0) const;
    void draw(Point v, Size s, double gridSize = 0) const;

    bool isHit(const Mino& mino);

    Array<int32> getAsBinaryArray();
    Grid<Blocks> getAsGrid();

private:
    Grid<Blocks> m_stage;

public:
    static constexpr uint32 Width = 10;
    static constexpr uint32 Height = 30;
    static constexpr uint32 SeenHeight = 20;
};
