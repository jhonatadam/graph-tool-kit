TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_fiber -lboost_context

SOURCES += \
        digraph.cpp \
        main.cpp \
        shortest_path.cpp

HEADERS += \
    digraph.h \
    graph.h \
    shortest_path.h \
    type_definitions.h
