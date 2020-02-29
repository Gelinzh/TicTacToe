#ifndef MENU_ABOUT_H
#define MENU_ABOUT_H

#include <QLabel>
#include <QPushButton>
#include <QLayout>
#include <QToolBar>

#include <QDesktopServices>
#include <QUrl>

class Menu_ABOUT : public QWidget
{
    Q_OBJECT
public:
    explicit Menu_ABOUT(int &rwidth, int &rheight, QWidget *parent = nullptr);

    int width, height;

    void InitMedia();
    void InitGUI();

    QToolBar *about_title_bar;
    QLabel *about_title;
    QPushButton *back;

    QWidget *info;
    QHBoxLayout *hLayout;
    QVBoxLayout *vLayout;
    QLabel *l_logo, *l_title, *l_date, *l_author;

    QToolBar *tb_link;
    QPushButton *b_github, *b_bili;


    QIcon *arrow_l;
    QPixmap *logo;

signals:
    void switch_back();
};

#endif // MENU_ABOUT_H
