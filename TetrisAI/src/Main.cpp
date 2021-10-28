#include "Common.hpp"
#include "Tetris.hpp"
#include "KeyConfig.hpp"

void Main() {
    Tetris tetris;
    KeyConfig keycon;
    int32 index = 0;
    while (System::Update()) {
        ClearPrint();
        Print << index;
        tetris.update(keycon);
        tetris.draw();

        auto res = tetris.getAllPlaceable();

        // if (0 <= index && index < res.size()) tetris.drawMino(res[index], ColorF(1.0, 0.3));

        if (Key1.down()) index++;
        if (Key2.down()) index--;
    }
}
