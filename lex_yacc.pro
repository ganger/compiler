#-------------------------------------------------
#
# Project created by QtCreator 2014-03-14T19:26:37
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = lex_yacc
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    lex.cpp \
    yacc.cpp \
    code.cpp

HEADERS  += mainwindow.h \
    lex.h \
    yacc.h \
    code.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    doc.txt \
    table.txt
