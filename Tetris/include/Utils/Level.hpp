﻿#pragma once
#include <Siv3D.hpp> // OpenSiv3D v0.6.2

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
        int32 now = 1 + m_deletedLineNum / LEVEL_UP_LINES;
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

    static constexpr int32 LEVEL_UP_LINES = 15;
    static constexpr int32 MAX_SPEED_LEVEL = 20;

private:
    int32 m_level;
    int32 m_deletedLineNum;
    Duration m_interval;
};
