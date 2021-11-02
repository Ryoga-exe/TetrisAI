﻿#include "Tetris.hpp"
#include "SRS.hpp"

Tetris::Tetris() {
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

    m_stopwatch.restart();
    m_score = 0;
    m_prevDownTime = 0.0s;
    generate();
}

bool Tetris::update(uint8 action) {

    ClearPrint();
    Print << m_level.deletedLineNum();
    Print << m_level.level();
    Print << m_level.interval();


    m_stage.update();

    int8 rotatedPoint = -1;
    for (uint8 i = 0; i < 8; i++) {
        switch (action & (1 << i)) {
        case Action::MoveLeft:
            if (!m_stage.isHit(m_currentMino.moved(-1, 0))) {
                m_currentMino.move(-1, 0);
            }
            m_lockdown++;
            break;
        case Action::MoveRight:
            if (!m_stage.isHit(m_currentMino.moved(1, 0))) {
                m_currentMino.move(1, 0);
            }
            m_lockdown++;
            break;
        case Action::SoftDrop:
            if (!m_stage.isHit(m_currentMino.moved(0, 1))) {
                m_currentMino.move(0, 1);
            }
            break;
        case Action::HardDrop:
            for (int32 y = 0; ; y++) {
                if (m_stage.isHit(m_currentMino.moved(0, y+1))) {
                    m_currentMino.move(0, y);
                    break;
                }
            }
            m_prevDownTime = -m_level.interval();
            break;
        case Action::RotateClockwise:
            rotatedPoint = SRS::Rotate(m_stage, m_currentMino, true);

            if (rotatedPoint != -1) {
                SRS::IsTSpined(m_stage, m_currentMino, rotatedPoint);
                m_lockdown++;
            }

            break;
        case Action::RotateCounterclockwise:
            rotatedPoint = SRS::Rotate(m_stage, m_currentMino, false);
            
            if (rotatedPoint != -1) {
                SRS::IsTSpined(m_stage, m_currentMino, rotatedPoint);
                m_lockdown++;
            }

            break;
        case Action::Hold:
            if (!m_hasHeld) {
                Mino buf = Mino(m_currentMino.type());
                if (!m_holdMino) {
                    m_holdMino = buf;
                }
                else {
                    m_nextMinos.push_front(*m_holdMino);
                    m_holdMino = buf;
                }
                generate();
                m_hasHeld = true;
            }
            break;
        default:
            break;
        }
    }

    if (downMino()) {
        m_stage.fixMino(m_currentMino);
        m_hasHeld = false;
        generate();
    }

    m_level += m_stage.deleteCompletedLines();

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

    m_stage.draw(100, 0, Scene::Height() / 2, Scene::Height(), 1.0);

    int32 y = 0;
    for (auto nextMino : m_nextMinos) {
        nextMino.draw({ 100 + Scene::Height() / 2 + 70 , 10 + 80 * y}, {70, 70});
        y++;
    }

    if (m_holdMino) m_holdMino.value().draw({ 20, 20 }, { 70, 70 });
}

void Tetris::addDrawMino(const Mino& mino, const double opacity) {
    m_stage.addDrawMino(mino, opacity);
}

void Tetris::addDrawMino(const Mino& mino, const Color color) {
    m_stage.addDrawMino(mino, color);
}

bool Tetris::downMino() {
    if (m_level > 19) {
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

    /*
    if (speedWaitMs + m_prevMinoDownTime <= (signed)m_gameTimer.Elapse()) {
        m_prevMinoDownTime = m_gameTimer.Elapse();
        if (!IsHit({ m_currentMinoPos.X, m_currentMinoPos.Y + 1 }, m_currentMino)) {
            m_currentMinoPos.Y++; m_tSpinAct = NOTSPIN;
        }
        else {
            FixMino();
            m_isPerfect = false;
            if (!DeleteLine()) {
                if (m_tSpinAct != NOTSPIN) {
                    m_isBack2Back = false;
                    int addtion = (m_tSpinAct == SPIN ? 400 : 100) * m_currentLevel;
                    if (m_actionNotification == TETRIS || (m_actionNotification >= T_SPIN && m_actionNotification <= T_SPIN_TRIPLE)) {
                        m_isBack2Back = true;
                        addtion += (int)addtion / 2;
                    }
                    m_actionNotification = (Actions)(T_SPIN + m_tSpinAct - 1);
                    m_timeActionNotification = m_gameTimer.Elapse();
                    m_score += addtion;
                }
                m_combo = -1;
                MinoUpdate();
                if (InitMinoPos()) {
                    // GameOver
                    return true;
                }
            }
            m_lockDown.Init();
            m_hasHeld = false;
        }
    }
    */

    return false;
}

void Tetris::generate() {

    m_currentMino = m_nextMinos.front();
    m_nextMinos.pop_front();
    if (m_nextMinos.size() < 6) m_nextMinos.push_back(m_bag.get());

    if (m_stage.isHit(m_currentMino)) {
        // gameover
    }

    for (int32 i = 0; i < 2; i++) {
        if (!m_stage.isHit(m_currentMino.moved(0, 1))) {
            m_currentMino.move(0, 1);
        }
        else break;
    }

    m_lockdown.init();
}

Array<Mino> Tetris::getAllPlaceable() {
    Array<Mino> ret;

    std::deque<Mino> que;
    HashSet<Vector3D<int32>> visited;
    que.push_back(m_currentMino);
    visited.insert(m_currentMino.asVec3());
    
    while (!que.empty()) {
        Mino q = que.front();
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
        Mino rotatedClockwise = SRS::Rotated(m_stage, q, true);
        if (!visited.contains(rotatedClockwise.asVec3())) {
            que.push_back(rotatedClockwise);
            visited.insert(rotatedClockwise.asVec3());
        }

        // Rotate counterclockwise
        Mino rotatedCounterclockwise = SRS::Rotated(m_stage, q, false);
        if (!visited.contains(rotatedCounterclockwise.asVec3())) {
            que.push_back(rotatedCounterclockwise);
            visited.insert(rotatedCounterclockwise.asVec3());
        }
    }

    return ret;
}
