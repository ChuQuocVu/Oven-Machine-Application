#include "learnimage.h"

LearnImage::LearnImage(QQuickItem *parent) : QQuickPaintedItem(parent)
{
    setWidth(100);
    setHeight(90);
}

void LearnImage::paint(QPainter *painter)
{
    QString imagePath = m_filepath;

    QImage mImage(imagePath);
    QImage scaledImage = mImage.scaled(width() , height());
    QRect mRect(mImage.rect());
    painter->drawImage(mRect,scaledImage);

    //Draw the rectangle at the bottom
    painter->setBrush(bgColor());
    painter->drawRect(mRect.bottomLeft().x(),
                      mRect.bottomLeft().y()-10,
                      width(),10);

    //Draw the text
    painter->setPen(textColor());
    auto txtPos = mRect.bottomLeft();
    txtPos.rx() += 1;
    txtPos.ry() -= 1;
    painter->setFont(QFont ("Consolas", 10, QFont::Bold));
    painter->drawText(txtPos,text());
}

QColor LearnImage::bgColor() const
{
    return m_bgColor;
}

QColor LearnImage::textColor() const
{
    return m_textColor;
}

QString LearnImage::text() const
{
    return m_text;
}

void LearnImage::setBgColor(QColor bgColor)
{
    if (m_bgColor == bgColor)
        return;

    m_bgColor = bgColor;
    emit bgColorChanged(m_bgColor);
}

void LearnImage::setTextColor(QColor textColor)
{
    if (m_textColor == textColor)
        return;

    m_textColor = textColor;
    emit textColorChanged(m_textColor);
}

void LearnImage::setText(QString text)
{
    if (m_text == text)
        return;

    m_text = text;
    emit textChanged(m_text);
}

QString LearnImage::filepath() const
{
    return m_filepath;
}

void LearnImage::setFilepath(QString filepath)
{
    if (m_filepath == filepath)
        return;

    m_filepath = filepath;
    emit filepathChanged(m_filepath);
}
