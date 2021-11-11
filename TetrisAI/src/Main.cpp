#include "Common.hpp"
#include "Tetris.hpp"
#include "KeyConfig/KeyConfig.hpp"

void Main() {
    Graphics::SetVSyncEnabled(false);
    Scene::SetBackground(Palette::Slategray);
    Tetris tetris;
    KeyConfig keycon;

    while (System::Update()) {
        tetris.update(keycon);
        tetris.draw();
    }
}
