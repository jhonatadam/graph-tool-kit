#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <graph.h>
#include <digraph.h>
#include <limits>
#include <iostream>
namespace gtk {
template <class weight>
using distance_map = std::unordered_map<vertex, weight>;
using predecessor_map = std::unordered_map<vertex, vertex>;

template <class weight>
std::pair<distance_map<weight>*, predecessor_map*> initialize_single_source(
        const graph & g, const vertex & s) {
    distance_map<weight> * distance = new distance_map<weight>;
    predecessor_map * predecessor = new predecessor_map;

    for (const vertex & v : g.vertices())
        (*distance)[v] = std::numeric_limits<weight>::max();
    distance->at(s) = 0;

    return {distance, predecessor};
}

template  <class weight>
void relax(const vertex & u, const vertex & v, distance_map<weight> * distance,
           predecessor_map * predecessor, const gtk::edge_function<weight> & w) {
    // TODO quando soma vai para negativo
    if (distance->at(v) - w(u, v) > distance->at(u)) {
        distance->at(v) = distance->at(u) + w(u, v);
        (*predecessor)[v] = u;
    }
}

template <class weight>
std::pair<distance_map<weight>*, predecessor_map*> bellman_ford(
        const graph &g, const vertex& s, const gtk::edge_function<weight> & w) {
    auto [distance, predecessor] = initialize_single_source<weight>(g, s);
    for (size i = 1; i < g.number_of_vertices(); i++) {
        for (const auto & [u, v] : g.edges())
            relax(u, v, distance, predecessor, w);
//        for (auto [v, d] : *distance)
//            std::cout << v << ": " << d << ", ";
//        std::cout << i << std::endl;
    }
    for (const auto & [u, v] : g.edges()) {
        if (distance->at(v) - w(u, v)> distance->at(u) ) {
            delete distance;
            delete predecessor;
            return {nullptr, nullptr};
        }
    }
    return {distance, predecessor};
}


template <class weight>
std::pair<distance_map<weight>*, predecessor_map*> dijkstra(
        const graph &g, const vertex& s, const gtk::edge_function<weight> & w) {

}

}

#endif // SHORTEST_PATH_H
