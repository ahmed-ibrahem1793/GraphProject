#include "graph_logic.h"
#include <sstream>

// --- DSU Implementation ---
DSU::DSU(int n) {
    parent.resize(n + 1);
    rank.resize(n + 1, 0);
    for (int i = 0; i <= n; i++) parent[i] = i;
}

int DSU::find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

bool DSU::unite(int x, int y) {
    int px = find(x), py = find(y);
    if (px == py) return false;
    if (rank[px] < rank[py]) swap(px, py);
    parent[py] = px;
    if (rank[px] == rank[py]) rank[px]++;
    return true;
}

// --- Graph Implementation ---
Graph::Graph(string filename) {
    ifstream infile(filename);
    if (!infile.is_open()) {
        n = 0;
        return;
    }

    string line;
    vector<string> lines;
    // 1. Read all lines first to determine node count 'n'
    while (getline(infile, line)) {
        if (!line.empty()) {
            lines.push_back(line);
        }
    }
    n = lines.size();
    adj.assign(n + 1, vector<pair<int, int>>());
    edges.clear();

    // 2. Process each line for each node
    for (int i = 0; i < lines.size(); i++) {
        int u = i + 1; // Current node is the line number
        stringstream ss(lines[i]);
        int v, w;

        // This will keep reading pairs (neighbor, weight) until the line ends
        while (ss >> v >> w) {
            adj[u].push_back({v, w});
            // For Kruskal/Prim, ensure we don't add the same edge twice
            if (u < v) {
                edges.push_back({u, v, w});
            }
        }
    }
    infile.close();
}
string Graph::primMST(string outputFile) {
    vector<bool> inMST(n + 1, false);
    vector<int> key(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[1] = 0;
    pq.push({0, 1});
    int totalWeight = 0;
    vector<pair<int, int>> mstEdges;

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;

        if (parent[u] != -1) {
            mstEdges.push_back({parent[u], u});
            totalWeight += key[u];
        }

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;
            if (!inMST[v] && w < key[v]) {
                key[v] = w;
                parent[v] = u;
                pq.push({w, v});
            }
        }
    }

    ofstream outfile(outputFile);
    outfile << "Prim's Minimum Spanning Tree\nEdge\tWeight\n";
    for (auto& edge : mstEdges) {
        int u = edge.first;
        int v = edge.second;
        outfile << u << " - " << v << "\t" << key[v] << "\n";
    }
    outfile << "Total Weight: " << totalWeight << "\n";
    outfile.close();

    return outputFile;
}

string Graph::kruskalMST(string outputFile) {
    sort(edges.begin(), edges.end());
    DSU dsu(n);
    int totalWeight = 0;
    vector<Edge> mstEdges;

    for (auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            mstEdges.push_back(e);
            totalWeight += e.weight;
        }
    }

    ofstream outfile(outputFile);
    outfile << "Kruskal's Minimum Spanning Tree\nEdge\tWeight\n";
    for (auto& e : mstEdges) {
        outfile << e.u << " - " << e.v << "\t" << e.weight << "\n";
    }
    outfile << "Total Weight: " << totalWeight << "\n";
    outfile.close();
    return outputFile;
}
string Graph::dijkstra(int src, string outputFile) {
    if (src < 1 || src > n) {
        ofstream outfile(outputFile);
        outfile << "Error: Source node " << src << " is out of bounds." << endl;
        outfile.close();
        return outputFile;
    }

    vector<int> dist(n + 1, INT_MAX);
    vector<int> parent(n + 1, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[src] = 0;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (auto& edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;

            // FIX: Check for INT_MAX to prevent overflow
            if (dist[u] != INT_MAX && dist[u] + w < dist[v]) {
                dist[v] = dist[u] + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    ofstream outfile(outputFile);
    outfile << "Dijkstra's Shortest Path from Node " << src << "\n";
    outfile << "Dst\tDist\tPath\n";

    for (int i = 1; i <= n; i++) {
        if (i == src) continue;
        outfile << i << "\t";
        if (dist[i] == INT_MAX) {
            outfile << "INF\tNo path\n";
        } else {
            outfile << dist[i] << "\t";
            vector<int> path;
            for (int v = i; v != -1; v = parent[v]) path.push_back(v);
            reverse(path.begin(), path.end());
            for (size_t j = 0; j < path.size(); j++) {
                outfile << path[j] << (j < path.size() - 1 ? "->" : "");
            }
            outfile << "\n";
        }
    }
    outfile.close();
    return outputFile;
}

string Graph::readFileContent(string filename) {
    ifstream f(filename);
    stringstream buffer;
    buffer << f.rdbuf();
    return buffer.str();
}
