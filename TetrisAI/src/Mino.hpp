#pragma once
#include "Common.hpp"
#include "Block.hpp"

class Mino {
public:
    Mino();
    Mino(uint32 type, uint32 angle = 0);
    Mino(uint32 type, uint32 angle, Point pos);

    ~Mino();

    bool update();
    void draw() const;

    void move(const int32 x, const int32 y);
    void move(const Point diff);
    void moveTo(const int32 x, const int32 y);
    void moveTo(const Point to);
    Mino moved(const int32 x, const int32 y) const;
    Mino moved(const Point diff) const;

    Point position() const;
    uint32 type() const;
    uint32 angle() const;

    Mino operator =(const Mino& mino);

private:
    Point generatePos();

private:
    Point m_pos;
    uint32 m_type;
    uint32 m_angle;

public:
    static constexpr uint32 Types = 7;
    static constexpr uint32 Angles = 4;
    static constexpr uint32 Size = 4;

    using enum Blocks;
    static constexpr Blocks Shapes[Types][Angles][Size][Size]
    {
        {       // I
            {
                { Air,Air,Air,Air },
                { I  ,I  ,I  ,I   },
                { Air,Air,Air,Air },
                { Air,Air,Air,Air },
            },
            {
                { Air,Air,I  ,Air },
                { Air,Air,I  ,Air },
                { Air,Air,I  ,Air },
                { Air,Air,I  ,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,Air,Air,Air },
                { I  ,I  ,I  ,I   },
                { Air,Air,Air,Air },
            },
            {
                { Air,I  ,Air,Air },
                { Air,I  ,Air,Air },
                { Air,I  ,Air,Air },
                { Air,I  ,Air,Air },
            },
        },{     // O
            {
                { Air,Air,Air,Air },
                { Air,O  ,O  ,Air },
                { Air,O  ,O  ,Air },
                { Air,Air,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,O  ,O  ,Air },
                { Air,O  ,O  ,Air },
                { Air,Air,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,O  ,O  ,Air },
                { Air,O  ,O  ,Air },
                { Air,Air,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,O  ,O  ,Air },
                { Air,O  ,O  ,Air },
                { Air,Air,Air,Air },
            },
        },{     // S
            {
                { Air,Air,Air,Air },
                { Air,S  ,S  ,Air },
                { S  ,S  ,Air,Air },
                { Air,Air,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,S  ,Air,Air },
                { Air,S  ,S  ,Air },
                { Air,Air,S  ,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,Air,Air,Air },
                { Air,S  ,S  ,Air },
                { S  ,S  ,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { S  ,Air,Air,Air },
                { S  ,S  ,Air,Air },
                { Air,S  ,Air,Air },
            },
        },{     // Z
            {
                { Air,Air,Air,Air },
                { Z  ,Z  ,Air,Air },
                { Air,Z  ,Z  ,Air },
                { Air,Air,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,Air,Z  ,Air },
                { Air,Z  ,Z  ,Air },
                { Air,Z  ,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,Air,Air,Air },
                { Z  ,Z  ,Air,Air },
                { Air,Z  ,Z  ,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,Z  ,Air,Air },
                { Z  ,Z  ,Air,Air },
                { Z  ,Air,Air,Air },
            },
        },{     // L
            {
                { Air,Air,Air,Air },
                { Air,Air,L  ,Air },
                { L  ,L  ,L  ,Air },
                { Air,Air,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,L  ,Air,Air },
                { Air,L  ,Air,Air },
                { Air,L  ,L  ,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,Air,Air,Air },
                { L  ,L  ,L  ,Air },
                { L  ,Air,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { L  ,L  ,Air,Air },
                { Air,L  ,Air,Air },
                { Air,L  ,Air,Air },
            },
        },{     // J
            {
                { Air,Air,Air,Air },
                { J  ,Air,Air,Air },
                { J  ,J  ,J  ,Air },
                { Air,Air,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,J  ,J  ,Air },
                { Air,J  ,Air,Air },
                { Air,J  ,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,Air,Air,Air },
                { J  ,J  ,J  ,Air },
                { Air,Air,J  ,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,J  ,Air,Air },
                { Air,J  ,Air,Air },
                { J  ,J  ,Air,Air },
            },
        },{     // T
            {
                { Air,Air,Air,Air },
                { Air,T  ,Air,Air },
                { T  ,T  ,T  ,Air },
                { Air,Air,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,T  ,Air,Air },
                { Air,T  ,T  ,Air },
                { Air,T  ,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,Air,Air,Air },
                { T  ,T  ,T  ,Air },
                { Air,T  ,Air,Air },
            },
            {
                { Air,Air,Air,Air },
                { Air,T  ,Air,Air },
                { T  ,T  ,Air,Air },
                { Air,T  ,Air,Air },
            },
        }
    };

    static constexpr Color GetColor(Blocks block) {
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
};
