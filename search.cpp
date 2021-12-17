#include "search.h"

gtk::generator<gtk::vertex> gtk::breadth_first_search(const graph & g, const vertex & source)   {
    auto generator_function = [&] (yield<vertex> & yield) {
        std::queue<vertex> queue;
        std::unordered_set<vertex> visited_vertices;
        queue.push(source);
        visited_vertices.insert(source);
        while (!queue.empty()) {
            vertex current = queue.front();
            queue.pop();
            yield(current);
            for (const vertex & u : g.neighbors(current)) {
                if (visited_vertices.find(u) == visited_vertices.end()) {
                    queue.push(u);
                    visited_vertices.insert(u);
                }
            }
        }
    };
    return generator<vertex>(generator_function);
}
