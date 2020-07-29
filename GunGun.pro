TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Unit/cannon.cpp \
        Unit/cannonball.cpp \
        Unit/enemy.cpp \
        Unit/weapon.cpp \
        core.cpp \
        main.cpp \
        mixer.cpp \
        score.cpp

LIBS += -L$$PWD/../../libs/SDL2-2.0.12/x86_64-w64-mingw32/lib/ -lmingw32 -lSDL2main -lSDL2
INCLUDEPATH += $$PWD/../../libs/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2
DEPENDPATH += $$PWD/../../libs/SDL2-2.0.12/x86_64-w64-mingw32/include/SDL2


LIBS += -LC:/Goose/libs/SDL2-2/bin -lSDL2_image
INCLUDEPATH += C:/Goose/libs/SDL2-2/include

LIBS += -LC:/Goose/libs/SDL2_ttf-2.0.15/x86_64-w64-mingw32/bin -lSDL2_ttf
INCLUDEPATH += C:/Goose\libs/SDL2_ttf-2.0.15/x86_64-w64-mingw32/include

LIBS += -LC:/Goose/libs/SDL2_mixer-2.0.4/x86_64-w64-mingw32/bin -lSDL2_mixer
INCLUDEPATH += C:/Goose/libs/SDL2_mixer-2.0.4/x86_64-w64-mingw32/include

HEADERS += \
    Unit/cannon.h \
    Unit/cannonball.h \
    Unit/enemy.h \
    Unit/unit.h \
    Unit/weapon.h \
    core.h \
    mixer.h \
    score.h
