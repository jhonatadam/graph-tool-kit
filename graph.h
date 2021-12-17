#ifndef GRAPH_H
#define GRAPH_H

#include "type_definitions.h"

namespace gtk {
    class graph {
    public:
        ///
        /// \brief graph contructor
        ///
        graph();

        ///
        /// \brief addVertex adds a vertex u to the graph.
        /// \param u vertex to be added.
        ///
        void add_vertex(const vertex &u);

        ///
        /// \brief add_edge adds an edge (u, v) to the graph. if one or both end points
        ///        are not in the graph, add_edge also adds the missing end point to the
        ///        graph.
        /// \param u end point u of the added edge.
        /// \param v end point v of the added edge.
        ///
        void add_edge(const vertex & u, const vertex & v);


        //TODO implement remove vertex
        void remove_vertex(const vertex& u);
        // TODO implement remove edge
        void remove_edge(const vertex& u, const vertex& v);

        ///
        /// \brief has_vertex checks if vertex u is in the graph.
        /// \param u vertex to be checked.
        /// \return true if vertex u is in the graph or false, otherwise.
        ///
        bool has_vertex(const vertex &u) const;

        ///
        /// \brief has_edge checks if edge (u, v) is in the graph.
        /// \param u end point u of the checked edge.
        /// \param v end point v of the checked edge.
        /// \return true if edge (u, v) is in the graph or
        ///         false, otherwise.
        ///
        bool has_edge(const vertex &u, const vertex &v);

        ///
        /// \brief vertices allows iterate over the vertices.
        /// \return a vertex generator for the graph vertices.
        ///
        generator<vertex> vertices() const;

        ///
        /// \brief edges allows iterate over the edges.
        /// \return a edge generator for the graph edges.
        ///
        generator<edge> edges() const;

        ///
        /// \brief neighbors allows iterate over the neighbors of u.
        /// \param u vertex the neighbors are accessed.
        /// \return a vertex generator for the adjacency of u.
        ///
        generator<vertex> neighbors(const vertex &u) const;

        ///
        /// \brief degree accesses the degree of vertex u.
        /// \param u vertex the degree is accessed.
        /// \return the degree of vertex u.
        ///
        size degree(const vertex& u);

        ///
        /// \brief number_of_vertices accesses the number of vertices.
        /// \return the number of vertices in the graph.
        ///
        size number_of_vertices() const;

        ///
        /// \brief number_of_edges accesses the number of edges.
        /// \return the number of edges in the graph.
        ///
        size number_of_edges();

    private:
        ///
        /// \brief adj_map keeps the adjacency map of the graph.
        ///
        adjacency_map adj_map; 

        ///
        /// \brief number_of_edges keeps the number of edges in the graph.
        ///
        size _number_of_edges;
    };
}

#endif // GRAPH_H
