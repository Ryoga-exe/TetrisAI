#pragma once
#include "Stage.hpp"
#include "Mino.hpp"

// SRS ... Super Rotation System
namespace SRS {

    enum class TSpin {
        None,
        Mini,
        TSpin,
    };

    int8 Rotate(const Stage& stage, Mino& mino, const bool clockwise);
    Mino Rotated(const Stage& stage, const Mino& mino, const bool clockwise);
    TSpin IsTSpined(const Stage& stage, const Mino& mino, const int8 previousRotationPoint);

    constexpr uint32 SRSCheckNum = 5;
    constexpr uint32 TSpinCheckNum = 4;
    constexpr Point SRSMovePos[2][2][Mino::Angles][SRSCheckNum]
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
