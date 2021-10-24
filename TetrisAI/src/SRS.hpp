#pragma once
#include "Stage.hpp"
#include "Mino.hpp"

// SRS ... Super Rotation System
namespace SRS {

    bool Rotate(const Stage& stage, Mino& mino, const bool clockwise);
    Mino Rotated(const Stage& stage, const Mino& mino, const bool clockwise);

    constexpr uint32 SRSCheckNum = 5;
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
}
