TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    baseinterface.cpp \
    primBinTreeDGPP.cpp \
    primSimpleDGPP.cpp \
    primBinTreeVSSS.cpp \
    primSimpleVSSS.cpp \
    primSimpleVKB.cpp \
    primBinTreeVKB.cpp

HEADERS += \
    baseinterface.h \
    primBinTreeDGPP.h \
    primSimpleDGPP.h \
    primBinTreeVSSS.h \
    primSimpleVSSS.h \
    primUnknownV.h \
    primBinTreeV.h \
    primSimpleVKB.h \
    primBinTreeVKB.h
