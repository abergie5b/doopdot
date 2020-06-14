
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bin/doopdot-gui
TEMPLATE = app

SOURCES += src/gui/main.cpp\
  src/gui/mainwindow.cpp\
  src/algorithms/convolution.cpp\
  src/algorithms/filter.cpp\
  src/algorithms/histogram.cpp\
  src/algorithms/resize.cpp\
  src/algorithms/transform.cpp\
  src/common/image.cpp\
  src/common/jpeg.cpp\
  src/common/pgm.cpp

HEADERS += src/gui/mainwindow.h \
  src/algorithms/include/* \
  src/common/include/*

LIBS += -ljpeg

FORMS += src/gui/mainwindow.ui

CONFIG += c++14
QMAKE_CXXFLAGS += -Wall

