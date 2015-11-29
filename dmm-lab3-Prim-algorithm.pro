TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle

CONFIG += c++11

SOURCES += main.cpp \
    baseinterface.cpp \
    primBinTreeDGPP.cpp \
    primSimpleDGPP.cpp \
    primBinTreeVSSS.cpp \
    primSimpleVSSS.cpp \
    primUnknownV.cpp \
    primBinTreeV.cpp

HEADERS += \
    baseinterface.h \
    primBinTreeDGPP.h \
    primSimpleDGPP.h \
    primBinTreeVSSS.h \
    primSimpleVSSS.h \
    primUnknownV.h \
    primBinTreeV.h
