#include "Stage.hpp"

Stage::Stage() : m_stage(Width, Height, Blocks::Air), m_binaryStage(Height, 0) {
    
}


Stage::~Stage() {

}

void Stage::clear() {
    m_stage.fill(Blocks::Air);
    m_binaryStage.fill(0);
}

void Stage::draw(int x, int y, int w, int h, double gridSize) const {
    draw(Point{ x, y }, Size{ w, h }, gridSize);
}
void Stage::draw(Point v, Size s, double gridSize) const {
    const float width = (float)s.x / Width;
    const float height = (float)s.y / Skyline;

    Rect{ v, s }.draw(Palette::Black);

    Line verticalLine{ v, v.x, v.y + s.y};
    Line horizontalLine{ v, v.x + s.x, v.y};

    for (int32 x = 0; x < Width - 1; x++) {
        verticalLine.moveBy(width, 0).draw(gridSize, Palette::Gray);
    }
    for (int32 y = 0; y < Skyline - 1; y++) {
        horizontalLine.moveBy(0, height).draw(gridSize, Palette::Gray);
    }

    for (int32 y = Height - Skyline; y < Height; y++) {
        for (int32 x = 0; x < Width; x++) {
            if (m_stage[y][x] != Blocks::Air) RectF(width * x, height * (y - (Height - Skyline)), width, height).moveBy(v).draw(Mino::GetColor(m_stage[y][x]));
        }
    }
}

void Stage::drawMinoOnStage(int x, int y, int w, int h, const Mino& mino, const double opacity) const {
    drawMinoOnStage(Point{ x, y }, Size{ w, h }, mino, opacity);
}

void Stage::drawMinoOnStage(int x, int y, int w, int h, const Mino& mino, const Color color) const {
    drawMinoOnStage(Point{ x, y }, Size{ w, h }, mino, color);
}

void Stage::drawMinoOnStage(Point v, Size s, const Mino& mino, const double opacity) const {
    const float width = (float)s.x / Width;
    const float height = (float)s.y / Skyline;

    for (int32 y = 0; y < Mino::Size; y++) {
        for (int32 x = 0; x < Mino::Size; x++) {
            Blocks piece = Mino::Shapes[mino.type()][mino.angle()][y][x];
            if (piece != Blocks::Air) {
                auto [mx, my] = mino.position();
                mx += x;
                my += y;
                if ((mx >= 0 && mx < Width) && (my >= 0 && my < Height)) {
                    RectF(width * mx, height * (my - (Height - Skyline)), width, height).moveBy(v).draw(ColorF(Mino::GetColor(piece), opacity));
                }
            }
        }
    }
}

void Stage::drawMinoOnStage(Point v, Size s, const Mino& mino, const Color color) const {
    const float width = (float)s.x / Width;
    const float height = (float)s.y / Skyline;

    for (int32 y = 0; y < Mino::Size; y++) {
        for (int32 x = 0; x < Mino::Size; x++) {
            Blocks piece = Mino::Shapes[mino.type()][mino.angle()][y][x];
            if (piece != Blocks::Air) {
                auto [mx, my] = mino.position();
                mx += x;
                my += y;
                if ((mx >= 0 && mx < Width) && (my >= 0 && my < Height)) {
                    RectF(width * mx, height * (my - (Height - Skyline)), width, height).moveBy(v).draw(color);
                }
            }
        }
    }
}


void Stage::fixMino(const Mino& mino) {
    for (int32 y = 0; y < Mino::Size; y++) {
        for (int32 x = 0; x < Mino::Size; x++) {
            Blocks piece = Mino::Shapes[mino.type()][mino.angle()][y][x];
            if (piece != Blocks::Air) {
                auto [mx, my] = mino.position();
                mx += x;
                my += y;
                if ((mx >= 0 && mx < Width) && (my >= 0 && my < Height)) {
                    m_stage[my][mx] = piece;
                    m_binaryStage[my] |= (1 << mx);
                }
            }
        }
    }
}

bool Stage::isHit(const Mino& mino) const {
    for (int32 y = 0; y < Mino::Size; y++) {
        for (int32 x = 0; x < Mino::Size; x++) {
            if (Mino::Shapes[mino.type()][mino.angle()][y][x] != Blocks::Air) {
                auto [mx, my] = mino.position();
                mx += x;
                my += y;
                if ((mx >= 0 && mx < Width) && (my >= 0 && my < Height)) {
                    if (m_stage[my][mx] != Blocks::Air) return true;
                }
                else return true;
            }
        }
    }
    return false;
}

uint32 Stage::countCompletedLines() const {
    return static_cast<uint32>(m_binaryStage.count((1 << Width) - 1));
}

Array<uint32> Stage::CompletedLines() const {
    Array<uint32> ret;
    for (uint32 i = 0; i < Height; i++) {
        if (m_binaryStage[i] == (1 << Width) - 1) ret << i;
    }
    return ret;
}

bool Stage::cleared() const {
    return m_binaryStage.all([](int32 x) {return x == 0; });
}

int32 Stage::deleteCompletedLines() {
    int32 lineNum = 0;
    int32 nowY = Height - 1;

    // if (countCompletedLines() == 0) return 0;

    for (int32 y = Height - 1; y >= 0; y--) {
        if (m_binaryStage[y] == (1 << Width) - 1) {
            lineNum++;
            continue;
        }

        for (int32 x = 0; x < Width; x++) {
            m_stage[nowY][x] = m_stage[y][x];
            m_binaryStage[nowY] = m_binaryStage[y];
        }
        nowY--;
    }
    return lineNum;
}

Array<int32> Stage::getAsBinaryArray() const {
    return m_binaryStage;
}

Grid<Blocks> Stage::getAsGrid() const {
    return m_stage;
}
