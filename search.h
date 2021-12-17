#ifndef SEARCH_H
#define SEARCH_H

#include <queue>
#include "graph.h"
#include "digraph.h"

// TODO give description of breadth_first_search class.
namespace gtk {
///
/// \brief breadth_first_search
/// \param g
/// \param source
/// \return
///
generator<vertex> breadth_first_search(const graph & g, const vertex & source);
generator<vertex> breadth_first_search(const digraph & d, const vertex & source);
generator<vertex> depth_first_search(const graph & g, const vertex & source);
generator<vertex> depth_first_search(const digraph & d, const vertex & source);
}

#endif // SEARCH_H
