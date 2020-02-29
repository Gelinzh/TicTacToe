#include "mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(int &rwidth, int &rheight, QWidget *parent)
    : QWidget(parent)
{
    //DEFINE
    width = rwidth;
    height = rheight;
    pieceScale = 3;
    pieceSize  = (width * 0.9) / 3;

    InitMedia();
    InitGUI();
    InitPiece();
    InitGame();
    InitBox();

    connect(setting, &QPushButton::clicked, [this]()
    {
       emit switch_option();
    });

    connect(help, &QPushButton::clicked, [this]()
    {
        emit switch_about();
    });

    connect(restart, &QPushButton::clicked, [this](){ Again(true); });

    connect(Timer, &QTimer::timeout, [this]()
    {
        pgBar->setValue(++progress);
        if(progress == 100)
        {
            //GAMEOVER : TIMEOUT
            Gameover(false);
        }
    });

    connect(pgb_clean, &QTimer::timeout, [this]()
    {
        pgBar->setValue(--progress);
        if(!progress)
        {
            pgb_clean->stop();

            //clean the table
            for (int i = 0; i < 9; i++)
            {
                piece[i].setObjectName(0);
                piece[i].setIcon(icon_temp);
            }
            finish = 0;

            //next round start
            qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

            if(isSwitch)
            {
                if(switch_side)
                    switch_side = false;
                else if(!switch_side)
                {
                    switch_side = true;
                    RandomGo();
                }
            }

            l_curr->setText(QString::number(curr_drawNum));

            Timer->start(int(((timer_range * 10 - 20) / (double(curr_drawNum) + 10) + 2) * 10));

            //unlock signals
            this->restart->setEnabled(true);
            this->setting->setEnabled(true);
            this->help->setEnabled(true);
        }
    });
}

MainWindow::~MainWindow()
{
    delete[] piece;
}

void MainWindow::InitMedia()
{
    this->sound_clicked   =  new QMediaPlayer;
    this->sound_draw      =  new QMediaPlayer;
    this->icon_o          =  new QIcon(":/assets/image/o.png");
    this->icon_x          =  new QIcon(":/assets/image/x.png");
    this->icon_restart    =  new QIcon(":/assets/image/restart.png");
    this->icon_setting    =  new QIcon(":/assets/image/setting.png");
    this->icon_help       =  new QIcon(":/assets/image/help.png");
    this->pix_3x3         =  new QPixmap(":/assets/image/mode_3x3.png");
    this->pix_5x5         =  new QPixmap(":/assets/image/mode_5x5.png");
    this->pix_stop        =  new QPixmap(":/assets/image/stop.png");
    this->pix_allow       =  new QPixmap(":/assets/image/allow.png");
    this->pix_loading     =  new QPixmap(":/assets/image/loading.png");
    this->pix_logo_text   =  new QPixmap(":/assets/image/logo_text.png");
    this->pix_logo        =  new QPixmap(":/assets/image/logo.png");
    this->_0020_ = new QPixmap(":/assets/image/0-0,2-0.png");
    this->_0121_ = new QPixmap(":/assets/image/0-1,2-1.png");
    this->_0222_ = new QPixmap(":/assets/image/0-2,2-2.png");
    this->_0002_ = new QPixmap(":/assets/image/0-0,0-2.png");
    this->_1012_ = new QPixmap(":/assets/image/1-0,1-2.png");
    this->_2022_ = new QPixmap(":/assets/image/2-0,2-2.png");
    this->_0022_ = new QPixmap(":/assets/image/0-0,2-2.png");
    this->_2002_ = new QPixmap(":/assets/image/2-0,0-2.png");
    this->sound_clicked->setMedia(QUrl("qrc:/assets/sounds/clicked.wav"));
    this->sound_clicked->setVolume(100);
    this->sound_draw->setMedia(QUrl("qrc:/assets/sounds/draw.wav"));
    this->sound_draw->setVolume(50);
}

void MainWindow::InitGUI()
{
    this->setFixedSize(width, height);
    this->setStyleSheet("MainWindow {background-color: #ffffff;}");

    this->l_logo_text = new QLabel(this);
    this->l_logo_text->setFixedSize(width * 2 / 5, (width * 2 / 5) / 4);
    this->l_logo_text->setPixmap(*pix_logo_text);
    this->l_logo_text->setScaledContents(true);
    this->l_logo_text->move((width / 2) - (width * 0.45), (height / 2) - (width * 0.45) - 250);
    this->counter = new QToolBar(this);
    this->counter->setFixedSize(width * 0.45, 200);
    this->counter->setMovable(false);
    this->counter->setContextMenuPolicy(Qt::PreventContextMenu);
    this->counter->move(width * 0.5, (height / 2) - (width * 0.45) - 300);
    this->counter->setStyleSheet("QToolBar {background-color: #f5f5f5;}"
                                 "QToolBar::separator {width: 3px;}"
                                 "QToolBar::separator {background-color: #c1c1c1;}");
    QWidget *s_1 = new QWidget, *s_2 = new QWidget, *s_3 = new QWidget, *s_4 = new QWidget;
    s_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    s_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    s_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    s_4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QFont *font_t = new QFont;
    font_t->setFamily("Arial");
    font_t->setPointSize(25);
    font_t->setBold(true);
    this->l_curr = new QLabel();
    this->l_curr->setFont(*font_t);
    this->l_curr->setText("0");
    this->l_curr->setStyleSheet("QLabel {color: #5f5f5f;}");
    this->l_best = new QLabel();
    this->l_best->setFont(*font_t);
    this->l_best->setText("0");
    this->l_best->setStyleSheet("QLabel {color: #5f5f5f;}");
    this->counter->addWidget(s_1);
    this->counter->addWidget(l_curr);
    this->counter->addWidget(s_2);
    this->counter->addSeparator();
    this->counter->addWidget(s_3);
    this->counter->addWidget(l_best);
    this->counter->addWidget(s_4);


    this->toolBar = new QToolBar(this);
    this->toolBar->setFixedSize(width * 0.9, 200);
    this->toolBar->setMovable(false);
    this->toolBar->setContextMenuPolicy(Qt::PreventContextMenu);
    this->toolBar->move((width / 2) - (width * 0.45), (height / 2) - (width * 0.45));
    this->toolBar->setStyleSheet("QToolBar {background-color: #e1e1e1;}"
                                 "QToolBar::separator {width: 3px;}"
                                 "QToolBar::separator {background-color: #c1c1c1;}");

    QWidget *spacer_1 = new QWidget(), *spacer_2 = new QWidget(), *spacer_3 = new QWidget(), *spacer_4 = new QWidget(),
            *spacer_5 = new QWidget(), *spacer_6 = new QWidget();
    spacer_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    restart = new QPushButton;
    restart->setFixedSize(200, 200);
    restart->setIcon(*icon_restart);
    restart->setIconSize(QSize(128, 128));
    restart->setStyleSheet("QPushButton {border-image: url(:/assets/image/piece.png);}");
    setting  = new QPushButton;
    setting->setFixedSize(200, 200);
    setting->setIcon(*icon_setting);
    setting->setIconSize(QSize(128, 128));
    setting->setStyleSheet("QPushButton {border-image: url(:/assets/image/piece.png);}");
    help    = new QPushButton;
    help->setFixedSize(200, 200);
    help->setIcon(*icon_help);
    help->setIconSize(QSize(128, 128));
    help->setStyleSheet("QPushButton {border-image: url(:/assets/image/piece.png);}");
    this->toolBar->addWidget(spacer_1);
    this->toolBar->addWidget(setting);
    this->toolBar->addWidget(spacer_2);
    this->toolBar->addSeparator();
    this->toolBar->addWidget(spacer_3);
    this->toolBar->addWidget(restart);
    this->toolBar->addWidget(spacer_4);
    this->toolBar->addSeparator();
    this->toolBar->addWidget(spacer_5);
    this->toolBar->addWidget(help);
    this->toolBar->addWidget(spacer_6);

    this->pgBar = new QProgressBar(this);
    this->pgBar->setValue(0);
    this->pgBar->setFixedSize(width * 0.9, 10);
    this->pgBar->setTextVisible(false);
    this->pgBar->move((width / 2) - (width * 0.45), (height / 2) - (width * 0.45) + 200);
    this->pgBar->setStyleSheet("QProgressBar {border: 0px; /*border-radius: 5px;*/ background-color: #f1f1f1;}"
                               "QProgressBar::chunk {background-color: #c1c1c1;}");

    this->checkerboard = new QWidget(this);
    this->checkerboard->setFixedSize(width * 0.9, width * 0.9);
    this->checkerboard->move((width / 2) - (width * 0.45), (height / 2) - (width * 0.45) + 210);
    this->checkerboard->setStyleSheet("QWidget {border-image: url(:/assets/image/checkerboard.png);}");
    this->checkerboard_cover = new QLabel(this);
    this->checkerboard_cover->setFixedSize(width * 0.9, width * 0.9);
    this->checkerboard_cover->move((width / 2) - (width * 0.45), (height / 2) - (width * 0.45) + 210);
    this->checkerboard_cover->setScaledContents(true);
    this->checkerboard_cover->setVisible(false);
}

void MainWindow::InitPiece()
{
    this->piece = new QPushButton[pieceScale * pieceScale];                                      //piece to place
    for(int i = 0, x = 0, y = 0; i < (pieceScale * pieceScale); i++)
    {
        x = i % pieceScale;
        y = i / pieceScale;
        piece[i].setParent(checkerboard);
        piece[i].setFixedSize(pieceSize, pieceSize);
        piece[i].setStyleSheet("QPushButton {border-image: url(:/assets/image/piece.png);}");
        piece[i].move(x * pieceSize, y * pieceSize);

        connect(&piece[i], &QPushButton::clicked, this, &MainWindow::Operation);
//        connect(&piece[i], &QPushButton::pressed, [this](){emit gi_loading();});
//        connect(&piece[i], &QPushButton::released, [this](){emit gi_allow();});
    }
}

void MainWindow::InitGame()
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    Timer      = new QTimer;
    pgb_clean  = new QTimer;

    switch_side = false;
    finish = 0;
    progress = 0;

    curr_drawNum = 0;
    record_drawNum = 0;
    timer_range = 5;
    isMute = false;
    isSwitch = true;
}

void MainWindow::InitBox()
{
    msg           =  new QWidget(this);
    l_msg         =  new QLabel(msg);
    m_restart     =  new QPushButton(msg);
    m_exit        =  new QPushButton(msg);
    opacityEffect =  new QGraphicsOpacityEffect(msg);
    opacityEffect->setOpacity(0);
    msg->setGraphicsEffect(opacityEffect); //这一步很关键

    msg->setFixedSize(width * 0.6, width * 0.4);
    msg->move(width / 2 - (width * 0.6 / 2), height / 2 - (width * 0.4 / 2));
    msg->setStyleSheet("QWidget {background-color: #f5f5f5;}");
    msg->close();
    temp_p = new QPoint;
    *temp_p = msg->pos();

    QFont *font_m = new QFont;
    font_m->setFamily("Arial");
    font_m->setPointSize(18);
    l_msg->setText("NEW RECORD:");
    l_msg->setFont(*font_m);
    l_msg->setFixedSize(600, 200);
    l_msg->move((msg->width() / 2) - (l_msg->width() / 2), (msg->height() * 4 / 10) - (l_msg->height() / 2));
    l_msg->setAlignment(Qt::AlignHCenter);
    l_msg->setStyleSheet("QLabel {color: #5f5f5f;}");

    m_restart->move((msg->width() * 1 / 3) - 64, (msg->height() * 7 / 10) - 64);
    m_restart->setStyleSheet("QPushButton {width: 128px; height: 128px;}"
                             "QPushButton {border-image: url(:/assets/image/restart.png); background-position:center;}");
    m_exit->move((msg->width() * 2 / 3) - 64, (msg->height() * 7 / 10) - 64);
    m_exit->setStyleSheet("QPushButton {width: 128px; height: 128px;}"
                          "QPushButton {border-image: url(:/assets/image/exit.png); background-position:center;}");

    connect(m_restart, &QPushButton::clicked, [this]()
    {
        Again(true);
        CloseBox();
    });

    connect(m_exit, &QPushButton::clicked, [this]()
    {
        CloseBox();
    });
}

void MainWindow::Operation()
{
    if(curr_drawNum == 0)
        Timer->start(timer_range * 10);

    //click bonus
    progress -= 3;
    pgBar->setValue(progress);

    QPushButton *temp = (QPushButton*)sender();
    if((temp->objectName() != "o") && (temp->objectName() != "x"))
    {
        if(switch_side)
        {
            temp->setObjectName("x");
            temp->setIcon(*icon_x);
        }
        else
        {
            temp->setObjectName("o");
            temp->setIcon(*icon_o);
        }
        temp->setIconSize(QSize(pieceSize * 0.6, pieceSize * 0.6));
        if(!isMute)
            this->sound_clicked->play();
        finish++;
        if(this->Check())
            this->AnalysedGo();
    }
}

void MainWindow::RandomGo()
{
    int temp;
    bool rand_finish = false;

    while(!rand_finish)
    {
        temp = qrand() % 9;
        if(piece[temp].objectName() != "o" && piece[temp].objectName() != "x")
        {
            if(switch_side)
            {
                piece[temp].setObjectName("o");
                piece[temp].setIcon(*icon_o);
            }
            else
            {
                piece[temp].setObjectName("x");
                piece[temp].setIcon(*icon_x);
            }
            piece[temp].setIconSize(QSize(pieceSize * 0.6, pieceSize * 0.6));
            rand_finish = true;
        }
    }
    finish++;
    this->Check();
}

void MainWindow::AnalysedGo()
{
    int go[9] = { 0 }, target = 0, temp, priority_max[9] = { 0 };
    bool isSingle = true;

    for(int i = 0; i < 9; i++) //获取优先级
    {
        if(piece[i].objectName() == "o" || piece[i].objectName() == "x")
            continue;
        go[i] = GetPriority(i);
        go[i]++;
    }

    /**=====优先级修正=====**/

    //补充，后手下棋如果对方先手下中间那么只能下四角
    if((finish == 1) && (!switch_side) && piece[4].objectName() == "o")
    {
        go[0]++; go[2]++; go[6]++; go[8]++;
    }

    //补充，后手或先手第二步尽量填在中间
    if((((finish == 2) && (switch_side)) || ((finish == 1) && (!switch_side))) && piece[4].objectName() == 0)
        go[4]++;

    //补充，后手且对方下对角我方下中间，剩下俩对角一定不能填
    if((finish == 3) && (!switch_side) && ((piece[0].objectName() == piece[8].objectName() && piece[0].objectName() != 0 )||
                                           (piece[2].objectName() == piece[6].objectName() && piece[2].objectName() != 0 )))
    {
        go[1] += 40; go[3] += 40; go[5] += 40; go[7] += 40; //因为此时有两个点构成反双杀条件，所以优先级修正到40
    }

    //补充，后手且对方下中间和角，我方下其对角，构成对方占据4个双杀点，我方需要引导敌方放弃下双杀点而不是一味地填
    if((finish == 3) && (!switch_side) && piece[4].objectName() == "o" && ((piece[0].objectName() == "o" && piece[8].objectName() == "x")||
                                                                           (piece[8].objectName() == "o" && piece[0].objectName() == "x")||
                                                                           (piece[2].objectName() == "o" && piece[6].objectName() == "x")||
                                                                           (piece[6].objectName() == "o" && piece[2].objectName() == "x")))
    {
        go[1] -= 20; go[3] -= 20; go[5] -= 20; go[7] -= 20;
    }

    for(int i = 0; i < 9; i += 3)
    {
        qDebug() << go[i] << go[i+1] << go[i+2];
    }

    priority_max[0] = 1;
    for(int i = 1; i < 9; i++) //求最大优先级的位置和个数
    {
        if(go[i] > go[target])
        {
            target = i;
            memset(priority_max, 0, sizeof(priority_max));
            priority_max[i]++;
            isSingle = true;
        }
        else if(go[i] == go[target])
        {
            priority_max[i]++;
            isSingle = false;
        }
    }

    if(!isSingle) //考虑到可能优先级最大有数个，随机选一个
    {
        while (true)
        {
            temp = (qrand() % 9);
            if(priority_max[temp] == 0)
                continue;
            else
            {
                target = temp;
                break;
            }
        }
    }

    if(switch_side) //下棋
    {
        piece[target].setObjectName("o");
        piece[target].setIcon(*icon_o);
    }
    else
    {
        piece[target].setObjectName("x");
        piece[target].setIcon(*icon_x);
    }
    piece[target].setIconSize(QSize(pieceSize * 0.6, pieceSize * 0.6));

    finish++;
    this->Check();
}

int MainWindow::GetPriority(int next_move)
{
    int Checkerboard[3][3] = { {0} }, priority = 0, result = 0;

    for(int i = 0, x = 0, y = 0; i < 9; i++) //read pieces' states
    {
        x = i % 3;
        y = i / 3;
        if(!piece[i].objectName().compare("o"))
            Checkerboard[x][y] = 1;
        else if(!piece[i].objectName().compare("x"))
            Checkerboard[x][y] = 2;
    }

    //determine priority

    /**=====赢棋检测=====**/

    if(switch_side) //set next move's position
        Checkerboard[next_move % 3][next_move / 3] = 1;
    else
        Checkerboard[next_move % 3][next_move / 3] = 2;

    result = CheckerBoard(Checkerboard);

    if(switch_side) //能赢加100优先级，直接跳过双杀检测
    {
        if(result == 1)
            priority += 100;
    }
    else
    {
        if(result == 2)
            priority += 100;
    }
    result = 0;

    /**=====双杀检测=====**/

    if((finish <= 6) && (finish >= 3) && (priority < 100)) //完成度在可能出现双杀，且下一步未能直接赢棋的情况
    {
        for(int i = 0; i < 9; i++)
        {
            if(Checkerboard[i % 3][i / 3] != 0) //下(下下)一步的棋子
                continue;
            if(switch_side)
                Checkerboard[i % 3][i / 3] = 1;
            else
                Checkerboard[i % 3][i / 3] = 2;

            if(switch_side && CheckerBoard(Checkerboard) == 1)
                result++;
            else if(!switch_side && CheckerBoard(Checkerboard) == 2)
                result++;

            Checkerboard[i % 3][i / 3] = 0; //取消下棋操作
        }
        if(result >= 2) //双杀加30优先级
            priority += 30;
    }
    result = 0;

    /**=====反防检测=====**/

    if(Checkerboard[next_move % 3][next_move / 3] == 1) //switch view of side
        Checkerboard[next_move % 3][next_move / 3] = 2;
    else
        Checkerboard[next_move % 3][next_move / 3] = 1;

    result = CheckerBoard(Checkerboard);

    if(switch_side) //反防加60优先级
    {
        if(result == 2)
            priority += 60;
    }
    else
    {
        if(result == 1)
            priority += 60;
    }

    /**====反双杀检测=====**/

    if((finish <= 6) && (finish >= 3) && (priority < 60))
    {
        for(int i = 0; i < 9; i++)
        {
            if(Checkerboard[i % 3][i / 3] != 0) //下(下下)一步的棋子
                continue;
            if(switch_side)
                Checkerboard[i % 3][i / 3] = 2;
            else
                Checkerboard[i % 3][i / 3] = 1;

            if(!switch_side && CheckerBoard(Checkerboard) == 1)
                result++;
            else if(switch_side && CheckerBoard(Checkerboard) == 2)
                result++;

            Checkerboard[i % 3][i / 3] = 0; //取消下棋操作
        }
        if(result >= 2) //双杀加30优先级
            priority += 30;
    }

    return priority;
}

bool MainWindow::Check()
{
    int Checkerboard[3][3] = { {0} }, x = 0, y = 0, result = 0;

    for(int i = 0; i < 9; i++) //read pieces' states
    {
        x = i % 3;
        y = i / 3;
        if(!piece[i].objectName().compare("o"))
        {
            Checkerboard[x][y] = 1;
        }
        else if(!piece[i].objectName().compare("x"))
        {
            Checkerboard[x][y] = 2;
        }
    }

    result = CheckerBoard(Checkerboard);

    if((finish == 9) && (!result)) //reach step 9 but the result have not been concluded
        result = 3;

    if(result)
    {
        if((switch_side && result == 2) || (!switch_side && result == 1))
        {
            //GAMEOVER : CHEAT?
            Gameover();
        }
        else if((!switch_side && result == 2) || (switch_side && result == 1)) //game over
        {
            //GAMEOVER : LOST
            Gameover();
        }
        else
            Again_t();

        return false;
    }
    else
        return true;
}

int MainWindow::CheckerBoard(int Checkerboard[3][3]) //basic rule
{
    int result = 0;

    for(int i = 0; i < 3; i++) //check horizontal and vertical
    {
        for(int j = 0; j < 2; j++) //horizon
        {
            if(Checkerboard[j][i] == Checkerboard[j + 1][i] && Checkerboard[0][i])
            {
                if(j == 1)
                {
                    result = Checkerboard[0][i];
                    tripletPos[0][0] = 0;
                    tripletPos[0][1] = i;
                    tripletPos[1][0] = 2;
                    tripletPos[1][1] = i;
                }
            }
            else
                break;
        }
        if(result)
            break;
        for(int j = 0; j < 2; j++) //vertical
        {
            if(Checkerboard[i][j] == Checkerboard[i][j + 1] && Checkerboard[i][0])
            {
                if(j == 1)
                {
                    result = Checkerboard[i][0];
                    tripletPos[0][0] = i;
                    tripletPos[0][1] = 0;
                    tripletPos[1][0] = i;
                    tripletPos[1][1] = 2;
                }
            }
            else
                break;
        }
        if(result)
            break;
    }

    for(int i = 0; i < 2; i++) //diagonal
    {
        if(Checkerboard[i][i] == Checkerboard[i + 1][i + 1] && Checkerboard[0][0])
        {
            if(i == 1)
            {
                result = Checkerboard[0][0];
                tripletPos[0][0] = 0;
                tripletPos[0][1] = 0;
                tripletPos[1][0] = 2;
                tripletPos[1][1] = 2;
            }
        }
        else
            break;
    }

    for (int i = 0; i < 2; i++) //diagonal - another one
    {
        if(Checkerboard[3 - i - 1][i] == Checkerboard[3 - i - 2][i + 1] && Checkerboard[3 - i - 1][i])
        {
            if(i == 1)
            {
                result = Checkerboard[2][0];
                tripletPos[0][0] = 2;
                tripletPos[0][1] = 0;
                tripletPos[1][0] = 0;
                tripletPos[1][1] = 2;
            }
        }
        else
            break;
    }

    return result;
}

void MainWindow::Again_t()
{
    //tell mainwindow
    Timer->stop();
    curr_drawNum++;
    l_curr->setText(QString::number(curr_drawNum - 1) + "+" + "1");

    if(!isMute)
        this->sound_draw->play();
    //block signals
    this->restart->setEnabled(false);
    this->setting->setEnabled(false);
    this->help->setEnabled(false);
    pgb_clean->start(2);
}

void MainWindow::Again(bool isResetSide)
{
    //reset pgb
    Timer->stop();
    curr_drawNum = 0;
    l_curr->setText("0");
    progress = 0;
    pgBar->setValue(progress);

    //clean and enable the table
    for (int i = 0; i < 9; i++)
    {
        piece[i].setObjectName(0);
        piece[i].setIcon(icon_temp);
        piece[i].setEnabled(true);
    }
    finish = 0;

    checkerboard_cover->setPixmap(pix_temp);
    checkerboard_cover->setVisible(false);
    update();

    //next round start
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    if(!isResetSide)
    {
        if(switch_side)
            switch_side = false;
        else if(!switch_side)
        {
            switch_side = true;
            RandomGo();
        }
    }
    else
        switch_side = false;
}

void MainWindow::Gameover(bool isPaintLine)
{
    Timer->stop();

    //disable the table & toolbar
    for (int i = 0; i < 9; i++)
    {
        piece[i].setEnabled(false);
    }

    //draw the line
    if(isPaintLine)
    {
        if((tripletPos[0][0] == 0 && tripletPos[0][1] == 0 && tripletPos[1][0] == 2 && tripletPos[1][1] == 0 )||
           (tripletPos[0][0] == 2 && tripletPos[0][1] == 0 && tripletPos[1][0] == 0 && tripletPos[1][1] == 0 ))
            checkerboard_cover->setPixmap(*_0020_);
        else if((tripletPos[0][0] == 0 && tripletPos[0][1] == 1 && tripletPos[1][0] == 2 && tripletPos[1][1] == 1 )||
                (tripletPos[0][0] == 2 && tripletPos[0][1] == 1 && tripletPos[1][0] == 0 && tripletPos[1][1] == 1 ))
            checkerboard_cover->setPixmap(*_0121_);
        else if((tripletPos[0][0] == 0 && tripletPos[0][1] == 2 && tripletPos[1][0] == 2 && tripletPos[1][1] == 2 )||
                (tripletPos[0][0] == 2 && tripletPos[0][1] == 2 && tripletPos[1][0] == 0 && tripletPos[1][1] == 2 ))
            checkerboard_cover->setPixmap(*_0222_);
        else if((tripletPos[0][0] == 0 && tripletPos[0][1] == 0 && tripletPos[1][0] == 0 && tripletPos[1][1] == 2 )||
                (tripletPos[0][0] == 0 && tripletPos[0][1] == 2 && tripletPos[1][0] == 0 && tripletPos[1][1] == 0 ))
            checkerboard_cover->setPixmap(*_0002_);
        else if((tripletPos[0][0] == 1 && tripletPos[0][1] == 0 && tripletPos[1][0] == 1 && tripletPos[1][1] == 2 )||
                (tripletPos[0][0] == 1 && tripletPos[0][1] == 2 && tripletPos[1][0] == 1 && tripletPos[1][1] == 0 ))
            checkerboard_cover->setPixmap(*_1012_);
        else if((tripletPos[0][0] == 2 && tripletPos[0][1] == 0 && tripletPos[1][0] == 2 && tripletPos[1][1] == 2 )||
                (tripletPos[0][0] == 2 && tripletPos[0][1] == 2 && tripletPos[1][0] == 2 && tripletPos[1][1] == 0 ))
            checkerboard_cover->setPixmap(*_2022_);
        else if((tripletPos[0][0] == 0 && tripletPos[0][1] == 0 && tripletPos[1][0] == 2 && tripletPos[1][1] == 2 )||
                (tripletPos[0][0] == 2 && tripletPos[0][1] == 2 && tripletPos[1][0] == 0 && tripletPos[1][1] == 0 ))
            checkerboard_cover->setPixmap(*_0022_);
        else if((tripletPos[0][0] == 2 && tripletPos[0][1] == 0 && tripletPos[1][0] == 0 && tripletPos[1][1] == 2 )||
                (tripletPos[0][0] == 0 && tripletPos[0][1] == 2 && tripletPos[1][0] == 2 && tripletPos[1][1] == 0 ))
            checkerboard_cover->setPixmap(*_2002_);
        checkerboard_cover->setVisible(true);
        update();
    }

    if(curr_drawNum > record_drawNum)
    {
        l_msg->setText("NEW RECORD: " + QString::number(curr_drawNum));
        record_drawNum = curr_drawNum;
        l_curr->setText("0");
        l_best->setText(QString::number(record_drawNum));
        emit record_changed();
        ShowBox();
    }
}

void MainWindow::ShowBox()
{
    //block signals
    this->restart->setEnabled(false);
    this->setting->setEnabled(false);
    this->help->setEnabled(false);

    //animate
    opacity = new QPropertyAnimation(opacityEffect, "opacity");
    opacity->setDuration(800);
    opacity->setStartValue(0);
    opacity->setEndValue(1);
    opacity->setEasingCurve(QEasingCurve::OutQuint);
    movement = new QPropertyAnimation(msg, "pos");
    movement->setDuration(800);
    movement->setStartValue(QPoint(temp_p->x(), temp_p->y() + 200));
    movement->setEndValue(*temp_p);
    movement->setEasingCurve(QEasingCurve::OutQuint);
    msg->show();
    opacity->start(QAbstractAnimation::DeleteWhenStopped);
    movement->start(QAbstractAnimation::DeleteWhenStopped);
    connect(opacity, &QPropertyAnimation::valueChanged, [this](){msg->setGraphicsEffect(opacityEffect);});
}

void MainWindow::CloseBox()
{
    //unlock signals
    this->restart->setEnabled(true);
    this->setting->setEnabled(true);
    this->help->setEnabled(true);

    //animate
    opacity = new QPropertyAnimation(opacityEffect, "opacity");
    opacity->setDuration(800);
    opacity->setStartValue(1);
    opacity->setEndValue(0);
    opacity->setEasingCurve(QEasingCurve::OutQuint);
    movement = new QPropertyAnimation(msg, "pos");
    movement->setDuration(800);
    movement->setStartValue(*temp_p);
    movement->setEndValue(QPoint(temp_p->x(), temp_p->y() + 200));
    movement->setEasingCurve(QEasingCurve::OutQuint);
    opacity->start();
    movement->start(QAbstractAnimation::DeleteWhenStopped);

    connect(opacity, &QPropertyAnimation::valueChanged, [this](){msg->setGraphicsEffect(opacityEffect);});
    connect(opacity, &QAbstractAnimation::finished, [this](){delete opacity; msg->close();});
}

void MainWindow::TimerControl(const QString &cmd)
{
    if(cmd == "pause")
    {
        if(Timer->isActive())
        {
            Timer->stop();
            switch_dir = 1;
        }
        else if(pgb_clean->isActive())
        {
            pgb_clean->stop();
            switch_dir = 2;
        }
    }
    else if(cmd == "continue")
    {
        switch(switch_dir)
        {
        case 1:
            Timer->start(); break;
        case 2:
            pgb_clean->start(); break;
        default:
            break;
        }
        switch_dir = 0;
    }
}

//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    if(isToPaint)
//    {
//        painter->drawLine(checkerboard->x() + width * 0.05 + tripletPos[0][0] * width * 0.4,
//                          checkerboard->y() + width * 0.05 + tripletPos[0][1] * width * 0.4,
//                          checkerboard->x() + width * 0.05 + tripletPos[1][0] * width * 0.4,
//                          checkerboard->y() + width * 0.05 + tripletPos[1][1] * width * 0.4);
//        qDebug() << "PAIINTING OPERATION FINISHED";
//    }
//}
