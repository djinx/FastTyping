#include "label.h"

Label::Label(QLabel* label)
    :m_label(label), m_hidden(false), m_speed(0)
{
    m_label->setAttribute(Qt::WA_TranslucentBackground);
}

QLabel* Label::getLabel() const
{
    return m_label;
}

bool Label::getHidden() const
{
    return m_hidden;
}

int Label::getSpeed() const
{
    return m_speed;
}

void Label::setHidden(bool b)
{
    m_hidden = b;
    if(m_hidden)
    {
        m_label->hide();
    }
    else
    {
        m_label->show();
    }
}

void Label::setSpeed(int speed)
{
    if(speed <= 3)
    {
        m_speed = 4;
    }
    else if(speed > 6)
    {
        m_speed = 1;
    }
    else
    {
        m_speed = 2;
    }
}

bool Label::moveLabel(int line)
{
    if(m_label->y() >= line)
    {
        return false;
    }
    else
    {
        m_label->move(m_label->x(), m_label->y()+m_speed);
        return true;
    }
}
