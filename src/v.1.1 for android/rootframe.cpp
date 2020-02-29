#include "rootframe.h"

RootFrame::RootFrame(int &width, int &height, QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(width, height);
    this->setStyleSheet("RootFrame {background-color: #ffffff;}");


    mainWindow = new MainWindow(width, height, this);
    menuAbout  = new Menu_ABOUT(width, height, this);
    menuOption = new Menu_OPTION(width, height, this);

    InitFile();

    menuAbout->hide();
    menuOption->hide();

    connect(mainWindow, &MainWindow::switch_about, [this](){mainWindow->TimerControl("pause"); SwitchIndex(1, 2);});
    connect(mainWindow, &MainWindow::switch_option, [this](){mainWindow->TimerControl("pause"); SwitchIndex(1, 0);});
    connect(menuAbout,  &Menu_ABOUT::switch_back, [this](){mainWindow->TimerControl("continue"); SwitchIndex(2, 1);});
    connect(menuOption, &Menu_OPTION::switch_back, [this](){mainWindow->TimerControl("continue"); SwitchIndex(0, 1);});

    connect(menuOption, &Menu_OPTION::timer_changed, [this]()
    {
        this->timer_range = menuOption->time_slider->value();
        mainWindow->timer_range = this->timer_range;
        setting->setValue("timer_range", this->timer_range);
    });

    connect(menuOption, &Menu_OPTION::volume_changed, [this]()
    {
        this->isMute = menuOption->volume_checkbox->isChecked();
        if(isMute)
        {
            menuOption->l_volume->setPixmap(*menuOption->pix_volume_down);
            mainWindow->isMute = true;
        }
        else
        {
            menuOption->l_volume->setPixmap(*menuOption->pix_volume);
            mainWindow->isMute = false;
        }
        setting->setValue("isMute", this->isMute);
    });

    connect(menuOption, &Menu_OPTION::switch_changed, [this]()
    {
        this->isSwitch = menuOption->switch_checkbox->isChecked();
        mainWindow->isSwitch = this->isSwitch;
        setting->setValue("isSwitch", this->isSwitch);
    });

    connect(mainWindow, &MainWindow::record_changed, [this]()
    {
        this->record_drawNum = mainWindow->record_drawNum;
        setting->setValue("record_drawNum", this->record_drawNum);
    });
}

RootFrame::~RootFrame()
{
}

void RootFrame::SwitchIndex(int previous, int target)
{
    switch(previous)
    {
    case 0: switch_previous = menuOption; break;
    case 1: switch_previous = mainWindow; break;
    case 2: switch_previous = menuAbout; break;
    default:
        break;
    }
    switch(target)
    {
    case 0: switch_target = menuOption; break;
    case 1: switch_target = mainWindow; break;
    case 2: switch_target = menuAbout; break;
    default:
        break;
    }

    switch_previous->hide();
    switch_target->show();
//    opcani_pre = new QPropertyAnimation(opcEff_pre, "opacity");
//    opcani_pre->setDuration(1000);
//    opcani_pre->setStartValue(1);
//    opcani_pre->setEndValue(0);
//    opcani_pre->setEasingCurve(QEasingCurve::InQuint);
//    opcani_tar = new QPropertyAnimation(opcEff_tar, "opacity");
//    opcani_tar->setDuration(1000);
//    opcani_tar->setStartValue(0);
//    opcani_tar->setEndValue(1);
//    opcani_tar->setEasingCurve(QEasingCurve::InQuint);

//    opcEff_tar->setOpacity(0);
//    switch_target->setGraphicsEffect(opcEff_tar);
//    switch_target->show();

//    opcani_pre->start();
//    opcani_tar->start(QAbstractAnimation::DeleteWhenStopped);

//    connect(opcani_pre, &QPropertyAnimation::valueChanged, [this](){switch_previous->setGraphicsEffect(opcEff_pre);});
//    connect(opcani_tar, &QPropertyAnimation::valueChanged, [this](){switch_target->setGraphicsEffect(opcEff_tar);});
//    connect(opcani_pre, &QAbstractAnimation::finished, [this]
//    {
//        delete opcani_pre;
//        switch_previous->hide();
//        qDebug() << "ANIMATE FINISHED!";
    //    });
}

void RootFrame::InitFile()
{
    QDir *folder = new QDir;

    qDebug() << "MARKDOWN" << folder->currentPath();

    QString filename;
    filename = folder->currentPath() + "/config.ini";

    setting = new QSettings(filename, QSettings::IniFormat);

    if(!setting->contains("record_drawNum")||
       !setting->contains("timer_range")||
       !setting->contains("isMute")||
       !setting->contains("isSwitch"))
    {
        qDebug() << "Making New File";
        setting->setValue("record_drawNum", 0);
        setting->setValue("timer_range", 5);
        setting->setValue("isMute", false);
        setting->setValue("isSwitch", true);
    }

    record_drawNum = setting->value("record_drawNum").toInt();
    timer_range = setting->value("timer_range").toInt();
    isMute = setting->value("isMute").toBool();
    isSwitch = setting->value("isSwitch").toBool();

    mainWindow->record_drawNum = this->record_drawNum;
    mainWindow->l_best->setText(QString::number(mainWindow->record_drawNum));
    mainWindow->timer_range = this->timer_range;
    mainWindow->isMute = this->isMute;
    mainWindow->isSwitch = this->isSwitch;

    menuOption->time_slider->setValue(timer_range);
    menuOption->volume_checkbox->setChecked(isMute);
    menuOption->switch_checkbox->setChecked(isSwitch);

    if(isMute)
    {
        menuOption->l_volume->setPixmap(*menuOption->pix_volume_down);
    }
}

