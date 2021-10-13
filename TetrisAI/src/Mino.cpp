#include "Mino.hpp"

Mino::Mino(uint32 type, uint32 angle, Point pos)
    : m_type(type), m_angle(angle % Angles), m_pos(pos) {
    if (type >= Types) m_type = 0;
}

Mino::~Mino() {

}

bool Mino::update() {
    return true;
}

void Mino::draw() const {

}

Point Mino::position() const {
    return m_pos;
}

uint32 Mino::type() const {
    return m_type;
}

uint32 Mino::angle() const {
    return m_angle;
}
