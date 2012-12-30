TEMPLATE = app
CONFIG += console
CONFIG -= qt

SOURCES += main.cpp \
    token.cpp \
    rexpbuilder.cpp \
    expbuilder.cpp \
    ll1expbuilder.cpp

HEADERS += \
    token.h \
    rexpbuilder.h \
    expbuilder.h \
    ll1expbuilder.h

OTHER_FILES += \
    sample.txt

