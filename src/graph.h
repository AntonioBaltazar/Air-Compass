#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <vector>
#include "airport.h"

class Vertice {
    private:
        int m_number;
        bool m_visited;
        Airport m_airport;
        std::vector<std::pair<Vertice*, int>> m_adjacent;
    public:
        // Constructors & Destructor
        Vertice() {}
        ~Vertice() {}

        // Getters
        int get_number() const { return m_number; }
        bool is_visited() const { return m_visited; }
        Airport& get_airport() { return m_airport; }
        std::vector<std::pair<Vertice*, int>>& get_adjacent() { return m_adjacent; }

        // Setters
        void set_number(int _number) { m_number = _number; }
        void set_visited(bool _visited) { m_visited = _visited; }
};

class Graph {
    private:
        int m_nb_vertices;
        bool m_oriented;
        std::vector<Vertice> m_vertices;
        std::vector<std::vector<float>> m_adjacency_list;
    public:
        // Constructors & Destructor
        Graph() {}
        ~Graph() {}

        // Getters
        int get_nb_vertices() const { return m_nb_vertices; }
        bool is_oriented() const { return m_oriented; }
        std::vector<Vertice>& get_vertices() { return m_vertices; }
        std::vector<std::vector<float>>& get_adjacency_list() { return m_adjacency_list; }

        // Setters
        void set_nb_vertices(int _nb_vertices) { m_nb_vertices = _nb_vertices; }
        void set_oriented(bool _oriented) { m_oriented = _oriented; }

        // Methods
};

#endif // AIRPORT_H_INCLUDED