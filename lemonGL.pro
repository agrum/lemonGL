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
HEADERS += src/CLemonGL.h \
    src/log/CGLString.h \
    src/texture/CTexture3D.h \
    src/texture/CTexture2D.h \
    src/texture/CTexture1D.h \
    src/log/CLogString.h \
    src/log/CLog.h \
    include/lemonGL.h \
    src/CGL.h \
    src/mvp/CLight.h \
    src/mvp/CMVP.h \
    src/object/CFace.h \
    src/object/CMesh.h \
    src/object/CMeshMngr.h \
    src/object/CObject.h \
    src/object/CVA.h \
    src/texture/CMaterial.h \
    src/texture/CMaterialMngr.h \
    src/texture/CTexture.h \
    src/shader/CShaderInterface.h
SOURCES += src/log/CGLString.cpp \
    src/texture/CTexture3D.cpp \
    src/texture/CTexture2D.cpp \
    src/texture/CTexture1D.cpp \
    src/log/CLog.cpp \
    src/mvp/CLight.cpp \
    src/mvp/CMVP.cpp \
    src/object/CFace.cpp \
    src/object/CMesh.cpp \
    src/object/CMeshMngr.cpp \
    src/object/CObject.cpp \
    src/object/CVA.cpp \
    src/texture/CMaterial.cpp \
    src/texture/CMaterialMngr.cpp \
    src/texture/CTexture.cpp \
    src/shader/CShaderInterface.cpp \
    src/CLemonGL.cpp
FORMS += 
RESOURCES += 

OTHER_FILES += \
    shaders/opaque.vs \
    shaders/opaque.fs \
    shaders/illumination.vs \
    shaders/illumination.fs
