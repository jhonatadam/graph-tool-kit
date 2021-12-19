#include "digraph.h"

gtk::digraph::digraph()
{
    _number_of_arcs = 0;
}

void gtk::digraph::add_vertex(const vertex &u)
{
    in_adj_map[u];
    out_adj_map[u];
}

bool gtk::digraph::has_vertex(const vertex &u)
{
    return in_adj_map.find(u) != in_adj_map.end();
}

bool gtk::digraph::has_arc(const vertex &u, const vertex &v)
{
    auto u_it = out_adj_map.find(u);
    return u_it != out_adj_map.end() && u_it->second.find(v) != u_it->second.end();
}

gtk::generator<gtk::vertex> gtk::digraph::in_neighbors(const vertex &u)
{
    if (!has_vertex(u))
        throw "Vertex u is not in the digraph.";

    auto generator_function = [&](yield<vertex> & yield) {
        for (auto & v : this->in_adj_map[u])
            yield(v);
    };
    return generator<vertex>(generator_function);
}

gtk::generator<gtk::vertex> gtk::digraph::out_neighbors(const vertex &u)
{
    if (!has_vertex(u))
        throw "Vertex u is not in the digraph.";

    auto generator_function = [&](yield<vertex> & yield) {
        for (auto & v : this->out_adj_map[u])
            yield(v);
    };
    return generator<vertex>(generator_function);
}
