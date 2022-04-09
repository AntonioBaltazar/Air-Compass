#include <iostream>
#include "graph.h"
#include "graphreader.h"
#define INF 0x3f3f3f3f

using namespace std;


// UPDATE
void Graph::addEdge(Vertice u, Vertice v, int wt) {
    m_adj[u.get_num()].push_back(make_pair(v, wt));
    m_adj[v.get_num()].push_back(make_pair(u, wt));
} 

void Graph::display_graph() {
    int v, w;
    for (int u = 0; u < m_nb_vertices; u++) {
        cout << "Sommet " << m_airports[u]->get_name() << " lié avec \n";
        for (auto it = m_adj[u].begin(); it!= m_adj[u].end(); it++) {
            v = it->first.get_num();
            w = it->second;
            cout << "\t- " << m_airports[it->first.get_num()]->get_name() << " avec une distance de "
                 << w*200 << "km\n";
        }
        cout << "\n";
    }
}

void Graph::BFS(Vertice u) {
    queue<Vertice> q;
    vector<bool> v;
    v.assign(m_nb_vertices, false);

    q.push(u);
    v[u.get_num()] = true;

    while (!q.empty()) {
        Vertice f = q.front();
        q.pop();
        cout << f.get_num() << " ";
        // Enqueue
        for (auto i = m_adj[f.get_num()].begin(); i != m_adj[f.get_num()].end(); i++) {
            if (!v[(*i).first.get_num()]) {
                q.push((*i).first);
                v[(*i).first.get_num()] = true;
            }
        }
    }
}

void Graph::DFS() {
    vector<bool> visited(m_nb_vertices, false);
    for (int u = 0; u < m_nb_vertices; u++)
        if (visited[u] == false)
            DFSUtil(u, visited);
}

void Graph::DFSUtil(int u, vector<bool>& visited) {
    visited[u] = true;
    cout << u << " ";
    for (int i=0; i < m_adj[u].size(); i++)
        if (visited[m_adj[u][i].first.get_num()] == false)
            DFSUtil(m_adj[u][i].first.get_num(), visited);
}

void Graph::shortest_path(Vertice src) {
    priority_queue< pi, vector<pi>, comparePi > pq;
    vector<int> dist(m_nb_vertices, INF);

    pq.push(make_pair(src, 0));
    dist[src.get_num()] = 0;
    
    while (!pq.empty()) {
        Vertice u = pq.top().first;
        pq.pop();

        for (auto i = m_adj[u.get_num()].begin(); i != m_adj[u.get_num()].end(); ++i) {
            
            Vertice v = (*i).first;
            int weight = (*i).second;

            if (dist[v.get_num()] > dist[u.get_num()] + weight) {
                dist[v.get_num()] = dist[u.get_num()] + weight;
                pq.push(make_pair(v, dist[v.get_num()]));
            }
        }
    }
    
    // Print shortest distances stored in dist[]
    printf("Vertex   Distance from Source\n");
    for (int i = 0; i < m_nb_vertices; ++i)
        printf("%d \t\t %d\n", i, dist[i]); 
}

void Graph::load_from_file(std::string _file_name) {
    vector<Airport*> airports;

    ifstream ifs{_file_name};
    if (!ifs) throw runtime_error("Can't open " + _file_name);

    int oriented(0), order(0), size(0);
    GraphReader::fget_int(ifs, "Unable to read graph's settings", {&oriented, &order, &size});
    
    m_oriented = oriented;
    m_nb_vertices = order;
    // Init vertices
    for (int i = 0; i < m_nb_vertices; i++)
        m_adj.push_back(vector<pi>());

    // Reading all airports
    string _str;
    getline(ifs, _str);
    for (int i = 0; i < order; i++) {
        getline(ifs, _str);
        vector<string> _strs = GraphReader::deserialize(_str);
        airports.push_back(new Airport(_strs[0], _strs[1], {stod(_strs[2]), stod(_strs[3])}, stoi(_strs[4]), stoi(_strs[5]),
            stoi(_strs[6]), stoi(_strs[7]), stoi(_strs[8]), stoi(_strs[9]), stoi(_strs[10]), stoi(_strs[11]), stoi(_strs[12])));
    }

    // Reading all edges
    int src(0), dest(0), weight(0);
    for (int i = 0; i < size; i++) {
        GraphReader::fget_int(ifs, "Can't read this ", {&src, &dest, &weight});
        addEdge(Vertice(src), Vertice(dest), weight);
    }
    std::cout << "All is good\n";
    m_airports = airports;
}

void Graph::primMST(Vertice src) {
    
    priority_queue< pi, vector<pi>, comparePi> pq;
    vector<int> key(m_nb_vertices, INF);
    vector<int> parent(m_nb_vertices, -1);
    vector<bool> inMST(m_nb_vertices, false);

    pq.push(make_pair(src, 0));
    key[src.get_num()] = 0;

    while (!pq.empty()) {

        int u = pq.top().first.get_num();
        pq.pop();

        if (inMST[u] == true) continue;
        inMST[u] = true;

        // Traverse all adjacent of vertice 'u'
        for (auto x : m_adj[u]) {
            int v = x.first.get_num();
            int weight = x.second;

            if (inMST[v] == false && key[v] > weight) {
                key[v] = weight;
                pq.push(make_pair(Vertice(v), key[v]));
                parent[v] = u;
            } 
        }
    }

    for (int i = 1; i < m_nb_vertices; ++i)
        printf("%d - %d\n", parent[i], i);

}

void Graph::limitEdge(int _lim) {
    for (auto i = get_adj().begin(); i != get_adj().end(); i++) 
        for (auto j = (*i).begin(); j != (*i).end(); j++)
            if ((*j).second > _lim)
                (*i).erase(j--); 
}

vector<Edge> Graph::get_edges() {
    vector<Edge> edges;
    for (auto i = m_adj.begin(); i != m_adj.end(); i++) 
        for (auto j = (*i).begin(); j != (*i).end(); j++)
            edges.push_back({distance(m_adj.begin(), i), (*j).first.get_num(), (*j).second});
    return edges;
}