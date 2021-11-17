#pragma once
#include <queue>
#include <Siv3D.hpp> // OpenSiv3D v0.6.2

class Bag {
public:
    Bag();
    ~Bag();

    void clear();
    bool set();
    uint32 get();

private:
    std::queue<uint32> m_que;
};
