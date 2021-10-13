#include "Tetris.hpp"

Tetris::Tetris() {
    init();
}

Tetris::~Tetris() {

}

void Tetris::init() {
    m_stage.clear();

}

bool Tetris::update() {
    
    return true;
}

void Tetris::draw() const {

    m_stage.draw(0, 0, Scene::Height() / 2, Scene::Height(), 1.0);

}
