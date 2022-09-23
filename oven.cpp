#include "oven.h"

Oven::Oven(QObject *parent) : QObject(parent), m_mode(None), m_userMode(MANUAL)
{

}

int Oven::mode() const
{
    return m_mode;
}

bool Oven::running() const
{
    return m_running;
}

void Oven::setMode(int mode)
{
    if (m_mode == mode)
        return;

    m_mode = mode;
    emit modeChanged(m_mode);
}

void Oven::setRunning(bool running)
{
    if (m_running == running)
        return;

    m_running = running;
    emit runningChanged(m_running);
}

int Oven::userMode() const
{
    return m_userMode;
}

void Oven::setUserMode(int userMode)
{
    if (m_userMode == userMode)
        return;

    m_userMode = userMode;
    emit userModeChanged(m_userMode);
}
