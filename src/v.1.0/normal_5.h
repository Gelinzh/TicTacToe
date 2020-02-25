#ifndef NORMAL_5_H
#define NORMAL_5_H

#include "gameimple.h"

#include <QTime>

class Normal_5 : public GameImple
{
    Q_OBJECT
public:
    explicit Normal_5(QWidget *parent = nullptr);

    void Operation();

    //algorithm part
    void RandomGo();
    void AnalysedGo();
    int GetPriority(int next_move);

    bool Check();
    int  CheckerBoard(int [5][5]);
    void Again(bool isResetSide = false);

    bool switch_side;

signals:

};

#endif // NORMAL_5_H
