#pragma once
#include <Siv3D.hpp> // OpenSiv3D v0.6.2
#include "Block.hpp"
#include "Tetrimino.hpp"

class Stage {
public:
    Stage();
    ~Stage();
    
    void clear();

    void update();

    void draw(int x, int y, int w, int h, double gridSize = 0) const;
    void draw(Point v, Size s, double gridSize = 0) const;

    void addDrawMino(const Tetrimino& mino, double opacity = 1.0);
    void addDrawMino(const Tetrimino& mino, Color color);

    void fixMino(const Tetrimino& mino);
    bool isHit(const Tetrimino& mino) const;

    uint32 countCompletedLines() const;
    Array<uint32> CompletedLines() const;
    bool cleared() const;
    int32 deleteCompletedLines();
    
    Array<int32> getAsBinaryArray() const;
    Grid<Blocks> getAsGrid() const;

private:
    Grid<Blocks> m_stage;
    Array<int32> m_binaryStage;
    std::list<std::tuple<Tetrimino, double, Optional<Color>>> m_minos;

public:
    static constexpr uint32 Width = 10;
    static constexpr uint32 Height = 30;
    static constexpr uint32 Skyline = 20;
};
