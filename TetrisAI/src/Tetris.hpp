﻿#pragma once
#include "Stage.hpp"
#include "Block.hpp"
#include "Mino.hpp"
#include "Bag.hpp"
#include "SRS.hpp"
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

struct ActionEffect : IEffect {
    Vec2 m_start;
    String m_action;
    Font m_font;

    ActionEffect(const Vec2& start, String action, const Font& font)
        : m_start{ start }, m_action{ action }, m_font{ font } {}

    bool update(double t) override {
        const double e = EaseOutExpo(t);

        m_font(m_action).drawAt(m_start.movedBy(0, -40 * e).movedBy(4, 4), ColorF(0.0, 0.5 * (1.0 - t)));
        m_font(m_action).drawAt(m_start.movedBy(0, -40 * e), ColorF(Palette::Whitesmoke, 1.0 - Max(0.0, 2.0 * t - 1.0)));

        return (t < 1.0);
    }
};

class Tetris {
public:
    Tetris();
    ~Tetris();

    void init();

    bool update(uint8 action = 0);
    void draw() const;
    void addDrawMino(const Mino& mino, const double opacity = 1.0);
    void addDrawMino(const Mino& mino, const Color color);

    bool gameover() const {
        return m_isGameover;
    }

    Stage& getStage() {
        return m_stage;
    }
    Array<Mino> getAllPlaceable();

private:
    bool downMino();
    void deleteLines();
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
    SRS::TSpin m_tspin;

    int32 m_score;
    bool m_isB2B;
    bool m_isGameover;
    int32 m_combo;
    Duration m_prevDownTime;
    Stopwatch m_stopwatch;
    Effect m_effect;
    Font m_effectFont;
};
