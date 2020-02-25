#ifndef HELPMENU_H
#define HELPMENU_H

#include <QPushButton>
#include <QLabel>
#include <QLayout>

#include <QCloseEvent>
#include <QDesktopServices>

class HelpMenu : public QWidget
{
    Q_OBJECT
public:
    explicit HelpMenu(QWidget *parent = nullptr);

    QVBoxLayout *vLayout;
    QHBoxLayout *hLayout, *bLayout;

    QLabel *l_logo, *l_projectName, *l_buildDate, *l_author;
    QPushButton *b_githubUrl, *b_biliUrl, *b_line;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void hm_close();

};

#endif // HELPMENU_H
