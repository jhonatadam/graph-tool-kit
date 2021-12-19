#ifndef GRAPH_H
#define GRAPH_H

#include <boost/functional/hash.hpp>
#include "type_definitions.h"

// TODO fix all graph exceptions.
namespace gtk {

template <class edge_data_type = double,
          class vertex_data_type = double,
          class vertex_type = int>
class graph {
    using vertex_set = std::unordered_set<vertex_type>;
    using vertex_pair = std::pair<vertex_type, vertex_type>;
    using vertex_pair_hash = boost::hash<vertex_pair>;

    ///
    /// \brief adjacency_map keeps the adjacency map of the graph.
    ///
    std::unordered_map<vertex_type, vertex_set> adjacency_map;

    ///
    /// \brief _number_of_edges keeps the number of edges in the graph.
    ///
    size _number_of_edges;

    ///
    /// \brief vertex_data_map maps vertices to their respective data.
    ///
    std::unordered_map<vertex_type, vertex_data_type> vertex_data_map;

    ///
    /// \brief edge_data_map maps edges to their respective data.
    ///
    std::unordered_map<vertex_pair, edge_data_type, vertex_pair_hash> edge_data_map;

public:
    struct edge{vertex_type u; vertex_type v;};

    ///
    /// \brief graph contructor
    ///
    graph()
    {
        _number_of_edges = 0;
    }

    ///
    /// \brief add_vertex adds a vertex u to the graph.
    /// \param u vertex to be added.
    ///
    void add_vertex(const vertex_type& u)
    {
        adjacency_map[u];
    }

    ///
    /// \brief add_vertex adds vertex u to the graph.
    /// \param u vertex to be added.
    /// \param data vertex u data.
    ///
    void add_vertex(const vertex_type& u, const edge_data_type& data)
    {
        adjacency_map[u];
        vertex_data_map[u] = data;
    }

    ///
    /// \brief add_edge adds an edge (u, v) to the graph. if one or both end points
    ///        are not in the graph, add_edge also adds the missing end point to the
    ///        graph.
    /// \param u end point u of the added edge.
    /// \param v end point v of the added edge.
    ///
    void add_edge(const vertex_type & u, const vertex_type & v)
    {
        if (!has_edge(u, v)) {
            adjacency_map[u].insert(v);
            adjacency_map[v].insert(u);
            _number_of_edges++;
        }
    }

    ///
    /// \brief add_edge adds an edge (u, v) e their data to the graph. if one or both
    ///        end points are not in the graph, add_edge also adds the missing end points
    ///        to the graph.
    /// \param u
    /// \param v
    /// \param data
    ///
    void add_edge(const vertex_type& u, const vertex_type& v, const edge_data_type& data)
    {
        if (!has_edge(u, v)) {
            adjacency_map[u].insert(v);
            adjacency_map[v].insert(u);
            edge_data_map[std::minmax(u, v)] = data;
            _number_of_edges++;
        }
    }


    //TODO implement remove vertex
    void remove_vertex(const vertex_type& u);
    // TODO implement remove edge
    void remove_edge(const vertex_type& u, const vertex_type& v);

    ///
    /// \brief has_vertex checks if vertex u is in the graph.
    /// \param u vertex to be checked.
    /// \return true if vertex u is in the graph or false, otherwise.
    ///
    bool has_vertex(const vertex_type &u) const
    {
        return adjacency_map.find(u) != adjacency_map.end();
    }

    ///
    /// \brief has_edge checks if edge (u, v) is in the graph.
    /// \param u end point u of the checked edge.
    /// \param v end point v of the checked edge.
    /// \return true if edge (u, v) is in the graph or
    ///         false, otherwise.
    ///
    bool has_edge(const vertex_type &u, const vertex_type &v)
    {
        auto u_it = adjacency_map.find(u);
        return u_it != adjacency_map.end() && u_it->second.find(v) != u_it->second.end();
    }


    ///
    /// \brief vertex_data provides access to the non-constant reference of u data.
    /// \param u vertex u.
    /// \return reference to u data.
    ///
    vertex_data_type & vertex_data(const vertex_type& u)
    {
        return vertex_data_map[u];
    }

    ///
    /// \brief vertex_data provides access to the constant reference of u data.
    /// \param u vertex u
    /// \return constant reference to u data.
    ///
    const vertex_data_type& vertex_data(const vertex_data_type& u) const
    {
        auto u_it = vertex_data_map.find(u);
        if (u_it != vertex_data_map.end())
            return u_it->second;
        else
            throw "Vertex u is not in the graph.";
    }

    ///
    /// \brief edge_data provides access to the non-constant reference of edge (u, v) data.
    /// \param u end point u.
    /// \param v end point v.
    /// \return reference to (u, v) data.
    ///
    edge_data_type & edge_data(const vertex_type& u, const vertex_type& v)
    {
        return edge_data_map[std::minmax(u, v)];
    }

    ///
    /// \brief edge_data provides access to the constant reference of edge (u, v) data.
    /// \param u end point u.
    /// \param v end point v.
    /// \return constant reference to (u, v) data.
    ///
    const edge_data_type & edge_data(const vertex_type& u, const vertex_type& v) const
    {
        auto uv_it = edge_data_map.find(std::minmax(u, v));
        if (uv_it != edge_data_map.end())
            return uv_it->second;
        else
            throw "Edge (u, v) is not in the graph.";
    }

    ///
    /// \brief vertices allows iterate over the vertices.
    /// \return a vertex generator for the graph vertices.
    ///
    generator<vertex_type> vertices() const
    {
        auto generator_function = [this](yield<vertex_type> & yield) {
            for (auto & [u, _] : this->adjacency_map)
                yield(u);
        };
        return generator<vertex_type>(generator_function);
    }

    ///
    /// \brief edges allows iterate over the edges.
    /// \return a edge generator for the graph edges.
    ///
    generator<edge> edges() const
    {
        auto generator_function = [this](yield<edge> & yield) {
            for (auto & [u, adjacency] : this->adjacency_map)
                for (auto & v : adjacency)
                    if (u <= v)
                        yield({u, v});
        };
        return generator<edge>(generator_function);
    }

    ///
    /// \brief neighbors allows iterate over the neighbors of u.
    /// \param u vertex the neighbors are accessed.
    /// \return a vertex generator for the adjacency of u.
    ///
    generator<vertex_type> neighbors(const vertex_type &u) const
    {
        if (!has_vertex(u))
            throw "Vertex u in not in the graph.";

        auto generator_function = [&](yield<vertex_type> & yield) {
            for (auto & v : this->adjacency_map.at(u))
                yield(v);
        };

        return generator<vertex_type>(generator_function);
    }

    ///
    /// \brief degree accesses the degree of vertex u.
    /// \param u vertex the degree is accessed.
    /// \return the degree of vertex u.
    ///
    size degree(const vertex_type& u) const
    {
        auto u_it = adjacency_map.find(u);
        if (u_it != adjacency_map.end())
            return u_it->second.size();
        else
            throw "Vertex u is not in the graph.";
    }

    ///
    /// \brief number_of_vertices accesses the number of vertices.
    /// \return the number of vertices in the graph.
    ///
    size number_of_vertices() const
    {
        return adjacency_map.size();
    }

    ///
    /// \brief number_of_edges accesses the number of edges.
    /// \return the number of edges in the graph.
    ///
    size number_of_edges() const
    {
        return _number_of_edges;
    }
};

}

#endif // GRAPH_H
