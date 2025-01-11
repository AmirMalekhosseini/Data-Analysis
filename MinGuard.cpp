#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>
using namespace std;

void fast_io() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
}

class Edge {
public:
    int u, v;
    Edge(int u, int v) : u(u), v(v) {}
};

int main() {
    fast_io();
    
    int n, m;
    cin >> n >> m;
    
    vector<Edge> edges;                
    unordered_map<int, vector<int>> adj; // Adjacency map for edges by vertices
    unordered_set<int> C;             // Vertex cover set
    
    // Input edges and populate adjacency map
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
        adj[u].push_back(i);
        adj[v].push_back(i);
    }

    vector<bool> edgeRemoved(m, false);

    while (true) {
        int arbitraryEdge = -1;
        for (int i = 0; i < m; ++i) {
            if (!edgeRemoved[i]) {
                arbitraryEdge = i;
                break;
            }
        }
        
        if (arbitraryEdge == -1) break; // All edges are processed
        
        // Let (u, v) be the arbitrary edge
        int u = edges[arbitraryEdge].u;
        int v = edges[arbitraryEdge].v;
        
        // Add u and v to the vertex cover
        C.insert(u);
        C.insert(v);
        
        // Remove edge (u, v) and all edges incident on u or v
        for (int edgeIdx : adj[u]) {
            edgeRemoved[edgeIdx] = true;
        }
        for (int edgeIdx : adj[v]) {
            edgeRemoved[edgeIdx] = true;
        }
    }
    
    cout << C.size() << "\n";

    return 0;
}
