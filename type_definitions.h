#ifndef TYPE_DEFINITIONS_H
#define TYPE_DEFINITIONS_H

#include <unordered_map>
#include <unordered_set>
#include <boost/coroutine2/all.hpp>
#include <boost/functional/hash.hpp>

namespace gtk {
    // TODO if vertex is a template parameter of graph, then these definitions must be defines inside graph definition.
    using size = unsigned long;
    using vertex = size;
    struct edge{vertex u; vertex v;};
    using arc = edge;
    using vertex_set = std::unordered_set<vertex>;
    using adjacency_map = std::unordered_map<vertex, vertex_set>;

    template <class T>
    using yield = typename boost::coroutines2::coroutine<T>::push_type;
    template <class T>
    using generator = typename boost::coroutines2::coroutine<T>::pull_type;

    template <class T = double>
    class vertex_function {
    public:
        T& operator()(const vertex & u) {
            return values[u];
        }

        void remove(const vertex & u) {
            auto u_it = values.find(u);
            if (u_it != values.end()) values.erase(u_it);
        }
    private:
        std::unordered_map<vertex, T> values;
    };

    template <class T = double>
    class edge_function {
    public:
        T & operator()(const vertex & u, const vertex & v) {return values[std::minmax(u, v)];}
        const T & operator()(const vertex & u, const vertex & v) const {return values.at(std::minmax(u, v));}
        T & operator()(const edge & e) {return *(this)(e.u, e.v);}
        const T & operator()(const edge & e) const {return (*this)(e.u, e.v);}
        void remove(const vertex & u, const vertex & v) {
            auto uv_it = values.find(std::minmax(u, v));
            if (uv_it != values.end()) values.erase(uv_it);
        }
        void remove(const edge & e) {this->remove(e.u, e.v);}
    private:
        std::unordered_map<std::pair<vertex, vertex>, T,
                            boost::hash<std::pair<vertex, vertex>>> values;
    };

    template <class T = double>
    class arc_function {
    public:
        T & operator()(const vertex & u, const vertex & v) const {
            return values[{u, v}];
        }
        T & operator()(const arc & e) const {return *(this)(e.u, e.v);}
        void remove(const vertex & u, const vertex & v) {
            auto uv_it = values.find({u, v});
            if (uv_it != values.end()) values.erase(uv_it);
        }
        void remove(const arc & e) {this->remove(e.u, e.v);}
    private:
        std::unordered_map<std::pair<vertex, vertex>, T,
                            boost::hash<std::pair<vertex, vertex>>> values;
    };

}

#endif // TYPE_DEFINITIONS_H
