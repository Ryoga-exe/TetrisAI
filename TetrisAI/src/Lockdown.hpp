#pragma once
#include "Common.hpp"

struct Lockdown{
public:
    Lockdown() {
        init();
    };

    void init() {
        m_isLockdown = false;
        m_count = m_prevCount = 0;
        m_maxY = 0;
    }

    void set(int32 y) {
        m_isLockdown = true;
        m_count = 0;
        m_prevCount = 0;
        m_maxY = y;
    }

    void update() {
        m_prevCount = m_count;
    }

    bool changed() {
        return m_count != m_prevCount;
    }

    bool oversteped() {
        return m_count > 14;
    }

    operator bool() {
        return m_isLockdown;
    }

    bool updateY(int32 y) {
        bool ret = m_maxY < y;
        if (ret) init();
        return ret;
    }

    Lockdown& operator++() {
        if (m_isLockdown) {
            ++m_count;
        }
        else {
            m_isLockdown = true;
            m_count = 1;
        }
        return *this;
    }

    const Lockdown operator++(int) {
        Lockdown tmp = *this;
        ++(*this);
        return tmp;
    }

private:
    int32 m_count, m_prevCount, m_maxY;
    bool m_isLockdown;
};
