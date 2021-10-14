#include "Tetris.hpp"

Tetris::Tetris() {
    init();
}

Tetris::~Tetris() {

}

void Tetris::init() {
    m_stage.clear();
    m_bag.clear();
    m_nextMinoes.clear();
    for (int32 i = 0; i < 6; i++) m_nextMinoes.push_back(m_bag.get());

    m_score = 0;
    generate();
}

bool Tetris::update() {

    ClearPrint();
    Print << m_currentMino.position();

    if (KeyDown.down()) {
        if (!m_stage.isHit(m_currentMino.moved(0, 1))) {
            m_currentMino.move(0, 1);
        }
    }
    if (KeyUp.down()) {
        if (!m_stage.isHit(m_currentMino.moved(0, -1))) {
            m_currentMino.move(0, -1);
        }
    }
    if (KeyLeft.down()) {
        if (!m_stage.isHit(m_currentMino.moved(-1, 0))) {
            m_currentMino.move(-1, 0);
        }
    }
    if (KeyRight.down()) {
        if (!m_stage.isHit(m_currentMino.moved(1, 0))) {
            m_currentMino.move(1, 0);
        }
    }

    if (KeySpace.down()) {
        m_stage.fixMino(m_currentMino);
        generate();
    }

    return true;
}

void Tetris::draw() const {

    m_stage.draw(0, 0, Scene::Height() / 2, Scene::Height(), 1.0);

    m_stage.drawMinoOnStage(0, 0, Scene::Height() / 2, Scene::Height(), m_currentMino);

}

void Tetris::generate() {

    m_currentMino = m_nextMinoes.front();
    m_nextMinoes.pop_front();
    m_nextMinoes.push_back(m_bag.get());

    if (m_stage.isHit(m_currentMino)) {
        // gameover
    }

    for (int32 i = 0; i < 2; i++) {
        if (!m_stage.isHit(m_currentMino.moved(0, 1))) {
            m_currentMino.move(0, 1);
        }
        else break;
    }
}
