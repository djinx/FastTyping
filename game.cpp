#include "game.h"
#include "word.h"

Game::Game(int P1, int P2)
    :m_allWords(0), m_scoreP1(P1), m_scoreP2(P2), m_combo(0)
    {
    }


QString Game::getScoreP1() const
{
    QString str;
    str.setNum(m_scoreP1);
    return str;
}

QString Game::getScoreP2() const
{
    QString str;
    str.setNum(m_scoreP2);
    return str;
}

int Game::getPointsP1() const
{
    return m_scoreP1;
}

int Game::getPointsP2() const
{
    return m_scoreP2;
}

unsigned Game::getCombo() const
{
    return m_combo;
}

void Game::setScoreP1(int p1)
{
    m_scoreP1 = p1;
}

void Game::setScoreP2(int p2)
{
    m_scoreP2 = p2;
}

void Game::setCombo(unsigned c)
{
    m_combo = c;
}

void Game::readWords(const QString fileName)
{
    QFile file(fileName);
    if(!file.open(QFile::ReadOnly |
                  QFile::Text))
    {
        throw "No puedo mas!";
    }

    m_allWords.clear();
    QTextStream in(&file);
    QString word;
    while(!(word = in.readLine()).isNull())
    {
        m_allWords.push_back(word);
    }
    file.close();

    // Generating a random sequence of appearance of words
    auto engine = std::default_random_engine{};
    engine.seed(time(0));
    std::shuffle(m_allWords.begin(), m_allWords.end(), engine);
}

QString Game::nextWord(int i)
{
    return m_allWords[i];
}

unsigned Game::numOfWords()
{
    return m_allWords.size();
}

void Game::updateScore(int bonus)
{
    setScoreP1(m_scoreP1 + bonus*10);
}

