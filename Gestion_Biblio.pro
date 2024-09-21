QT       += core gui
QT += sql



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addloandialog.cpp \
    bookdialog.cpp \
    databasemanager.cpp \
    main.cpp \
    mainwindow.cpp \
    memberdialog.cpp

HEADERS += \
    addloandialog.h \
    bookdialog.h \
    databasemanager.h \
    mainwindow.h \
    memberdialog.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    Gestion_Biblio_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES += images.qrc


DISTFILES += \
    images/img1.jpg \
    images/img10.jpg \
    images/img11.jpg \
    images/img2.jpg \
    images/img3.png \
    images/img4.jpg \
    images/img5.jpg \
    images/img6.jpg \
    images/img7.jpg \
    images/img8.jpg \
    images/img9.jpg
