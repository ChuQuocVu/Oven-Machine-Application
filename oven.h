#ifndef OVEN_H
#define OVEN_H

#include <QObject>

class Oven : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int mode READ mode WRITE setMode NOTIFY modeChanged)
    Q_PROPERTY(int userMode READ userMode WRITE setUserMode NOTIFY userModeChanged)
    Q_PROPERTY(bool running READ running WRITE setRunning NOTIFY runningChanged)

public:
    explicit Oven(QObject *parent = nullptr);

    enum MODE
    {
        None,
        Grill,
        Stream,
        Warmer,
        Fan,
        MANUAL,
        DEFAULT
    };

    Q_ENUM(MODE)

    int mode() const;
    bool running() const;
    int userMode() const;

    void setMode(int mode);
    void setRunning(bool running);
    void setUserMode(int userMode);

signals:

    void modeChanged(int mode);
    void runningChanged(bool running);
    void userModeChanged(int userMode);

private:

    int m_mode;
    bool m_running;
    int m_userMode;
};

#endif // OVEN_H
