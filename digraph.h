#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <type_definitions.h>

// TODO implement digraph class.
namespace gtk {
    class digraph
    {
    public:
        ///
        /// \brief digraph
        ///
        digraph();

        ///
        /// \brief add_vertex
        /// \param u
        ///
        void add_vertex(const vertex& u);
        void add_arc(const vertex& u, const vertex& v);
        void remove_vertex(const vertex& u);
        void remove_arc(const vertex& u, const vertex& v);

        ///
        /// \brief has_vertex
        /// \param u
        /// \return
        ///
        bool has_vertex(const vertex& u);

        ///
        /// \brief has_arc
        /// \param u
        /// \param v
        /// \return
        ///
        bool has_arc(const vertex& u, const vertex& v);

        generator<vertex> vertices();
        generator<arc> arcs();

        ///
        /// \brief in_neighbors
        /// \param u
        /// \return
        ///
        generator<vertex> in_neighbors(const vertex& u);

        ///
        /// \brief out_neighbors
        /// \param u
        /// \return
        ///
        generator<vertex> out_neighbors(const vertex& u);

        size degree(const vertex& u);
    public:
        adjacency_map in_adj_map;
        adjacency_map out_adj_map;
        size _number_of_arcs;
    };
}



#endif // DIGRAPH_H
