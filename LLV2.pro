TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    glad.c \
    window.cpp \
    glrender.cpp \
    chunk.cpp \
    chunkmanager.cpp \
    noiseutils.cpp \
    mesh.cpp

LIBS += -lglfw3 -lGL -lm -ldl -lXinerama -lXrandr -lXi -lXcursor -lX11 -lXxf86vm -lpthread -lnoise

INCLUDEPATH += ./include

HEADERS += \
    window.h \
    glrender.h \
    camera.h \
    shader.h \
    chunk.h \
    block.h \
    chunkmanager.h \
    noiseutils.h \
    mesh.h

DISTFILES += \
    shader.vert \
    shader.frag \
    light.vert \
    light.frag
