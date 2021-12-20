TEMPLATE = app
CONFIG += console c++2x
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_fiber -lboost_context

SOURCES += \
        main.cpp

HEADERS += \
    digraph.h \
    graph.h \
    shortest_path.h \
    type_definitions.h
