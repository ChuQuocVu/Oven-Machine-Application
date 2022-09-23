#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>
#include <QTimer>
#include <QDebug>

class Counter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int intervals READ intervals WRITE setIntervals NOTIFY intervalsChanged)
    Q_PROPERTY(int value READ value WRITE setValue NOTIFY valueChanged)
    Q_PROPERTY(int second READ second WRITE setSecond NOTIFY secondChanged)
    Q_PROPERTY(float beginValue READ beginValue WRITE setBeginValue NOTIFY beginValueChanged)
    Q_PROPERTY(bool isRunning READ isRunning WRITE setIsRunning NOTIFY isRunningChanged)

public:
    explicit Counter(QObject *parent = nullptr);

    int intervals() const;
    void setIntervals(int newIntervals);

    int value() const;
    void setValue(int newValue);

    float beginValue() const;
    void setBeginValue(float newBeginValue);

    bool isRunning() const;
    void setIsRunning(bool newIsRunning);

    int second() const;
    void setSecond(int second);

    Q_INVOKABLE void startTimer(float beginValue);
    Q_INVOKABLE void stopTimer();
    Q_INVOKABLE int minuteDisplay() const;
    Q_INVOKABLE int secondDisplay() const;

signals:

    void intervalsChanged();
    void valueChanged();
    void beginValueChanged();
    void isRunningChanged();
    void secondChanged(int second);

    void timeOut();

private:
    QTimer * mTimer;
    int m_intervals;
    int m_value;
    int m_beginValue;
    bool m_isRunning;
    int m_second;
};

#endif // COUNTER_H
