#include "SRS.hpp"

namespace SRS {
    bool Rotate(const Stage& stage, Mino& mino, const bool clockwise) {
        if (mino.type() == 1) return false; // O-mino

        for (uint32 i = 0; i < SRSCheckNum; i++) {
            Mino candidate = mino.rotated(clockwise).moved(SRSMovePos[mino.type() != 0][!clockwise][mino.angle()][i]);
            if (!stage.isHit(candidate)) {
                mino = candidate;
                return true;
            }
        }

        return false;
    }

    Mino Rotated(const Stage& stage, const Mino& mino, const bool clockwise) {
        Mino ret = mino;
        Rotate(stage, ret, clockwise);
        return ret;
    }
}
