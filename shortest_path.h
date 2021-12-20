#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include <graph.h>
#include <digraph.h>
#include <limits>
#include <iostream>
namespace gtk {
template <class weight, class vertex>
using distance_map = std::unordered_map<vertex, weight>;
template <class vertex>
using predecessor_map = std::unordered_map<vertex, vertex>;

template <class weight, class vertex_data, class vertex>
std::pair<distance_map<weight, vertex>*, predecessor_map<vertex>*> initialize_single_source(
        const graph<weight, vertex_data, vertex>& g, const vertex& s) {
    distance_map<weight, vertex> * distance = new distance_map<weight, vertex>;
    predecessor_map<vertex> * predecessor = new predecessor_map<vertex>;

    for (const vertex & v : g.vertices())
        (*distance)[v] = std::numeric_limits<weight>::max();
    distance->at(s) = 0;

    return {distance, predecessor};
}

template <class weight, class vertex_data, class vertex>
void relax(const graph<weight, vertex_data, vertex>& g, const vertex& u, const vertex& v,
           distance_map<weight, vertex> * distance, predecessor_map<vertex> * predecessor) {
    // TODO quando soma vai para negativo
    if (distance->at(v) - g.edge_data(u, v) > distance->at(u)) {
        distance->at(v) = distance->at(u) + g.edge_data(u, v);
        (*predecessor)[v] = u;
    }
}

template <class weight, class vertex_data, class vertex>
std::pair<distance_map<weight, vertex>*, predecessor_map<vertex>*> bellman_ford(const graph<weight, vertex_data, vertex>& g, const vertex& s) {
    auto [distance, predecessor] = initialize_single_source<weight>(g, s);
    for (unsigned long i = 1; i < g.number_of_vertices(); i++)
        for (const auto & [u, v] : g.edges())
            relax(g, u, v, distance, predecessor);
    for (const auto & [u, v] : g.edges()) {
        if (distance->at(v) - g.edge_data(u, v)> distance->at(u) ) {
            delete distance;
            delete predecessor;
            return {nullptr, nullptr};
        }
    }
    return {distance, predecessor};
}


//template <class weight>
//std::pair<distance_map<weight>*, predecessor_map*> dijkstra(
//        const graph &g, const vertex& s, const gtk::edge_function<weight> & w) {

//}

}

#endif // SHORTEST_PATH_H
