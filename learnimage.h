#ifndef LEARNIMAGE_H
#define LEARNIMAGE_H

#include <QObject>
#include <QImage>
#include <QQuickPaintedItem>
#include <QPainter>
#include "recipe.h"

class LearnImage : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor bgColor READ bgColor WRITE setBgColor NOTIFY bgColorChanged)
    Q_PROPERTY(QColor textColor READ textColor WRITE setTextColor NOTIFY textColorChanged)
    Q_PROPERTY(QString text READ text WRITE setText NOTIFY textChanged)
    Q_PROPERTY(QString filepath READ filepath WRITE setFilepath NOTIFY filepathChanged)

public:
    explicit LearnImage(QQuickItem *parent = nullptr);

    void paint(QPainter * painter);

    QColor bgColor() const;
    QColor textColor() const;
    QString text() const;
    QString filepath() const;

    void setBgColor(QColor bgColor);
    void setTextColor(QColor textColor);
    void setText(QString text);
    void setFilepath(QString filepath);

signals:

    void bgColorChanged(QColor bgColor);
    void textColorChanged(QColor textColor);
    void textChanged(QString text);
    void filepathChanged(QString filepath);

private:

    QColor m_bgColor;
    QColor m_textColor;
    QString m_text;
    QString m_filepath;
};

#endif // LEARNIMAGE_H
