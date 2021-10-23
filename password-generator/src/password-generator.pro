QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

RC_ICONS = icon.ico

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    focusablelineedit.cpp \
    licensedialog.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    focusablelineedit.h \
    licensedialog.h \
    mainwindow.h

FORMS += \
    licensedialog.ui \
    mainwindow.ui

TRANSLATIONS += \
    password-generator_en_US.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
