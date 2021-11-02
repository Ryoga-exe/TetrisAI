#pragma once
#include "Common.hpp"

struct Level {
public:
    Level() {
        init();
    }

    void init() {
        m_deletedLineNum = 0;
        m_level = 1;
        m_interval = Duration(pow(0.8 - (m_level - 1) * 0.007, m_level - 1));
    }

    Level& operator+=(const int32 r) {
        m_deletedLineNum += r;
        int32 now = 1 + m_deletedLineNum / 15;
        if (m_level < now) {
            m_level = now;
            m_interval = Duration(pow(0.8 - (m_level - 1) * 0.007, m_level - 1));
        }
        return *this;
    }

    int32 level() const {
        return m_level;
    }

    int32 deletedLineNum() const{
        return m_deletedLineNum;
    }

    Duration interval() const {
        return m_interval;
    }

    operator int32() const {
        return m_level;
    }

private:
    int32 m_level;
    int32 m_deletedLineNum;
    Duration m_interval;
};
