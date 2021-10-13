#include "Mino.hpp"

Mino::Mino(uint32 type, uint32 angle, Point pos)
    : m_type(type), m_angle(angle % Angles), m_pos(pos) {
    if (type >= Types) m_type = 0;
}

Mino::~Mino() {

}

void Mino::move(const int32 x, const int32 y) {
    move(Point{ x, y });
}

void Mino::move(const Point diff) {
    m_pos += diff;
}

void Mino::moveTo(const int32 x, const int32 y) {
    moveTo(Point{ x, y });
}

void Mino::moveTo(const Point to) {
    m_pos = to;
}

Mino Mino::moved(const int32 x, const int32 y) const {
    return moved(Point{ x, y });
}

Mino Mino::moved(const Point diff) const {
    return Mino(m_type, m_angle, m_pos + diff);
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
