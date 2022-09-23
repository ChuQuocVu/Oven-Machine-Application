#include "recipe.h"

Recipe::Recipe(QObject *parent)
    : QObject{parent}
{

}

Recipe::Recipe(const QString &name, const float &cookingTime, const float &temperature, const bool &state, const QString &fileImage, QObject *parent):
    QObject(parent), m_name(name), m_cookingTime(cookingTime), m_temperature(temperature), m_state(state),m_fileImage(fileImage)
{

}


QString Recipe::name() const
{
    return m_name;
}

void Recipe::setname(QString newName)
{
    if (m_name == newName)
        return;
    m_name = newName;
    emit nameChanged();
}

float Recipe::cookingTime() const
{
    return m_cookingTime;
}

void Recipe::setCookingTime(float newCookingTime)
{
    if (m_cookingTime == newCookingTime)
        return;
    m_cookingTime = newCookingTime;
    emit cookingTimeChanged();
}

float Recipe::temperature() const
{
    return m_temperature;
}

void Recipe::setTemperature(float newTemperature)
{
    if (qFuzzyCompare(m_temperature, newTemperature))
        return;
    m_temperature = newTemperature;
    emit temperatureChanged();
}

bool Recipe::state() const
{
    return m_state;
}

void Recipe::setState(bool newState)
{
    if (m_state == newState)
        return;
    m_state = newState;
    emit stateChanged();
}

QString Recipe::fileImage() const
{
    return m_fileImage;
}

void Recipe::setFileImage(const QString newFileImage)
{
    if (m_fileImage == newFileImage)
        return;
    m_fileImage = newFileImage;
    emit fileImageChanged();
}
