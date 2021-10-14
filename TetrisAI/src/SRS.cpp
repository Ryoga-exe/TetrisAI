#include "SRS.hpp"

namespace SRS {
    bool Rotate(Stage& stage, Mino& mino, bool clockwise) {
        if (mino.type() == 1) return false; // O-mino

        for (uint32 i = 0; i < SRSCheckNum; i++) {
            Mino candidate = mino.rotated(clockwise).moved(SRSMovePos[mino.type() != 0][!clockwise][mino.angle()][i]);

            if (!stage.isHit(candidate)) {
                // return candidate;
                mino = candidate;
                return true;
            }
        }

        return false;
    }
}
