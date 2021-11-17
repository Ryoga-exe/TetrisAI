#include "Tetrimino.hpp"
#include "Stage.hpp"

Tetrimino::Tetrimino()
    : m_type(0), m_angle(0) {
    m_pos = generatePos();
}

Tetrimino::Tetrimino(uint32 type, uint32 angle)
    : m_type(type % Types), m_angle(angle % Angles) {
    m_pos = generatePos();
}

Tetrimino::Tetrimino(uint32 type, uint32 angle, Point pos)
    : m_type(type % Types), m_angle(angle % Angles), m_pos(pos) {
}

Tetrimino::~Tetrimino() {

}

void Tetrimino::draw(const Point v, const ::Size s, const Optional<Color> color) const {
    const float width = (float)s.x / Tetrimino::Size;
    const float height = (float)s.y / Tetrimino::Size;

    for (int32 y = 0; y < Tetrimino::Size; y++) {
        for (int32 x = 0; x < Tetrimino::Size; x++) {
            if (Tetrimino::Shapes[m_type][m_angle][y][x] != Blocks::Air) {
                RectF(width * x, height * y, width, height).moveBy(v).draw(color ? color.value() : GetColor(Tetrimino::Shapes[m_type][m_angle][y][x]));
            }
        }
    }
}


void Tetrimino::move(const int32 x, const int32 y) {
    move(Point{ x, y });
}

void Tetrimino::move(const Point diff) {
    m_pos += diff;
}

Tetrimino Tetrimino::moved(const int32 x, const int32 y) const {
    return moved(Point{ x, y });
}

Tetrimino Tetrimino::moved(const Point diff) const {
    return Tetrimino(m_type, m_angle, m_pos + diff);
}

void Tetrimino::moveTo(const int32 x, const int32 y) {
    moveTo(Point{ x, y });
}

void Tetrimino::moveTo(const Point to) {
    m_pos = to;
}

Tetrimino Tetrimino::movedTo(const int32 x, const int32 y) const {
    return movedTo(Point{ x, y });
}

Tetrimino Tetrimino::movedTo(const Point to) const {
    return Tetrimino(m_type, m_angle, to);
}

void Tetrimino::rotate(bool clockwise) {
    m_angle = clockwise ? (m_angle + 1) % Angles : (m_angle + Angles - 1) % Angles;
}

Tetrimino Tetrimino::rotated(bool clockwise) const {
    uint32 ret = clockwise ? (m_angle + 1) % Angles : (m_angle + Angles - 1) % Angles;
    return Tetrimino(m_type, ret, m_pos);
}

Point Tetrimino::position() const {
    return m_pos;
}

uint32 Tetrimino::type() const {
    return m_type;
}

uint32 Tetrimino::angle() const {
    return m_angle;
}

Tetrimino Tetrimino::operator =(const Tetrimino& mino) {
    this->m_pos = mino.m_pos;
    this->m_type = mino.m_type;
    this->m_angle = mino.m_angle;
    return *this;
}

Point Tetrimino::generatePos() {
    Point ret;
    ret.x = (Stage::Width - Tetrimino::Size) / 2;
    ret.y = Stage::Height - Stage::Skyline;
    if (m_type == 0) ret.y -= 2;
    else ret.y -= 3;
    return ret;
}
