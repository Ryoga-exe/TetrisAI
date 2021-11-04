#pragma once
#include "Mino/Tetrimino.hpp"
#include "Stage/Stage.hpp"

// SRS ... Super Rotation System
namespace SRS {

    enum class TSpin {
        None,
        Mini,
        TSpin,
    };

    int8 Rotate(const Stage& stage, Tetrimino& mino, const bool clockwise);
    Tetrimino Rotated(const Stage& stage, const Tetrimino& mino, const bool clockwise);
    TSpin IsTSpined(const Stage& stage, const Tetrimino& mino, const int8 previousRotationPoint);

    constexpr uint32 SRSCheckNum = 5;
    constexpr uint32 TSpinCheckNum = 4;
    constexpr Point SRSMovePos[2][2][Tetrimino::Angles][SRSCheckNum]
    {
        {   // I
            {   // Clockwise
                { {0, 0}, {-2, 0}, { 1, 0}, {-2, 1}, { 1,-2} }, // 0
                { {0, 0}, {-1, 0}, { 2, 0}, {-1,-2}, { 2, 1} }, // 1
                { {0, 0}, { 2, 0}, {-1, 0}, { 2,-1}, {-1, 2} }, // 2
                { {0, 0}, {-2, 0}, { 1, 0}, { 1, 2}, {-2, 1} }  // 3
            },{ // Counterclockwise
                { {0, 0}, {-1, 0}, { 2, 0}, {-1,-2}, { 2, 1} }, // 0
                { {0, 0}, { 2, 0}, {-1, 0}, { 2,-1}, {-1, 2} }, // 1
                { {0, 0}, { 1, 0}, {-2, 0}, { 1, 2}, {-2,-1} }, // 2
                { {0, 0}, { 1, 0}, {-2, 0}, {-2, 1}, { 1,-2} }  // 3
            }
        },{ // T, S, Z, L, J
            {   // Clockwise
                { {0, 0}, {-1, 0}, {-1,-1}, { 0, 2}, {-1, 2} }, // 0
                { {0, 0}, { 1, 0}, { 1, 1}, { 0,-2}, { 1,-2} }, // 1
                { {0, 0}, { 1, 0}, { 1,-1}, { 0, 2}, { 1, 2} }, // 2
                { {0, 0}, {-1, 0}, {-1, 1}, { 0,-2}, {-1,-2} }  // 3
            },{ // Counterclockwise
                { {0, 0}, { 1, 0}, { 1,-1}, { 0, 2}, { 1, 2} }, // 0
                { {0, 0}, { 1, 0}, { 1, 1}, { 0,-2}, { 1,-2} }, // 1
                { {0, 0}, {-1, 0}, {-1,-1}, { 0, 2}, {-1, 2} }, // 2
                { {0, 0}, {-1, 0}, {-1, 1}, { 0,-2}, {-1,-2} }  // 3
            }
        }
    };
    constexpr Point TSpinCheckPos[TSpinCheckNum] = {
        {0, 1}, {2, 1}, {2, 3}, {0, 3}
    };
}
