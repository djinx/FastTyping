#ifndef LABEL_H
#define LABEL_H

#include <QWidget>
#include <QLabel>

#include "game.h"

class Label
{
public:
    // constructor
    Label(QLabel* label);

    // getters
    QLabel* getLabel() const;
    bool getHidden() const;
    int getSpeed() const;

    // setters
    void setSpeed(int speed);
    void setHidden(bool b);

    // others
    bool moveLabel(int line);
    unsigned length();

private:
    QLabel* m_label;
    bool m_hidden;
    int m_speed;
};

#endif // LABEL_H
