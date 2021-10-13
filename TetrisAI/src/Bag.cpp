#include "Bag.hpp"
#include "Block.hpp"

Bag::Bag() {
    set();
}

Bag::~Bag() {
}

void Bag::set() {
    auto arr = Iota(Mino::Types);
    Shuffle(arr);
    for (auto e : arr) {
        m_que.push(e);
    }
}

uint32 Bag::get() {
    if (m_que.empty()) {
        set();
    }
    uint32 ret = m_que.front();
    m_que.pop();
    return ret;
}
