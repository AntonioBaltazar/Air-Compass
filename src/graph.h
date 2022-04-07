#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include <queue>
#include "airport.h"
#include "airplane.h"

class Vertice {
private: 
    int m_num;
public: 
    Vertice(int _num) : m_num(_num) {}
    ~Vertice() {}

    int get_num() const { return m_num; }  
};

typedef std::pair<Vertice, int> pi;

struct comparePi {
    constexpr bool operator()(pi const& a, pi const& b) const noexcept {
        return a.second < b.second;
    }
};

class Graph {
    private:
        int m_nb_vertices;
        bool m_oriented;
        std::vector<std::vector<pi>> m_adj;
        std::vector<Airport*> m_airports;
    public: 
        Graph(int _nb_vertices) : m_nb_vertices(_nb_vertices) {
            for (int i = 0; i < _nb_vertices; i++)
                m_adj.push_back(std::vector<pi>());
        }
        Graph(std::string _file_name) {
            load_from_file(_file_name);
        }
        ~Graph() {}

        // Methods
        void load_from_file(std::string _file_name);
        void addEdge(Vertice u, Vertice v, int wt);
        void display_graph();
        void BFS(Vertice u);
        void DFS();
        void DFSUtil(int u, std::vector<bool>& visited);
        void shortest_path(Vertice src);
        void primMST(Vertice src);
};

#endif // AIRPORT_H_INCLUDED