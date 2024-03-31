QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    addcontact.cpp \
    addinteraction.cpp \
    bdd.cpp \
    contact.cpp \
    displaycontact.cpp \
    editcontact.cpp \
    gestioncontact.cpp \
    gestioninteraction.cpp \
    gestiontodo.cpp \
    interactions.cpp \
    main.cpp \
    mainwindow.cpp \
    searchcontact.cpp \
    todo.cpp

HEADERS += \
    addcontact.h \
    addinteraction.h \
    bdd.h \
    contact.h \
    displaycontact.h \
    editcontact.h \
    gestioncontact.h \
    gestioninteraction.h \
    gestiontodo.h \
    interactions.h \
    mainwindow.h \
    searchcontact.h \
    todo.h

FORMS += \
    addcontact.ui \
    addinteraction.ui \
    displaycontact.ui \
    editcontact.ui \
    mainwindow.ui \
    searchcontact.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
