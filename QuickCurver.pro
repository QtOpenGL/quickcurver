TEMPLATE = app

QT += qml quick opengl
CONFIG += c++11

SOURCES += src/curveitem.cpp \
src/dieanimation.cpp \
src/fastitem.cpp \
src/game.cpp \
src/graphnode.cpp \
src/headnode.cpp \
src/main.cpp \
src/qcurver.cpp \
src/segment.cpp \
src/slowitem.cpp \
src/wallnode.cpp \
    src/aicontroller.cpp \
    src/cleaninstallitem.cpp


RESOURCES += \
    src/qml/qml.qrc \
    icons/icons.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += src/curveitem.h \
src/dieanimation.h \
src/fastitem.h \
src/game.h \
src/graphnode.h \
src/headnode.h \
src/qcurver.h \
src/segment.h \
src/slowitem.h \
src/wallnode.h \
    src/aicontroller.h \
    src/cleaninstallitem.h