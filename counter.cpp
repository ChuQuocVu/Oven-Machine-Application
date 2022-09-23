#include "counter.h"

Counter::Counter(QObject *parent)
    : QObject{parent}, mTimer(new QTimer(this)), m_isRunning(false)
{
    connect(mTimer, &QTimer::timeout, this, [=](){
        if(m_isRunning)
        {
            --m_second;
            emit secondChanged(m_second);
            if(m_second < 0)
            {
                m_second = 59;
                emit secondChanged(m_second);
                --m_value;
                emit valueChanged();

                if(m_value < 0)
                {
                    stopTimer();
                    emit timeOut();
                }
            }
        }
    });
}

int Counter::intervals() const
{
    return m_intervals;
}

void Counter::setIntervals(int newIntervals)
{
    if (m_intervals == newIntervals)
        return;
    m_intervals = newIntervals;
    emit intervalsChanged();
}

int Counter::value() const
{
    return m_value;
}

void Counter::setValue(int newValue)
{
    if (m_value == newValue)
        return;
    m_value = newValue;
    emit valueChanged();
}

float Counter::beginValue() const
{
    return m_beginValue;
}

void Counter::setBeginValue(float newBeginValue)
{
    if (m_beginValue == newBeginValue)
        return;
    m_beginValue = newBeginValue;
    emit beginValueChanged();
}

bool Counter::isRunning() const
{
    return m_isRunning;
}

void Counter::setIsRunning(bool newIsRunning)
{
    if (m_isRunning == newIsRunning)
        return;
    m_isRunning = newIsRunning;
    emit isRunningChanged();
}

int Counter::second() const
{
    return m_second;
}

void Counter::setSecond(int second)
{
    if (m_second == second)
        return;

    m_second = second;
    emit secondChanged(m_second);
}

void Counter::startTimer(float beginValue)
{
    int minutes = (int)beginValue / 60;
    int second = (int)beginValue % 60;

    m_value = minutes;
    m_second = second;
    emit valueChanged();
    emit secondChanged(m_second);

    if(!m_isRunning)
    {
        mTimer->start(1000);
        m_isRunning = true;
    }
    else
        qDebug() << "Program is running!";

}

void Counter::stopTimer()
{
    mTimer->stop();
    m_isRunning = false;
}

int Counter::minuteDisplay() const
{
    return m_value;
}

int Counter::secondDisplay() const
{
    return m_second;
}
