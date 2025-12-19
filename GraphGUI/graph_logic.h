#ifndef GRAPH_LOGIC_H
#define GRAPH_LOGIC_H

#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DSU {
    vector<int> parent, rank;
public:
    DSU(int n);
    int find(int x);
    bool unite(int x, int y);
};

class Graph {
    int n;
    vector<vector<pair<int, int>>> adj;
    vector<Edge> edges;

public:
    Graph(string filename);
    // Returns the filename of the output so the GUI knows what to read
    string primMST(string outputFile);
    string kruskalMST(string outputFile);
    string dijkstra(int src, string outputFile);

    // Helper to read file content back to string for GUI display
    static string readFileContent(string filename);
};

#endif // GRAPH_LOGIC_H
