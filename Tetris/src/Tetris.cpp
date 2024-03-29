﻿#include "Tetris.hpp"

Tetris::Tetris()
    : m_effectFont(20, Typeface::Bold), m_mainFont(25, Typeface::Regular) {
    init();
}

Tetris::~Tetris() {

}

void Tetris::init() {
    m_stage.clear();
    m_bag.clear();
    m_nextMinos.clear();
    m_holdMino.reset();
    m_hasHeld = false;
    m_lockdown.init();
    m_level.init();
    for (int32 i = 0; i < 6; i++) m_nextMinos.push_back(m_bag.get());

    m_tspin = SRS::TSpin::None;
    m_stopwatch.restart();
    m_score = 0;
    m_isB2B = false;
    m_isGameover = false;
    m_combo = -1;
    m_prevDownTime = 0.0s;
    generate();
}

bool Tetris::update(uint8 action) {

    m_stage.update();

    if (m_isGameover) {
        return false;
    }

    int8 rotatedPoint = -1;
    for (uint8 i = 0; i < 8; i++) {
        switch (action & (1 << i)) {
        case Action::MoveLeft:
            if (!m_stage.isHit(m_currentMino.moved(-1, 0))) {
                m_currentMino.move(-1, 0);

                m_tspin = SRS::TSpin::None;

                if (m_stage.isHit(m_currentMino.moved(0, 1))) {
                    m_prevDownTime = m_stopwatch.elapsed();
                }
                m_lockdown++;
            }
            break;
        case Action::MoveRight:
            if (!m_stage.isHit(m_currentMino.moved(1, 0))) {
                m_currentMino.move(1, 0);

                m_tspin = SRS::TSpin::None;

                if (m_stage.isHit(m_currentMino.moved(0, 1))) {
                    m_prevDownTime = m_stopwatch.elapsed();
                }
                m_lockdown++;
            }
            break;
        case Action::SoftDrop:
            if (!m_stage.isHit(m_currentMino.moved(0, 1))) {
                m_currentMino.move(0, 1);
                m_prevDownTime = m_stopwatch.elapsed();

                m_tspin = SRS::TSpin::None;

                m_score++;  // Action: Soft Drop
            }
            break;
        case Action::HardDrop:
            for (int32 y = 0; ; y++) {
                if (m_stage.isHit(m_currentMino.moved(0, y + 1))) {
                    m_currentMino.move(0, y);
                    break;
                }
                m_score += 2; // Action: Hard Drop
            }
            m_prevDownTime = -m_level.interval();
            break;
        case Action::RotateClockwise:
            rotatedPoint = SRS::Rotate(m_stage, m_currentMino, true);

            if (rotatedPoint != -1) {
                m_tspin = SRS::IsTSpined(m_stage, m_currentMino, rotatedPoint);
                m_lockdown++;
            }

            break;
        case Action::RotateCounterclockwise:
            rotatedPoint = SRS::Rotate(m_stage, m_currentMino, false);

            if (rotatedPoint != -1) {
                m_tspin = SRS::IsTSpined(m_stage, m_currentMino, rotatedPoint);
                m_lockdown++;
            }

            break;
        case Action::Hold:
            if (!m_hasHeld) {
                Tetrimino buf = Tetrimino(m_currentMino.type());
                if (!m_holdMino) {
                    m_holdMino = buf;
                }
                else {
                    m_nextMinos.push_front(*m_holdMino);
                    m_holdMino = buf;
                }
                generate();
                m_hasHeld = true;
                m_prevDownTime = m_stopwatch.elapsed();
            }
            break;
        default:
            break;
        }
    }

    if (downMino()) {
        deleteLines();
        generate();
    }

    m_stage.addDrawMino(m_currentMino);
    for (int32 y = 0; ; y++) {
        if (m_stage.isHit(m_currentMino.moved(0, y + 1))) {
            m_stage.addDrawMino(m_currentMino.moved(0, y), 0.3);
            break;
        }
    }

    m_lockdown.update();

    return true;
}

void Tetris::draw() const {

    m_stage.draw(Scene::Width() / 2 - Scene::Height() / 4, 0, Scene::Height() / 2, Scene::Height(), 1.0);

    m_mainFont(U"NEXT").draw(Arg::center = Vec2{ 672.5, 25 });
    Rect{ 600, 50, 145, 535 }.draw(Palette::Black);

    int32 y = 0;
    for (auto nextMino : m_nextMinos) {
        nextMino.draw({ 630 , 50 + 90 * y}, {85, 85});
        y++;
    }

    m_mainFont(U"HOLD").draw(Arg::center = Vec2{ 125.5, 25 });
    Rect{ 53, 50, 145, 90 }.draw(Palette::Black);

    if (m_holdMino) {
        m_holdMino.value().draw({ 83, 50 }, { 85, 85 }, m_hasHeld ? Optional<Color>(Palette::Lightgray) : none);
    }

    m_mainFont(U"SCORE").draw(Arg::center = Vec2{ 125.5, 200 });
    Rect{ 53, 225, 145, 42 }.draw(Palette::Black);
    m_mainFont(U"{}"_fmt(m_score)).draw(Arg::rightCenter = Vec2{ 173, 245 });

    m_mainFont(U"TIME").draw(Arg::center = Vec2{ 125.5, 300 });
    Rect{ 53, 325, 145, 42 }.draw(Palette::Black);
    m_mainFont(m_stopwatch.format(U"mm:ss.xx")).draw(Arg::center = Vec2{ 125.5, 345 });

    m_mainFont(U"LINES:").draw(Arg::leftCenter = Vec2{ 53, 450 });
    m_mainFont(m_level.deletedLineNum()).draw(Arg::leftCenter = Vec2{ 173, 450 });
    m_mainFont(U"LEVEL:").draw(Arg::leftCenter = Vec2{ 53, 490 });
    m_mainFont(m_level).draw(Arg::leftCenter = Vec2{ 173, 490 });

    m_effect.update();
}

void Tetris::addDrawMino(const Tetrimino& mino, const double opacity) {
    m_stage.addDrawMino(mino, opacity);
}

void Tetris::addDrawMino(const Tetrimino& mino, const Color color) {
    m_stage.addDrawMino(mino, color);
}

bool Tetris::downMino() {
    if (m_level >= Level::MAX_SPEED_LEVEL) {
        for (int32 y = 0; ; y++) {
            if (m_stage.isHit(m_currentMino.moved(0, y + 1))) {
                m_currentMino.move(0, y);
                break;
            }
        }
    }

    Duration interval = m_level.interval();
    if (m_stage.isHit(m_currentMino.moved(0, 1))) {
        if (!m_lockdown) {
            m_lockdown.set(m_currentMino.position().y);
        }
        if (m_lockdown) {
            interval = 0.5s;
            if (m_lockdown.changed()) m_prevDownTime = m_stopwatch.elapsed();
            if (m_lockdown.oversteped()) interval = 0.0s;
        }
    }
    
    if (m_lockdown) {
        m_lockdown.updateY(m_currentMino.position().y);
    }

    if (interval + m_prevDownTime <= m_stopwatch) {
        m_prevDownTime = m_stopwatch.elapsed();
        if (!m_stage.isHit(m_currentMino.moved(0, 1))) {
            m_currentMino.move(0, 1);
            m_tspin = SRS::TSpin::None;
        }
        else {
            m_stage.fixMino(m_currentMino);
            m_lockdown.init();
            m_hasHeld = false;
            return true;
        }
    }
    return false;
}

void Tetris::deleteLines() {
    int32 completedLine = m_stage.countCompletedLines();
    String action = U"";
    bool b2bText = false;
    if (completedLine > 0) {
        int32 addition = 0;
        bool b2b = true;
        if (m_tspin == SRS::TSpin::None) {
            if (completedLine != 4) b2b = false;
            switch (completedLine) {
            case 1: addition = 100 * m_level; action = U"Single"; break; // Action: Single
            case 2: addition = 300 * m_level; action = U"Double"; break; // Action: Double
            case 3: addition = 500 * m_level; action = U"Triple"; break; // Action: Triple
            case 4: addition = 800 * m_level; action = U"Tetris"; break; // Action: Tetris
            default: break;
            }
        }
        else if (m_tspin == SRS::TSpin::Mini) {
            addition = 200 * m_level; action = U"Mini T-Spin Single";    // Action: Mini T-Spin Single
        }
        else {
            switch (completedLine) {
            case 1: addition =  800 * m_level; action = U"T-Spin Single"; break; // Action: T-Spin Single
            case 2: addition = 1200 * m_level; action = U"T-Spin Double"; break; // Action: T-Spin Double
            case 3: addition = 1600 * m_level; action = U"T-Spin Triple"; break; // Action: T-Spin Triple
            default: break;
            }
        }

        if (m_isB2B && b2b) {
            addition += addition / 2;                  // Action: Back to Back Bonus
            // action += U"\nBack to Back";
            b2bText = true;

        }
        addition += 50 * (m_combo + 1) * m_level;

        m_score += addition;
        m_isB2B = b2b;

        m_level += m_stage.deleteCompletedLines();

        addition = 0;
        m_combo++;

        if (m_stage.cleared()) {
            switch (completedLine) {
            case 1: addition = 800  * m_level; break; // Action: Single-line Perfect Clear
            case 2: addition = 1200 * m_level; break; // Action: Double-line Perfect Clear
            case 3: addition = 1800 * m_level; break; // Action: Triple-line Perfect Clear
            case 4: addition = 2000 * m_level; break; // Action: Tetris Perfect Clear
            default: break;
            }
            if (completedLine == 4 && m_isB2B) {
                addition = 3200 * m_level;            // Action: Back-to-back Tetris Perfect Clear
            }
        }

    }
    else {
        m_combo = -1;

        if (m_tspin == SRS::TSpin::Mini) {
            m_score += 100 * m_level;                  // Action: Mini T-Spin
            action = U"Mini T-Spin";
        }
        else if (m_tspin == SRS::TSpin::TSpin) {
            m_score += 400 * m_level;                  // Action: T-Spin
            action = U"T-Spin";
        }
    }

    Vec2 pos;
    pos = Vec2{ Scene::Width() / 2, Scene::Height() / Stage::Height * m_currentMino.position().y };
    
    m_effect.add<ActionEffect>(pos, action, m_effectFont);
    if (b2bText) {
        m_effect.add<ActionEffect>(pos.moveBy(0, 25), U"Back to Back", m_effectFont);
    }
    if (m_combo > 0) {
        m_effect.add<ActionEffect>(pos.moveBy(0, 25), U"{} REN"_fmt(m_combo), m_effectFont);
    }
}

void Tetris::generate() {

    m_currentMino = m_nextMinos.front();
    m_nextMinos.pop_front();
    if (m_nextMinos.size() < 6) m_nextMinos.push_back(m_bag.get());

    if (m_stage.isHit(m_currentMino)) {
        // gameover
        m_isGameover = true;
        m_stopwatch.pause();
    }

    for (int32 i = 0; i < 2; i++) {
        if (!m_stage.isHit(m_currentMino.moved(0, 1))) {
            m_currentMino.move(0, 1);
        }
        else break;
    }

    m_lockdown.init();
    m_tspin = SRS::TSpin::None;
}

Array<Tetrimino> Tetris::getAllPlaceable() {
    Array<Tetrimino> ret;

    Tetrimino buf = m_currentMino;
    if (m_level >= Level::MAX_SPEED_LEVEL) {
        for (int32 y = 0; ; y++) {
            if (m_stage.isHit(buf.moved(0, y + 1))) {
                buf.move(0, y);
                break;
            }
        }
    }

    std::deque<Tetrimino> que;
    HashSet<Vector3D<int32>> visited;
    que.push_back(buf);
    visited.insert(buf.asVec3());
    
    while (!que.empty()) {
        Tetrimino q = que.front();
        que.pop_front();

        // Right
        if (!m_stage.isHit(q.moved(1, 0))) {
            if (!visited.contains(q.moved(1, 0).asVec3())) {
                que.push_front(q.moved(1, 0));
                visited.insert(q.moved(1, 0).asVec3());
            }
        }

        // Left
        if (!m_stage.isHit(q.moved(-1, 0))) {
            if (!visited.contains(q.moved(-1, 0).asVec3())) {
                que.push_front(q.moved(-1, 0));
                visited.insert(q.moved(-1, 0).asVec3());
            }
        }
        // Down
        if (!m_stage.isHit(q.moved(0, 1))) {
            if (!visited.contains(q.moved(0, 1).asVec3())) {
                que.push_front(q.moved(0, 1));
                visited.insert(q.moved(0, 1).asVec3());
            }
        }
        else {
            ret << q;
        }
        // Rotate clockwise
        Tetrimino rotatedClockwise = SRS::Rotated(m_stage, q, true);
        if (!visited.contains(rotatedClockwise.asVec3())) {
            que.push_back(rotatedClockwise);
            visited.insert(rotatedClockwise.asVec3());
        }

        // Rotate counterclockwise
        Tetrimino rotatedCounterclockwise = SRS::Rotated(m_stage, q, false);
        if (!visited.contains(rotatedCounterclockwise.asVec3())) {
            que.push_back(rotatedCounterclockwise);
            visited.insert(rotatedCounterclockwise.asVec3());
        }
    }

    return ret;
}

Array<std::pair<Tetrimino, SRS::TSpin>> Tetris::getAllPlaceableWithTSpin() {
    Array<std::pair<Tetrimino, SRS::TSpin>> ret;

    Tetrimino buf = m_currentMino;
    if (m_level >= Level::MAX_SPEED_LEVEL) {
        for (int32 y = 0; ; y++) {
            if (m_stage.isHit(buf.moved(0, y + 1))) {
                buf.move(0, y);
                break;
            }
        }
    }

    std::deque<std::pair<Tetrimino, SRS::TSpin>> que;
    HashSet<Vector3D<int32>> visited;
    que.push_back({ buf, SRS::TSpin::None });
    visited.insert(buf.asVec3());

    while (!que.empty()) {
        auto [q, t] = que.front();
        que.pop_front();

        // Right
        if (!m_stage.isHit(q.moved(1, 0))) {
            if (!visited.contains(q.moved(1, 0).asVec3())) {
                que.push_front({ q.moved(1, 0), SRS::TSpin::None });
                visited.insert(q.moved(1, 0).asVec3());
            }
        }

        // Left
        if (!m_stage.isHit(q.moved(-1, 0))) {
            if (!visited.contains(q.moved(-1, 0).asVec3())) {
                que.push_front({ q.moved(-1, 0), SRS::TSpin::None });
                visited.insert(q.moved(-1, 0).asVec3());
            }
        }
        // Down
        if (!m_stage.isHit(q.moved(0, 1))) {
            if (!visited.contains(q.moved(0, 1).asVec3())) {
                que.push_front({ q.moved(0, 1), SRS::TSpin::None });
                visited.insert(q.moved(0, 1).asVec3());
            }
        }
        else {
            ret << std::pair{ q, t };
        }
        // Rotate clockwise
        Tetrimino rotatedClockwise = q;
        int8 rotatedPointClockwise = SRS::Rotate(m_stage, rotatedClockwise, true);
        if (rotatedPointClockwise != -1 && !visited.contains(rotatedClockwise.asVec3())) {
            que.push_back({ rotatedClockwise, SRS::IsTSpined(m_stage, rotatedClockwise, rotatedPointClockwise) });
            visited.insert(rotatedClockwise.asVec3());
        }

        // Rotate counterclockwise
        Tetrimino rotatedCounterclockwise = q;
        int8 rotatedPointCounterclockwise = SRS::Rotate(m_stage, rotatedCounterclockwise, false);
        if (rotatedPointCounterclockwise != -1 && !visited.contains(rotatedCounterclockwise.asVec3())) {
            que.push_back({ rotatedCounterclockwise, SRS::IsTSpined(m_stage, rotatedCounterclockwise, rotatedPointCounterclockwise) });
            visited.insert(rotatedCounterclockwise.asVec3());
        }
    }

    return ret;
}

bool Tetris::minoMoveTo(uint32 index) {
    auto all = getAllPlaceableWithTSpin();
    if (index >= all.size()) {
        return false;
    }

    m_currentMino = all[index].first;
    m_tspin = all[index].second;

    m_prevDownTime = -m_level.interval();

    if (downMino()) {
        deleteLines();
        generate();
    }

    return true;
}

bool Tetris::holdMino() {
    if (m_hasHeld) return false;

    Tetrimino buf = Tetrimino(m_currentMino.type());
    if (!m_holdMino) {
        m_holdMino = buf;
    }
    else {
        m_nextMinos.push_front(*m_holdMino);
        m_holdMino = buf;
    }
    generate();
    m_hasHeld = true;
    m_prevDownTime = m_stopwatch.elapsed();

    return true;
}
