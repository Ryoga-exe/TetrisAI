#include "Common.hpp"
#include "Tetris.hpp"
#include "KeyConfig/KeyConfig.hpp"

void Main() {
    Graphics::SetVSyncEnabled(false);
    Tetris tetris;
    KeyConfig keycon;

    while (System::Update()) {
        tetris.update(keycon);
        tetris.draw();
    }
}
