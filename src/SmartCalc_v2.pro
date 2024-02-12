QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller/controller.cpp \
    Model/bonusmodel.cpp \
    Model/model.cpp \
    View/button.cpp \
    View/credit.cpp \
    View/deposit.cpp \
    View/graphic.cpp \
    View/mainwindow.cpp \
    View/qcustomplot.cpp \
    View/replenishments.cpp \
    View/withdrawals.cpp \
    main.cpp \

HEADERS += \
    Controller/controller.h \
    Model/bonusmodel.h \
    Model/model.h \
    View/button.h \
    View/credit.h \
    View/deposit.h \
    View/graphic.h \
    View/mainwindow.h \
    View/qcustomplot.h \
    View/replenishments.h \
    View/withdrawals.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
