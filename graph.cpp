#include "graph.h"


gtk::graph::graph()
{
    _number_of_edges = 0;
}

void gtk::graph::add_vertex(const vertex &u)
{
    adj_map[u];
}

void gtk::graph::add_edge(const vertex &u, const vertex &v)
{
    if (!has_edge(u, v)) {
        adj_map[u].insert(v);
        adj_map[v].insert(u);
        _number_of_edges++;
    }
}

bool gtk::graph::has_vertex(const vertex &u) const
{
    return adj_map.find(u) != adj_map.end();
}

bool gtk::graph::has_edge(const vertex &u, const vertex &v)
{
    auto u_it = adj_map.find(u);
    return u_it != adj_map.end() && u_it->second.find(v) != u_it->second.end();
}

gtk::generator<gtk::vertex> gtk::graph::vertices() const
{
    auto generator_function = [this](yield<vertex> & yield) {
        for (auto & [u, _] : this->adj_map)
            yield(u);
    };
    return generator<vertex>(generator_function);
}

gtk::generator<gtk::edge> gtk::graph::edges() const
{
    auto generator_function = [this](yield<edge> & yield) {
        for (auto & [u, adjacency] : this->adj_map)
            for (auto & v : adjacency)
                if (u <= v)
                    yield({u, v});
    };
    return generator<edge>(generator_function);
}

gtk::generator<gtk::vertex> gtk::graph::neighbors(const vertex &u) const
{
    if (!has_vertex(u))
        throw "Vertex u in not in the graph.";

    auto generator_function = [&](yield<vertex> & yield) {
        for (auto & v : this->adj_map.at(u))
            yield(v);
    };

    return generator<vertex>(generator_function);
}

gtk::size gtk::graph::degree(const vertex &u)
{
    auto u_it = adj_map.find(u);
    if (u_it != adj_map.end())
        return u_it->second.size();
    else
        throw "Vertex u is not in the graph.";
}

gtk::size gtk::graph::number_of_vertices() const
{
    return adj_map.size();
}

gtk::size gtk::graph::number_of_edges()
{
    return _number_of_edges;
}
