#include "word.h"

QString Word::getColoredWord() const
{
    QString tmp("<font color=\"red\">");
    tmp.append(m_colored);
    tmp.append("</font><font color=\"");
    tmp.append(m_nColor);
    tmp.append("\">");
    tmp.append(m_notColored);
    tmp.append("</font>");
    return tmp;
}

QString Word::getWord() const
{
    QString tmp = m_colored;
    tmp.append(m_notColored);
    return tmp;
}

QString Word::getNotColored() const
{
    return m_notColored;
}

QString Word::getColored() const
{
    return m_colored;
}


void Word::setColored(QString word)
{
    m_colored = word;
}

void Word::setNotColored(QString word)
{
    m_notColored = word;
}


int Word::length()
{
    return m_notColored.length() + m_colored.length();
}
