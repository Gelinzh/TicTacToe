#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <QStackedWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QLabel>
#include <QLayout>
#include <QToolBar>

#include <QDebug>
#include <QDesktopWidget>

#include "optionmenu.h"
#include "helpmenu.h"
#include "random_3.h"
#include "random_5.h"
#include "normal_3.h"
#include "normal_5.h"
#include "timer_3.h"
#include "custom.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void UpdateCurr();
    void SwitchMode(int size, int diff);      //delete all pieces and create new checkerboard
    void Restart();                                                     //clean the data, but will not delete pieces

    //Setters
    void InitMedia();
    void InitGUI(int size = 3);
    void InitOption();
    void InitHelp();

    //Getters

    //State
    int currSize;
    int currDiff;

    int drawNum_curr;
    int drawNum_record;

    //Elements
    QToolBar *toolBar;
    QAction *restart, *setting, *help;
    QLabel *l_state; //last one is for timer mode
    GameImple *mainWidget;

    //Element option
    OptionMenu *optionMenu;

    //Elements help
    HelpMenu *helpMenu;

private:
    QIcon *icon_x, *icon_o, *icon_restart, *icon_setting, *icon_help, icon_temp;
    QPixmap *pix_stop, *pix_allow, *pix_loading, *pix_3x3, *pix_5x5, *pix_logo;
    QMediaPlayer *sound_clicked, sound_temp;

};
#endif // MAINWINDOW_H
