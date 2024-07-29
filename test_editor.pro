QT       += core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    about_test.cpp \
    change_test.cpp \
    dialog.cpp \
    main.cpp \
    mainwindow.cpp \
    make_test.cpp

HEADERS += \
    about_test.h \
    change_test.h \
    dialog.h \
    mainwindow.h \
    make_test.h

FORMS += \
    about_test.ui \
    change_test.ui \
    dialog.ui \
    mainwindow.ui \
    make_test.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
