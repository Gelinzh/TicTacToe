#include "mainwindow.h"

#include <QStatusBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    InitMedia();
    InitGUI();
    InitOption();
    InitHelp();

    currSize = 3;
    currDiff = 1;
    drawNum_curr = 0;
    drawNum_record = 0;

    connect(restart, &QAction::triggered, [this]()
    {
        mainWidget->Again(true);
    });

    connect(setting, &QAction::triggered, [this]()
    {
        mainWidget->TimerControl("pause");
        this->optionMenu->show();
    });

    connect(help, &QAction::triggered, [this]()
    {
        mainWidget->TimerControl("pause");
        this->helpMenu->show();
    });

    connect(optionMenu, &OptionMenu::om_change, this, &MainWindow::UpdateCurr);

    connect(optionMenu, &OptionMenu::om_close, [this]()
    {
        mainWidget->TimerControl("continue");
    });

    connect(helpMenu, &HelpMenu::hm_close, [this]()
    {
        mainWidget->TimerControl("continue");
    });

    connect(mainWidget, &GameImple::gi_exit, this, &MainWindow::close);
    connect(mainWidget, &GameImple::gi_allow, [this](){this->l_state->setPixmap(*pix_allow);});
    connect(mainWidget, &GameImple::gi_stop, [this](){this->l_state->setPixmap(*pix_stop);});
    connect(mainWidget, &GameImple::gi_loading, [this](){this->l_state->setPixmap(*pix_loading);});
;}

MainWindow::~MainWindow()
{
}

void MainWindow::UpdateCurr()
{
    int size = -1, diff = -1;
    if(optionMenu->temp->isChecked())
    {
        size = 4;
        diff = optionMenu->switch_scale->value();
    }
    else if(optionMenu->r3x3->isChecked())
    {
        size = 3;
        diff = optionMenu->diff;
    }
    else if(optionMenu->r5x5->isChecked())
    {
        size = 5;
        diff = optionMenu->diff;
    }
    SwitchMode(size, diff);
}

void MainWindow::SwitchMode(int size, int diff)
{
    if(size != currSize || (diff != currDiff && currDiff == 2) || (size == 4 && diff != currDiff)) //change mainwindow size if size change/switch from timer mode/size changed in custom mode
    {
        this->setWindowTitle("TicTacToe");
        if(size != 4)
            this->setFixedSize(size * 100 + 2, size * 100 + 36);
        else
            this->setFixedSize(diff * 100 + 2, diff * 100 + 36);
    }

    if(size != currSize || diff != currDiff)
    {
        mainWidget->close();
        delete mainWidget;
        if(size == 3)
        {
            if(diff == 0)
                mainWidget = new Random_3(this);
            else if(diff == 1)
                mainWidget = new Normal_3(this);
            else if(diff == 2)
            {
                //Timer Mode Init
                mainWidget = new Timer_3(this);

                this->drawNum_curr = 0;
                this->setFixedSize(size * 100 + 2, size * 100 + 46); //add 10px in height in timer mode
                this->setWindowTitle("TicTacToe - " + QString::number(drawNum_curr) + " / " + QString::number(drawNum_record));

                connect(mainWidget, &GameImple::timer_askRecord, [this]()
                {
                    mainWidget->drawNum_record = drawNum_record;
                });
                connect(mainWidget, &GameImple::timer_addDraw_start, [this]()
                {
                    drawNum_curr = mainWidget->drawNum;
                    this->setWindowTitle("TicTacToe - " + QString::number(drawNum_curr - 1) + "+1 / " + QString::number(drawNum_record));
                });
                connect(mainWidget, &GameImple::timer_addDraw_finish, [this]()
                {
                    this->setWindowTitle("TicTacToe - " + QString::number(drawNum_curr) + " / " + QString::number(drawNum_record));
                });
                connect(mainWidget, &GameImple::timer_record, [this]()
                {
                    if(mainWidget->drawNum > drawNum_record)
                        drawNum_record = mainWidget->drawNum;
                    drawNum_curr = 0;
                    this->setWindowTitle("TicTacToe - " + QString::number(drawNum_curr) + " / " + QString::number(drawNum_record));
                });
            }
        }
        else if(size == 5)
        {
            if(diff == 0)
                mainWidget = new Random_5(this);
            else if(diff == 1)
                mainWidget = new Normal_5(this);
        }
        else if(size == 4)
        {
            mainWidget = new Custom(diff, this);
        }
        mainWidget->move(1, 35);
        mainWidget->show();

        currSize = size;
        currDiff = diff;

        //the connect functions of a class will be delete when the class is deleted.
        connect(restart, &QAction::triggered, [this](){ mainWidget->Again(true); });
        connect(mainWidget, &GameImple::gi_exit, this, &MainWindow::close);
        connect(mainWidget, &GameImple::gi_allow, [this](){this->l_state->setPixmap(*pix_allow);});
        connect(mainWidget, &GameImple::gi_stop, [this](){this->l_state->setPixmap(*pix_stop);});
        connect(mainWidget, &GameImple::gi_loading, [this](){this->l_state->setPixmap(*pix_loading);});
    }
}

void MainWindow::InitMedia()
{
    this->sound_clicked   =  new QMediaPlayer;
    this->icon_o          =  new QIcon("asset/image/o.png");
    this->icon_x          =  new QIcon("asset/image/x.png");
    this->icon_restart    =  new QIcon("asset/image/restart.png");
    this->icon_setting    =  new QIcon("asset/image/setting.png");
    this->icon_help       =  new QIcon("asset/image/help.png");
    this->pix_3x3         =  new QPixmap("asset/image/mode_3x3.png");
    this->pix_5x5         =  new QPixmap("asset/image/mode_5x5.png");
    this->pix_stop        =  new QPixmap("asset/image/stop.png");
    this->pix_allow       =  new QPixmap("asset/image/allow.png");
    this->pix_loading     =  new QPixmap("asset/image/loading.png");
    this->pix_logo        =  new QPixmap("asset/image/logo.png");
    this->sound_clicked->setMedia(QUrl("asset/sounds/clicked.wav"));
    this->sound_clicked->setVolume(100);
}

void MainWindow::InitGUI(int size)
{
    /*=======INIT FRAME========*/
    this->setFixedSize(size * 100 + 2, size * 100 + 36);
    this->setWindowTitle("TicTacToe");

    /*=======INIT TOOLBAL======*/
    toolBar = addToolBar("toolBar");
    toolBar->setMovable(false);
    toolBar->setContextMenuPolicy(Qt::PreventContextMenu);
    //actions
    restart = new QAction(*icon_restart, "Restart");
    setting = new QAction(*icon_setting, "Setting");
    help    = new QAction(*icon_help, "Help");
    toolBar->addAction(restart);
    toolBar->addSeparator();
    toolBar->addAction(setting);
    toolBar->addSeparator();
    toolBar->addAction(help);

    /*=====INIT STATE_LABEL=====*/
    QWidget *spacer = new QWidget(this);
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    l_state = new QLabel("state", this);
    l_state->setPixmap(*pix_allow);
    toolBar->addWidget(spacer);
    toolBar->addWidget(l_state);

    /*=======INIT CBOARD=======*/
    mainWidget = new Normal_3(this);
    mainWidget->move(1, 35);
}

void MainWindow::InitOption()
{
    optionMenu = new OptionMenu(this);
    optionMenu->setWindowTitle("Setting");
    optionMenu->setFixedSize(400, 170);
    optionMenu->setWindowFlags(Qt::Window | Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    optionMenu->setWindowModality(Qt::WindowModal);

    //insert images
    optionMenu->r3x3->setStyleSheet("QRadioButton::indicator {width: 100px; height: 100px;}"
                                    "QRadioButton::indicator::unchecked {image: url(asset/image/mode_3x3_0.png); background-position:center;}"
                                    "QRadioButton::indicator::checked {image: url(asset/image/mode_3x3_1.png); background-position:center;}");
    optionMenu->r5x5->setStyleSheet("QRadioButton::indicator {width: 100px; height: 100px;}"
                                    "QRadioButton::indicator::unchecked {image: url(asset/image/mode_5x5_0.png); background-position:center;}"
                                    "QRadioButton::indicator::checked {image: url(asset/image/mode_5x5_1.png); background-position:center;}");
}

void MainWindow::InitHelp()
{
    helpMenu = new HelpMenu(this);
    helpMenu->setWindowTitle("About");
    helpMenu->setFixedSize(350, 200);
    helpMenu->setWindowFlags(Qt::Window | Qt::Dialog | Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
    helpMenu->setWindowModality(Qt::WindowModal);

    helpMenu->l_logo->setPixmap(*pix_logo);
    helpMenu->l_logo->setScaledContents(true);

    //insert images
    helpMenu->b_githubUrl->setStyleSheet("QPushButton {width: 100px; height: 100px;}"
                                         "QPushButton {border-image: url(asset/image/github_logo.png); background-position:center;}");
    helpMenu->b_biliUrl->setStyleSheet("QPushButton {width: 100px; height: 100px;}"
                                       "QPushButton {border-image: url(asset/image/bili_logo.png); background-position:center;}");
}

