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
    m_nextMinos.clear();
    for (int32 i = 0; i < 6; i++) m_nextMinos.push_back(m_bag.get());

    m_score = 0;
    generate();
}

bool Tetris::update(uint8 action) {

    m_stage.deleteCompletedLines();

    for (uint8 i = 0; i < 8; i++) {
        switch (action & (1 << i)) {
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
            if (!m_stage.isHit(m_currentMino.moved(0, 1))) {
                m_currentMino.move(0, 1);
            }
            break;
        case Action::HardDrop:
            break;
        case Action::RotateClockwise:
            SRS::Rotate(m_stage, m_currentMino, true);
            // true なら lockDown を加算
            // ここで T-spin か判定
            break;
        case Action::RotateCounterclockwise:
            SRS::Rotate(m_stage, m_currentMino, false);
            // true なら lockDown を加算
            // ここで T-spin か判定
            break;
        case Action::Hold:
            break;
        default:
            break;
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

    int32 y = 0;
    for (auto nextMino : m_nextMinos) {
        nextMino.draw({ Scene::Height() / 2 + 70 , 10 + 80 * y}, {70, 70});
        y++;
    }

}

void Tetris::generate() {

    m_currentMino = m_nextMinos.front();
    m_nextMinos.pop_front();
    m_nextMinos.push_back(m_bag.get());

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
