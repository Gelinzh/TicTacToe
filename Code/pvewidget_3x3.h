#ifndef PVEWIDGET_3X3_H
#define PVEWIDGET_3X3_H

#include "widget.h"

#include <QTime>
#include <QDebug>

class PVEWidget_3x3 : public Widget
{
    Q_OBJECT
public:
    explicit PVEWidget_3x3(QWidget *parent = nullptr);

    void Operation();

    //algorithm part
    void RandomGo();
    void AnalysedGo();
    int GetPriority(int next_move);

    bool Check();
    void Again();

    bool switch_side;

signals:

};

#endif // PVEWIDGET_3X3_H
