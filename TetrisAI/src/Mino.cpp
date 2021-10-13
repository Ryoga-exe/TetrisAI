#include "Mino.hpp"
#include "Stage.hpp"

Mino::Mino()
    : m_type(0), m_angle(0) {
    m_pos = generatePos();
}

Mino::Mino(uint32 type, uint32 angle)
    : m_type(type % Types), m_angle(angle % Angles) {
    m_pos = generatePos();
}

Mino::Mino(uint32 type, uint32 angle, Point pos)
    : m_type(type % Types), m_angle(angle % Angles), m_pos(pos) {
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

Mino Mino::operator =(const Mino& mino) {
    this->m_pos = mino.m_pos;
    this->m_type = mino.m_type;
    this->m_angle = mino.m_angle;
    return *this;
}

Point Mino::generatePos() {
    Point ret;
    ret.x = (Stage::Width - Mino::Size) / 2;
    ret.y = Stage::Height - Stage::Skyline;
    if (m_type == 0) ret.y -= 2;
    else ret.y -= 3;
    return ret;
}
