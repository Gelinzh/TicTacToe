#include "rootframe.h"

#include <QApplication>
#include <QScreen>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //get screen size
    QScreen *iScreen = a.primaryScreen();
    QSize rScreenSize = iScreen->size();
    RootFrame w(rScreenSize.rwidth(), rScreenSize.rheight());
    w.show();
    return a.exec();
}
