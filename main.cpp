#include <iostream>
#include "shortest_path.h"

using namespace std;

pair<bool, vector<int>*> test(int a, vector<int>* v) {
    return {a, v};
}

int main()
{
    cout << std::numeric_limits<unsigned long>::max() << endl;
    gtk::graph g; gtk::edge_function<int> w;
    g.add_edge(1, 2), w(1, 2) = 1;
    g.add_edge(2, 3), w(2, 3) = 2;
    g.add_edge(3, 4), w(3, 4) = 3;
    g.add_edge(4, 5), w(4, 5) = 4;
    g.add_edge(5, 1), w(5, 1) = 5;
    g.add_vertex(10);

    cout << g.number_of_vertices() << endl;
    auto [distance, predecessor] = gtk::bellman_ford(g, 1, w);

    for (auto [v, d] : *distance)
        cout << v << ": " << d << ", ";
    cout << endl;

    for (auto [v, p] : *predecessor)
        cout << v << ": " << p << ", ";
    cout << endl;

    return 0;
}
