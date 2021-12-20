#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <unordered_map>
#include <unordered_set>
#include "type_definitions.h"


namespace gtk {

template <class arc_data_type = double, class vertex_data_type = double, class vertex_type = int>
class digraph
{
    /// definitions
    using vertex_set = std::unordered_set<vertex_type>;
    using vertex_pair = std::pair<vertex_type, vertex_type>;
    using vertex_pair_hash = boost::hash<vertex_pair>;

    ///
    /// \brief in_adj_map keeps the in adjacency map of the digraph.
    ///
    std::unordered_map<vertex_type, vertex_set> in_adjacency_map;

    ///
    /// \brief out_adj_map keeps the out adjacency map of the digraph.
    ///
    std::unordered_map<vertex_type, vertex_set> out_adjacency_map;

    ///
    /// \brief _number_of_arcs keeps the number of arcs in the digraph.
    ///
    size_t _number_of_arcs;

    ///
    /// \brief vertex_data_map maps vertices to their respective data.
    ///
    std::unordered_map<vertex_type, vertex_data_type> vertex_data_map;

    ///
    /// \brief arc_data_map maps arcs to their respective data.
    ///
    std::unordered_map<vertex_pair, arc_data_type, vertex_pair_hash> arc_data_map;

public:
    struct arc {vertex_type u; vertex_type v;};

    // TODO implement digraph methods.

    ///
    /// \brief digraph
    ///
    digraph();

    ///
    /// \brief add_vertex
    /// \param u
    ///
    void add_vertex(const vertex_type& u);
    void add_vertex(const vertex_type& u, const vertex_data_type& data);
    void add_arc(const vertex_type& u, const vertex_type& v);
    void add_arc(const vertex_type& u, const vertex_type& v, const arc_data_type& data);
    void remove_vertex(const vertex_type& u);
    void remove_arc(const vertex_type& u, const vertex_type& v);

    ///
    /// \brief has_vertex
    /// \param u
    /// \return
    ///
    bool has_vertex(const vertex_type& u);

    ///
    /// \brief has_arc
    /// \param u
    /// \param v
    /// \return
    ///
    bool has_arc(const vertex_type& u, const vertex_type& v);

    generator<vertex_type> vertices();
    generator<arc> arcs();

    ///
    /// \brief in_neighbors
    /// \param u
    /// \return
    ///
    generator<vertex_type> in_neighbors(const vertex_type& u);

    ///
    /// \brief out_neighbors
    /// \param u
    /// \return
    ///
    generator<vertex_type> out_neighbors(const vertex_type& u);

    size_t degree(const vertex_type& u);
};
}



#endif // DIGRAPH_H
