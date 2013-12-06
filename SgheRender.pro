unix {
   CONFIG += link_pkgconfig
   PKGCONFIG += opencv
}

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    types/triangle.cpp \
    scene.cpp \
    camera.cpp \
    utils/printutils.cpp \
    types/sphere.cpp \
    imgplane.cpp

HEADERS += \
    types/StructDef.h \
    types/triangle.h \
    scene.h \
    camera.h \
    utils/printutils.h \
    types/sphere.h \
    imgplane.h

QMAKE_CXXFLAGS+= -fopenmp
QMAKE_LFLAGS +=  -fopenmp

