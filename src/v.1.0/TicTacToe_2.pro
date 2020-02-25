QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    custom.cpp \
    gameimple.cpp \
    helpmenu.cpp \
    main.cpp \
    mainwindow.cpp \
    normal_3.cpp \
    normal_5.cpp \
    optionmenu.cpp \
    random_3.cpp \
    random_5.cpp \
    timer_3.cpp

HEADERS += \
    custom.h \
    gameimple.h \
    helpmenu.h \
    mainwindow.h \
    normal_3.h \
    normal_5.h \
    optionmenu.h \
    random_3.h \
    random_5.h \
    timer_3.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RC_ICONS = icon.ico
