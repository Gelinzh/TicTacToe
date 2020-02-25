#ifndef RANDOM_5_H
#define RANDOM_5_H

#include "gameimple.h"

#include <QTime>

class Random_5 : public GameImple
{
    Q_OBJECT
public:
    explicit Random_5(QWidget *parent = nullptr);

    void Operation();

    //algorithm part
    void RandomGo();
    void AnalysedGo();
    int GetPriority(int next_move);

    bool Check();
    int CheckerBoard(int [5][5]);
    void Again(bool isResetSide = false);


    bool switch_side;

signals:

};

#endif // RANDOM_5_H
