#ifndef WORD
#define WORD

#include <QString>

class Word
{
public:
    Word(QString word, QString color)
        :m_notColored(word), m_colored(""), m_nColor(color)
    {}

    // Methods for getting a full word out of small pieces
    QString getColoredWord() const;
    QString getWord() const;

    // Methods for getting (not) colored part of a word
    QString getNotColored() const;
    QString getColored() const;

    // Set methods
    void setColored(QString word);
    void setNotColored(QString word);

    int length();

private:
    QString m_notColored;
    QString m_colored;
    QString m_nColor;
};

#endif // WORD
