#pragma once
#include "Stage.hpp"
#include "Block.hpp"
#include "Mino.hpp"
#include "Bag.hpp"
#include "Lockdown.hpp"
#include "Level.hpp"

namespace Action {
    constexpr uint8
        MoveLeft               = 1 << 0,
        MoveRight              = 1 << 1,
        SoftDrop               = 1 << 2,
        HardDrop               = 1 << 3,
        RotateClockwise        = 1 << 4,
        RotateCounterclockwise = 1 << 5,
        Hold                   = 1 << 6;
}

class Tetris {
public:
    Tetris();
    ~Tetris();

    void init();

    bool update(uint8 action = 0);
    void draw() const;
    void addDrawMino(const Mino& mino, const double opacity = 1.0);
    void addDrawMino(const Mino& mino, const Color color);

    Stage& getStage() {
        return m_stage;
    }
    Array<Mino> getAllPlaceable();

private:
    void downMino();
    void generate();

private:
    Stage m_stage;
    Mino m_currentMino;
    Optional<Mino> m_holdMino;
    std::list<Mino> m_nextMinos;

    bool m_hasHeld;
    Bag m_bag;
    Lockdown m_lockdown;
    Level m_level;

    int32 m_score;
    Timer m_timer;
};
