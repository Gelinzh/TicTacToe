#include "gameimple.h"

GameImple::GameImple(int size, QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(size * 100, size * 100);
    InitMedia();
    InitBox();
    InitPiece(size);
    finish = 0;
}

GameImple::~GameImple()
{
    delete[] piece;
}

void GameImple::InitPiece(int pieceScale)
{
    this->piece = new QPushButton[pieceScale * pieceScale];                                      //piece to place
    for(int i = 0, x = 0, y = 0; i < (pieceScale * pieceScale); i++)
    {
        x = i % pieceScale;
        y = i / pieceScale;
        piece[i].setParent(this);
        piece[i].setFixedSize(100, 100);
        piece[i].move(x * 100, y * 100);
        connect(&piece[i], &QPushButton::clicked, this, &GameImple::Operation);
        connect(&piece[i], &QPushButton::pressed, [this](){emit gi_loading();});
        connect(&piece[i], &QPushButton::released, [this](){emit gi_allow();});
    }
}

void GameImple::InitMedia()
{
    this->sound_clicked   =  new QMediaPlayer;
    this->sound_draw      =  new QMediaPlayer;
    this->icon_o          =  new QIcon("asset/image/o.png");
    this->icon_x          =  new QIcon("asset/image/x.png");
    this->sound_clicked->setMedia(QUrl("asset/sounds/clicked.wav"));
    this->sound_clicked->setVolume(100);
    this->sound_draw->setMedia(QUrl("asset/sounds/draw.wav"));
    this->sound_draw->setVolume(50);
}

void GameImple::InitBox()
{
    msg     =  new QWidget(this);
    restart =  new QPushButton(msg);
    exit    =  new QPushButton(msg);

    msg->setFixedSize(200, 100);
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowTitleHint;
    msg->setWindowFlags(flags);
    msg->setWindowModality(Qt::WindowModal);

    restart->move(30, 25);
    restart->setStyleSheet("QPushButton {width: 50px; height: 50px;}"
                           "QPushButton {border-image: url(asset/image/restart.png); background-position:center;}");
    exit->move(120, 25);
    exit->setStyleSheet("QPushButton {width: 50px; height: 50px;}"
                        "QPushButton {border-image: url(asset/image/exit.png); background-position:center;}");

    connect(restart, &QPushButton::clicked, [this]()
    {
        Again(true);
        msg->close();
    });

    connect(exit, &QPushButton::clicked, [this]()
    {
        emit gi_exit();
        msg->close();
    });
}

void GameImple::Operation()
{
    //rules here
}

void GameImple::Again(bool isResetSide)
{
    //again here
    qDebug() << isResetSide;
}

void GameImple::TimerControl(const QString &)
{
    //timer here
}
