#include "Common.hpp"
#include "Tetris.hpp"
#include "KeyConfig.hpp"

void Main() {
    Tetris tetris;
    KeyConfig keycon;
    while (System::Update()) {
        tetris.update(keycon);
        tetris.draw();
    }
}
