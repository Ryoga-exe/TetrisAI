#pragma once
#include "Common.hpp"
#include "Block.hpp"

class Tetrimino {
public:
    Tetrimino();
    Tetrimino(uint32 type, uint32 angle = 0);
    Tetrimino(uint32 type, uint32 angle, Point pos);

    ~Tetrimino();

    void draw(const Point v, const Size s) const;

    void move(const int32 x, const int32 y);
    void move(const Point diff);
    Tetrimino moved(const int32 x, const int32 y) const;
    Tetrimino moved(const Point diff) const;
    void moveTo(const int32 x, const int32 y);
    void moveTo(const Point to);
    Tetrimino movedTo(const int32 x, const int32 y) const;
    Tetrimino movedTo(const Point to) const;

    void rotate(bool clockwise);
    Tetrimino rotated(bool clockwise) const;

    Point position() const;
    uint32 type() const;
    uint32 angle() const;
    Vector3D<int32> asVec3() const {
        return Vector3D<int32>{ m_pos.x, m_pos.y, m_angle };
    }
    Vector4D<int32> asVec4() const {
        return Vector4D<int32>{ m_type, m_pos.x, m_pos.y, m_angle };
    }

    Tetrimino operator =(const Tetrimino& mino);
    bool operator ==(const Tetrimino& r) const {
        return (m_type == r.m_type) && (m_pos == r.m_pos) && (m_angle == r.m_angle);
    }

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
        case I: ret = Palette::Cyan; break;
        case O: ret = Palette::Yellow; break;
        case S: ret = Palette::Limegreen; break;
        case Z: ret = Palette::Red; break;
        case J: ret = Palette::Blue; break;
        case L: ret = Palette::Orange; break;
        case T: ret = Palette::Blueviolet; break;
        case Block: ret = Palette::Lightgray; break;
        }
        return ret;
    }
};
