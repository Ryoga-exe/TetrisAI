#include "SRS.hpp"

namespace SRS {
    int8 Rotate(const Stage& stage, Tetrimino& mino, const bool clockwise) {
        if (mino.type() == 1) return false; // O-mino

        for (int32 i = 0; i < SRSCheckNum; i++) {
            Tetrimino candidate = mino.rotated(clockwise).moved(SRSMovePos[mino.type() != 0][!clockwise][mino.angle()][i]);
            if (!stage.isHit(candidate)) {
                mino = candidate;
                return (int8)i;
            }
        }

        return -1;
    }

    Tetrimino Rotated(const Stage& stage, const Tetrimino& mino, const bool clockwise) {
        Tetrimino ret = mino;
        Rotate(stage, ret, clockwise);
        return ret;
    }

    TSpin IsTSpined(const Stage& stage, const Tetrimino& mino, const int8 previousRotationPoint) {
        if (mino.type() != 6) return TSpin::None;

        int8 unhitIndex = -1;
        for (int8 i = 0; i < TSpinCheckNum; i++) {
            auto [x, y] = mino.position() + TSpinCheckPos[i];
            if ((x >= 0 && x < Stage::Width) && (y >= 0 && y < Stage::Height)) {
                if (stage.getAsGrid()[y][x] == Blocks::Air) {
                    if (unhitIndex != -1) return TSpin::None;
                    unhitIndex = i;
                }
            }
        }
        
        if (previousRotationPoint != 4 && (unhitIndex == (int8)mino.angle() || unhitIndex == (int8)(mino.angle() + 1) % 4)) {
            return TSpin::Mini;
        }

        return TSpin::TSpin;
    }

}
