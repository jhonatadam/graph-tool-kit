TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

LIBS += -lboost_fiber -lboost_context

SOURCES += \
        digraph.cpp \
        graph.cpp \
        main.cpp \
        path/dijkstra.cpp \
        search/depth_girst_search.cpp \
        search/search.cpp \
        shortest_path.cpp

HEADERS += \
    digraph.h \
    graph.h \
    path/dijkstra.h \
    search/depth_first_search.h \
    search/search.h \
    shortest_path.h \
    type_definitions.h
