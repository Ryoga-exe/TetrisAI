#pragma once
#include <queue>
#include "Common.hpp"

class Bag {
public:
    Bag();
    ~Bag();

    void set();
    uint32 get();

private:
    std::queue<uint32> m_que;
};
