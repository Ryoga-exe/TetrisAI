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
    m_holdMino.reset();
    m_hasHeld = false;
    for (int32 i = 0; i < 6; i++) m_nextMinos.push_back(m_bag.get());

    m_score = 0;
    generate();
}

bool Tetris::update(uint8 action) {

    m_stage.update();

    bool isFixMino = false;
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
            else {
                // isFixMino = true;
            }
            break;
        case Action::HardDrop:
            for (int32 y = 0; ; y++) {
                if (m_stage.isHit(m_currentMino.moved(0, y+1))) {
                    m_currentMino.move(0, y);
                    break;
                }
            }
            isFixMino = true;
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
            if (!m_hasHeld) {
                Mino buf = Mino(m_currentMino.type());
                if (!m_holdMino) {
                    m_holdMino = buf;
                    generate();
                }
                else {
                    m_nextMinos.push_front(*m_holdMino);
                    m_holdMino = buf;
                    generate();
                }
                m_hasHeld = true;
            }
            break;
        default:
            break;
        }

        if (isFixMino) {
            break;
        }
    }

    if (isFixMino) {
        m_stage.fixMino(m_currentMino);
        m_hasHeld = false;
        generate();
    }

    m_stage.deleteCompletedLines();

    m_stage.addDrawMino(m_currentMino);
    for (int32 y = 0; ; y++) {
        if (m_stage.isHit(m_currentMino.moved(0, y + 1))) {
            m_stage.addDrawMino(m_currentMino.moved(0, y), 0.3);
            break;
        }
    }
    

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
