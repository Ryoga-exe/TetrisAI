﻿#pragma once
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

    void drawMinoOnStage(int x, int y, int w, int h, const Mino& mino, const double opacity = 1.0) const;
    void drawMinoOnStage(int x, int y, int w, int h, const Mino& mino, const Color color) const;
    void drawMinoOnStage(Point v, Size s, const Mino& mino, const double opacity = 1.0) const;
    void drawMinoOnStage(Point v, Size s, const Mino& mino, const Color color) const;
    void fixMino(const Mino& mino);
    bool isHit(const Mino& mino) const;

    uint32 countCompletedLines() const;
    Array<uint32> CompletedLines() const;
    bool cleared() const;
    int32 deleteCompletedLines();
    
    Array<int32> getAsBinaryArray() const;
    Grid<Blocks> getAsGrid() const;

private:
    Grid<Blocks> m_stage;
    Array<int32> m_binaryStage;

public:
    static constexpr uint32 Width = 10;
    static constexpr uint32 Height = 30;
    static constexpr uint32 Skyline = 20;
};
