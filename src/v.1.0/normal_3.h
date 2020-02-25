#ifndef NORMAL_3_H
#define NORMAL_3_H

#include "gameimple.h"

#include <QTime>

class Normal_3 : public GameImple
{
    Q_OBJECT
public:
    explicit Normal_3(QWidget *parent = nullptr);

    void Operation();

    //algorithm part
    void RandomGo();
    void AnalysedGo();
    int GetPriority(int next_move);

    bool Check();
    void Again(bool isResetSide = false);

    bool switch_side;

signals:

};

#endif // NORMAL_3_H
