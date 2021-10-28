#include "KeyConfig.hpp"

KeyConfig::KeyConfig()
    : m_state(0) {

}

KeyConfig::~KeyConfig() {

}

void KeyConfig::update() {
    m_state = 0;
    if (KeyLeft.down()) {
        m_state |= Action::MoveLeft;
    }
    if (KeyRight.down()) {
        m_state |= Action::MoveRight;
    }
    if (KeyDown.down()) {
        m_state |= Action::SoftDrop;
    }
    if (KeySpace.down()) {
        m_state |= Action::HardDrop;
    }
    if ((KeyUp | KeyX | KeyRControl).down()) {
        m_state |= Action::RotateClockwise;
    }
    if ((KeyZ | KeyLControl).down()) {
        m_state |= Action::RotateCounterclockwise;
    }
    if ((KeyC | KeyLShift | KeyRShift).down()) {
        m_state |= Action::Hold;
    }
}

KeyConfig::operator uint8 (){
    update();
    return m_state;
}
