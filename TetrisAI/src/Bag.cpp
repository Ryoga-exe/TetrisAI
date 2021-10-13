#include "Bag.hpp"
#include "Block.hpp"
#include "Mino.hpp"

Bag::Bag() {
    set();
}

Bag::~Bag() {
}

void Bag::clear() {
    while (!m_que.empty()) {
        m_que.pop();
    }
}

bool Bag::set() {
    if (!m_que.empty()) {
        return false;
    }
    Array<uint32> arr;
    for (auto e : step(Mino::Types)) arr << e;
    Shuffle(arr);
    for (auto e : arr) {
        m_que.push(e);
    }
    return true;
}

uint32 Bag::get() {
    if (m_que.empty()) {
        set();
    }
    uint32 ret = m_que.front();
    m_que.pop();
    return ret;
}
