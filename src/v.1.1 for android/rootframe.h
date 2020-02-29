#ifndef ROOTFRAME_H
#define ROOTFRAME_H

#include "mainwindow.h"
#include "menu_about.h"
#include "menu_option.h"

#include <QDir>
#include <QSettings>
//#include <QPropertyAnimation>
//#include <QPainter>
//#include <QPaintEvent>
//#include <QMouseEvent>

class RootFrame : public QWidget
{
    Q_OBJECT
public:
    RootFrame(int &width, int &height, QWidget *parent = nullptr);
    ~RootFrame();

    void InitFile();

    void SwitchIndex(int previous, int target);

    MainWindow *mainWindow;
    Menu_ABOUT *menuAbout;
    Menu_OPTION *menuOption;

    //basic info
    QSettings *setting;
    int record_drawNum;
    int timer_range;
    bool isMute;
    bool isSwitch;

//protected:
//    void paintEvent(QPaintEvent *event) Q_DECL_OVERRIDE;
//    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

private:
    QWidget *switch_previous;
    QWidget *switch_target;

//    QGraphicsOpacityEffect *opcEff_pre;
//    QGraphicsOpacityEffect *opcEff_tar;

//    QPropertyAnimation *opcani_pre, *posani_pre;
//    QPropertyAnimation *opcani_tar, *posani_tar;

signals:

};

#endif // ROOTFRAME_H
