#ifndef GAME_H
#define GAME_H

// Including Qt libraries
#include <QMainWindow>
#include <QString>
#include <QObject>
#include <QLabel>
#include <QThread>
#include <QTimer>
#include <QDebug>
#include <QPushButton>
#include <QTime>
#include <QFile>
#include <QTextStream>

// Including STD C++ libraries
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <random>

// Including STD C libraries
#include <time.h>

// Including project classes
class Word;

#define TIMEOUT 60

class Game{
public:
    Game(int P1, int P2);

    // Get methods
    QString getScoreP1() const;
    QString getScoreP2() const;
    int getPointsP1() const;
    int getPointsP2() const;
    unsigned getCombo() const;

    // Set methods
    void setScoreP1(int p1);
    void setScoreP2(int p2);
    void setCombo(unsigned c);

    // Reading words from file
    void readWords(const QString fileName);

    // Methods for m_allWords vector
    QString nextWord(int i);
    unsigned numOfWords();

    // Methods for changing score
    void updateScore(int bonus);

private:
    std::vector<QString> m_allWords;
    int m_scoreP1;
    int m_scoreP2;
    unsigned m_combo;
};

#endif // GAME_H
