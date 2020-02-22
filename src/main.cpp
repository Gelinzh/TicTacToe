#include "pvpwidget_3x3.h"
#include "pvewidget_3x3.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PVEWidget_3x3 w;
    w.show();
    return a.exec();
}
