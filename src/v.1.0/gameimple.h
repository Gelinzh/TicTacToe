#ifndef GAMEIMPLE_H
#define GAMEIMPLE_H

#include <QWidget>
#include <QPushButton>
#include <QtMultimedia/QMediaPlayer>

class GameImple : public QWidget //create frame, pieces, media files and basic gamerule
{
    Q_OBJECT
public:
    explicit GameImple(int size, QWidget *parent = nullptr);
    ~GameImple();

    void InitPiece(int pieceScale);
    void InitMedia();
    void InitBox();

    virtual void Operation();
    virtual void Again(bool isResetSide = false);
    virtual void TimerControl(const QString &);

    //Element
    QIcon *icon_o, *icon_x, icon_temp;
    QMediaPlayer *sound_clicked, *sound_draw;
    int finish;

    QPushButton *piece;

    QPushButton *restart, *exit;
    QWidget *msg;

    //Timer
    int per, drawNum, drawNum_record;

signals:
    void gi_exit();
    void gi_allow();
    void gi_stop();
    void gi_loading();

    void timer_record();
    void timer_addDraw_start();
    void timer_addDraw_finish();
    void timer_askRecord();
};

#endif // GAMEIMPLE_H
