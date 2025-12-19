QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# Define output directories
DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build

# Source files
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    graph_logic.cpp

# Header files
HEADERS += \
    mainwindow.h \
    graph_logic.h
