#ifndef RECIPE_H
#define RECIPE_H

#include <QObject>
#include <QDebug>
#include <QQuickPaintedItem>
#include <QImage>

class Recipe : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name READ name WRITE setname NOTIFY nameChanged)
    Q_PROPERTY(float cookingTime READ cookingTime WRITE setCookingTime NOTIFY cookingTimeChanged)
    Q_PROPERTY(float temperature READ temperature WRITE setTemperature NOTIFY temperatureChanged)
    Q_PROPERTY(bool state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString fileImage READ fileImage WRITE setFileImage NOTIFY fileImageChanged)

public:
    explicit Recipe(QObject *parent = nullptr);

    Recipe(const QString &name, const float &cookingTime, const float &temperature, const bool &state, const QString &fileImage, QObject * parent = nullptr);

    QString name() const;
    float cookingTime() const;
    float temperature() const;
    bool state() const;
    QString fileImage() const;

    void setname(QString newName);
    void setCookingTime(float newCookingTime);
    void setTemperature(float newTemperature);
    void setState(bool newState);
    void setFileImage(QString newFileImage);

signals:

    void nameChanged();
    void cookingTimeChanged();
    void temperatureChanged();
    void stateChanged();
    void fileImageChanged();

private:
    QString m_name;
    int m_cookingTime;
    float m_temperature;
    bool m_state;
    QString m_fileImage;
};

#endif // RECIPE_H
