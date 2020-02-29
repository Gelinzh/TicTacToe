#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QPropertyAnimation>
#include <QtMultimedia/QMediaPlayer>
#include <QLabel>
#include <QLayout>
#include <QToolBar>

#include <QTime>
#include <QTimer>
#include <QProgressBar>

#include <QDebug>
#include <QDesktopWidget>
#include <QGraphicsOpacityEffect>

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(int &width, int &height, QWidget *parent = nullptr);
    ~MainWindow();

    void InitMedia();
    void InitGUI();
    void InitPiece();
    void InitGame();
    void InitBox();

    void Operation();

    //algorithm part
    void RandomGo();
    void AnalysedGo();
    int GetPriority(int next_move);

    bool Check();
    int CheckerBoard(int Checkerboard[3][3]);
    void Again_t();
    void Again(bool isResetSide = true);
    void Gameover(bool isPaintLine = true);

    void ShowBox();
    void CloseBox();

    void TimerControl(const QString &cmd);

    int width, height;
    int curr_drawNum, record_drawNum;
    int timer_range;
    bool isMute, isSwitch;

    //Elements title & counter
    QLabel *l_logo_text, *l_curr, *l_best;
    QToolBar *counter;
    QWidget *w_curr, *w_best;

    //Elements tool bar
    QToolBar *toolBar;
    QPushButton *restart, *setting, *help;
    QLabel *l_state;

    //Element pg bar
    QTimer *Timer, *pgb_clean;
    QProgressBar *pgBar;
    int progress;
    int switch_dir;

    //Element c board
    QPushButton *piece;
    QWidget *checkerboard;
    QLabel *checkerboard_cover;
    int pieceScale, pieceSize;
    int finish;
    bool switch_side;
    int tripletPos[2][2] = { {0} };

    //Element box
    QWidget *msg;
    QLabel *l_msg;
    QPushButton *m_restart, *m_exit;
    QPropertyAnimation *movement, *opacity;
    QGraphicsOpacityEffect *opacityEffect;
    QPoint *temp_p;

    QMediaPlayer *sound_clicked, *sound_draw, sound_temp;

private:
    QIcon *icon_x, *icon_o, *icon_restart, *icon_setting, *icon_help, icon_temp;
    QPixmap *pix_stop, *pix_allow, *pix_loading, *pix_3x3, *pix_5x5, *pix_logo_text, *pix_logo, pix_temp;
    QPixmap *_0020_, *_0121_, *_0222_, *_0002_, *_1012_, *_2022_, *_0022_, *_2002_;

signals:
    void switch_option();
    void switch_about();

    void record_changed();
};
#endif // MAINWINDOW_H
