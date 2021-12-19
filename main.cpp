#include <iostream>
#include "shortest_path.h"

using namespace std;

int main()
{
    gtk::graph g;
    g.add_edge(1, 2, 1);
    g.add_edge(2, 3, 2);
    g.add_edge(3, 4, 3);
    g.add_edge(4, 5, 4);
    g.add_edge(5, 1, 5);
    g.add_vertex(10, 100);
    g.vertex_data(1) = 4;

    cout << g.vertex_data(1) << " " << g.vertex_data(10) << endl;



    auto [distance, predecessor] = gtk::bellman_ford(g, 1);

    for (auto [v, d] : *distance)
        cout << v << ": " << d << ", ";
    cout << endl;

    for (auto [v, p] : *predecessor)
        cout << v << ": " << p << ", ";
    cout << endl;

    delete distance;
    delete predecessor;

    return 0;
}
