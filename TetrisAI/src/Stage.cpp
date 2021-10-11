#include "Stage.hpp"

Stage::Stage() : m_stage(Width, Height, Blocks::Air){
    
}


Stage::~Stage() {

}

void Stage::clear() {
    m_stage.fill(Blocks::Air);
}

void Stage::draw(int x, int y, int w, int h, double gridSize) const {
    draw(Point{ x, y }, Size{ w, h }, gridSize);
}
void Stage::draw(Point v, Size s, double gridSize) const {
    const float width = (float)s.x / Width;
    const float height = (float)s.y / SeenHeight;

    Rect{ v, s }.draw(Palette::Black);

    Line verticalLine{ v, 0, s.y};
    Line horizontalLine{ v, s.x, 0 };

    for (int32 x = 0; x < Width - 1; x++) {
        verticalLine.moveBy(width, 0).draw(gridSize, Palette::Gray);
    }
    for (int32 y = 0; y < SeenHeight - 1; y++) {
        horizontalLine.moveBy(0, height).draw(gridSize, Palette::Gray);
    }

    for (int32 y = Height - SeenHeight; y < Height; y++) {
        for (int32 x = 0; x < Width; x++) {
            if (m_stage[y][x] != Blocks::Air) RectF(width * x, height * (y - (Height - SeenHeight)), width, height).moveBy(v).draw(Mino::GetColor(m_stage[y][x]));
        }
    }
}

Array<int32> Stage::getAsBinaryArray() {
    Array<int32> ret(Height);
    for (int32 y = 0; y < Height; y++) {
        for (int32 x = 0; x < Width; x++) {
            if (m_stage[y][x] != Blocks::Air) {
                ret[y] |= (1 << x);
            }
        }
    }
    return ret;
}

Grid<Blocks> Stage::getAsGrid() {
    return m_stage;
}
