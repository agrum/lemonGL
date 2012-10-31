TEMPLATE = lib
TARGET = lemonGL
QT += core \
    xml \
    opengl
INCLUDEPATH += /usr/include/GL
LIBS += -lGLEW \
    -lGLU \
    -lGL
DESTDIR = lib
HEADERS += src/CGL.h \
    src/mvp/CLight.h \
    src/mvp/CMVP.h \
    src/object/CFace.h \
    src/object/CMesh.h \
    src/object/CMeshMngr.h \
    src/object/CObject.h \
    src/object/CVA.h \
    src/shader/CProgram.h \
    src/texture/CMaterial.h \
    src/texture/CMaterialMngr.h \
    src/texture/CTexture.h
SOURCES += src/mvp/CLight.cpp \
    src/mvp/CMVP.cpp \
    src/object/CFace.cpp \
    src/object/CMesh.cpp \
    src/object/CMeshMngr.cpp \
    src/object/CObject.cpp \
    src/object/CVA.cpp \
    src/shader/CProgram.cpp \
    src/texture/CMaterial.cpp \
    src/texture/CMaterialMngr.cpp \
    src/texture/CTexture.cpp
FORMS += 
RESOURCES += 
