#include "Tetris.hpp"
#include "SRS.hpp"

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

bool Tetris::update(Action action) {

    m_stage.deleteCompletedLines();

    switch (action) {
    case Action::None:
        break;
    case Action::MoveLeft:
        if (!m_stage.isHit(m_currentMino.moved(-1, 0))) {
            m_currentMino.move(-1, 0);
        }
        break;
    case Action::MoveRight:
        if (!m_stage.isHit(m_currentMino.moved(1, 0))) {
            m_currentMino.move(1, 0);
        }
        break;
    case Action::SoftDrop:
        break;
    case Action::HardDrop:
        break;
    case Action::RotateClockwise:
        break;
    case Action::RotateCounterclockwise:
        break;
    case Action::Hold:
        break;
    default:
        break;
    }

    if (KeyDown.down()) {
        if (!m_stage.isHit(m_currentMino.moved(0, 1))) {
            m_currentMino.move(0, 1);
        }
    }
    if (KeyUp.down()) {
        SRS::Rotate(m_stage, m_currentMino, true);
        // true なら lockDown を加算
        // ここで T-spin か判定
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

    int32 y = 0;
    for (auto nextMino : m_nextMinoes) {
        nextMino.draw({ Scene::Height() / 2 + 70 , 10 + 80 * y}, {70, 70});
        y++;
    }

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
