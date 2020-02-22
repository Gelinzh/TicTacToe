#ifndef PVPWIDGET_H
#define PVPWIDGET_H

#include "widget.h"

class PVPWidget_3x3 : public Widget
{
    Q_OBJECT
public:
    explicit PVPWidget_3x3(QWidget *parent = nullptr);

    void Operation();
    void Again();

private:
    bool player;
signals:

};

#endif // PVPWIDGET_H
