#ifndef MENU_OPTION_H
#define MENU_OPTION_H

#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QToolBar>
#include <QSlider>
#include <QCheckBox>

class Menu_OPTION : public QWidget
{
    Q_OBJECT
public:
    explicit Menu_OPTION(int &rwidth, int &rheight, QWidget *parent = nullptr);

    int width, height;

    void InitMedia();
    void InitGUI();

    QToolBar *option_title_bar;
    QLabel *option_title;
    QPushButton *back;

    QToolBar *tb_time, *tb_volume, *tb_switch;
    QLabel *l_time, *l_volume, *l_switch;
    QSlider *time_slider;
    QCheckBox *volume_checkbox;
    QCheckBox *switch_checkbox;

    QIcon *arrow_r;
    QPixmap *pix_timer, *pix_volume, *pix_volume_down, *pix_switch;

signals:
    void switch_back();

    void timer_changed();
    void volume_changed();
    void switch_changed();
};

#endif // MENU_OPTION_H
