#include "Common.hpp"
#include "Tetris.hpp"

void Main() {
    Tetris tetris;
    while (System::Update()) {
        tetris.update();
        tetris.draw();
    }
}
