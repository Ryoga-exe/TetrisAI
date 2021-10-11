#pragma once
#include "Common.hpp"

enum class Blocks : uint32 {
    Air,
    Block,
    I,
    O,
    S,
    Z,
    J,
    L,
    T,
};

namespace Mino {
    constexpr uint32 Types = 7;
    constexpr uint32 Angles = 4;
    constexpr uint32 Size = 4;

    using enum Blocks;
    constexpr Blocks Shapes[Types][Angles][Size][Size]
    {
        {       // I
            {
                Air,Air,Air,Air,
                I  ,I  ,I  ,I  ,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,I  ,Air,
                Air,Air,I  ,Air,
                Air,Air,I  ,Air,
                Air,Air,I  ,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                I  ,I  ,I  ,I  ,
                Air,Air,Air,Air,
            },
            {
                Air,I  ,Air,Air,
                Air,I  ,Air,Air,
                Air,I  ,Air,Air,
                Air,I  ,Air,Air,
            },
        },{     // O
            {
                Air,Air,Air,Air,
                Air,O  ,O  ,Air,
                Air,O  ,O  ,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,O  ,O  ,Air,
                Air,O  ,O  ,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,O  ,O  ,Air,
                Air,O  ,O  ,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,O  ,O  ,Air,
                Air,O  ,O  ,Air,
                Air,Air,Air,Air,
            },
        },{     // S
            {
                Air,Air,Air,Air,
                Air,S  ,S  ,Air,
                S  ,S  ,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,S  ,Air,Air,
                Air,S  ,S  ,Air,
                Air,Air,S  ,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,S  ,S  ,Air,
                S  ,S  ,Air,Air,
            },
            {
                Air,Air,Air,Air,
                S  ,Air,Air,Air,
                S  ,S  ,Air,Air,
                Air,S  ,Air,Air,
            },
        },{     // Z
            {
                Air,Air,Air,Air,
                Z  ,Z  ,Air,Air,
                Air,Z  ,Z  ,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Z  ,Air,
                Air,Z  ,Z  ,Air,
                Air,Z  ,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Z  ,Z  ,Air,Air,
                Air,Z  ,Z  ,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Z  ,Air,Air,
                Z  ,Z  ,Air,Air,
                Z  ,Air,Air,Air,
            },
        },{     // L
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
        },{     // J
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
        },{     // T
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
            {
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
                Air,Air,Air,Air,
            },
        }
    };

    constexpr Color GetColor(Blocks block) {
        Color ret(0);
        switch (block) {
        case I: ret = Palette::Lightblue; break;
        case O: ret = Palette::Yellow; break;
        case S: ret = Palette::Green; break;
        case Z: ret = Palette::Red; break;
        case J: ret = Palette::Darkblue; break;
        case L: ret = Palette::Orange; break;
        case T: ret = Palette::Magenta; break;
        }
        return ret;
    }

}
