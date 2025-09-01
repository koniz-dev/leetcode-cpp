# Advanced Graph Algorithms

## Overview

Advanced graph algorithms solve complex problems involving graph structures, including shortest paths, network flow, strongly connected components, and advanced traversal techniques. These algorithms are fundamental to many real-world applications.

## Shortest Path Algorithms

### Dijkstra's Algorithm

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

class Graph {
private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adj; // {destination, weight}
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight}); // Undirected graph
    }
    
    std::vector<int> dijkstra(int source) {
        std::vector<int> dist(V, INT_MAX);
        std::vector<bool> visited(V, false);
        
        // Priority queue: {distance, vertex}
        std::priority_queue<std::pair<int, int>, 
                           std::vector<std::pair<int, int>>, 
                           std::greater<std::pair<int, int>>> pq;
        
        dist[source] = 0;
        pq.push({0, source});
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});
                }
            }
        }
        
        return dist;
    }
};

// Usage
void dijkstraExample() {
    Graph g(6);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);
    
    std::vector<int> distances = g.dijkstra(0);
    
    for (int i = 0; i < 6; ++i) {
        std::cout << "Distance from 0 to " << i << ": " << distances[i] << std::endl;
    }
}
```

### Bellman-Ford Algorithm

```cpp
#include <vector>
#include <climits>
#include <iostream>

struct Edge {
    int source, destination, weight;
};

class Graph {
private:
    int V, E;
    std::vector<Edge> edges;
    
public:
    Graph(int vertices, int edges) : V(vertices), E(edges) {}
    
    void addEdge(int u, int v, int w) {
        edges.push_back({u, v, w});
    }
    
    std::vector<int> bellmanFord(int source) {
        std::vector<int> dist(V, INT_MAX);
        dist[source] = 0;
        
        // Relax all edges V-1 times
        for (int i = 1; i < V; ++i) {
            for (const auto& edge : edges) {
                int u = edge.source;
                int v = edge.destination;
                int weight = edge.weight;
                
                if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                }
            }
        }
        
        // Check for negative weight cycles
        for (const auto& edge : edges) {
            int u = edge.source;
            int v = edge.destination;
            int weight = edge.weight;
            
            if (dist[u] != INT_MAX && dist[u] + weight < dist[v]) {
                std::cout << "Graph contains negative weight cycle" << std::endl;
                return {};
            }
        }
        
        return dist;
    }
};
```

### Floyd-Warshall Algorithm

```cpp
#include <vector>
#include <climits>
#include <iostream>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> dist;
    
public:
    Graph(int vertices) : V(vertices) {
        dist.resize(V, std::vector<int>(V, INT_MAX));
        for (int i = 0; i < V; ++i) {
            dist[i][i] = 0;
        }
    }
    
    void addEdge(int u, int v, int weight) {
        dist[u][v] = weight;
    }
    
    void floydWarshall() {
        for (int k = 0; k < V; ++k) {
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    if (dist[i][k] != INT_MAX && dist[k][j] != INT_MAX &&
                        dist[i][k] + dist[k][j] < dist[i][j]) {
                        dist[i][j] = dist[i][k] + dist[k][j];
                    }
                }
            }
        }
    }
    
    void printDistances() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][j] == INT_MAX) {
                    std::cout << "INF ";
                } else {
                    std::cout << dist[i][j] << " ";
                }
            }
            std::cout << std::endl;
        }
    }
};
```

## Network Flow Algorithms

### Ford-Fulkerson Algorithm

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

class FlowGraph {
private:
    int V;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;
    
public:
    FlowGraph(int vertices) : V(vertices) {
        capacity.resize(V, std::vector<int>(V, 0));
        flow.resize(V, std::vector<int>(V, 0));
    }
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
    }
    
    bool bfs(int source, int sink, std::vector<int>& parent) {
        std::vector<bool> visited(V, false);
        std::queue<int> q;
        
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (int v = 0; v < V; ++v) {
                if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        
        return visited[sink];
    }
    
    int fordFulkerson(int source, int sink) {
        std::vector<int> parent(V);
        int maxFlow = 0;
        
        while (bfs(source, sink, parent)) {
            int pathFlow = INT_MAX;
            
            // Find minimum residual capacity
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = std::min(pathFlow, capacity[u][v] - flow[u][v]);
            }
            
            // Update flow
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                flow[u][v] += pathFlow;
                flow[v][u] -= pathFlow; // Back edge
            }
            
            maxFlow += pathFlow;
        }
        
        return maxFlow;
    }
};
```

### Edmonds-Karp Algorithm

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

class EdmondsKarp {
private:
    int V;
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;
    
public:
    EdmondsKarp(int vertices) : V(vertices) {
        capacity.resize(V, std::vector<int>(V, 0));
        flow.resize(V, std::vector<int>(V, 0));
    }
    
    void addEdge(int u, int v, int cap) {
        capacity[u][v] = cap;
    }
    
    bool bfs(int source, int sink, std::vector<int>& parent) {
        std::vector<bool> visited(V, false);
        std::queue<int> q;
        
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        
        while (!q.empty() && !visited[sink]) {
            int u = q.front();
            q.pop();
            
            for (int v = 0; v < V; ++v) {
                if (!visited[v] && capacity[u][v] - flow[u][v] > 0) {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        
        return visited[sink];
    }
    
    int maxFlow(int source, int sink) {
        std::vector<int> parent(V);
        int maxFlow = 0;
        
        while (bfs(source, sink, parent)) {
            int pathFlow = INT_MAX;
            
            // Find minimum residual capacity
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                pathFlow = std::min(pathFlow, capacity[u][v] - flow[u][v]);
            }
            
            // Update flow
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                flow[u][v] += pathFlow;
                flow[v][u] -= pathFlow;
            }
            
            maxFlow += pathFlow;
        }
        
        return maxFlow;
    }
};
```

## Strongly Connected Components

### Tarjan's Algorithm

```cpp
#include <vector>
#include <stack>
#include <iostream>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adj;
    std::vector<int> disc, low;
    std::vector<bool> inStack;
    std::stack<int> st;
    int time;
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
        disc.resize(V, -1);
        low.resize(V, -1);
        inStack.resize(V, false);
        time = 0;
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    void tarjanDFS(int u, std::vector<std::vector<int>>& sccs) {
        disc[u] = low[u] = ++time;
        st.push(u);
        inStack[u] = true;
        
        for (int v : adj[u]) {
            if (disc[v] == -1) {
                tarjanDFS(v, sccs);
                low[u] = std::min(low[u], low[v]);
            } else if (inStack[v]) {
                low[u] = std::min(low[u], disc[v]);
            }
        }
        
        if (low[u] == disc[u]) {
            std::vector<int> scc;
            int v;
            do {
                v = st.top();
                st.pop();
                inStack[v] = false;
                scc.push_back(v);
            } while (v != u);
            sccs.push_back(scc);
        }
    }
    
    std::vector<std::vector<int>> findSCCs() {
        std::vector<std::vector<int>> sccs;
        
        for (int i = 0; i < V; ++i) {
            if (disc[i] == -1) {
                tarjanDFS(i, sccs);
            }
        }
        
        return sccs;
    }
};
```

### Kosaraju's Algorithm

```cpp
#include <vector>
#include <stack>
#include <iostream>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adj;
    std::vector<std::vector<int>> revAdj;
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
        revAdj.resize(V);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        revAdj[v].push_back(u);
    }
    
    void dfs1(int u, std::vector<bool>& visited, std::stack<int>& st) {
        visited[u] = true;
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs1(v, visited, st);
            }
        }
        
        st.push(u);
    }
    
    void dfs2(int u, std::vector<bool>& visited, std::vector<int>& scc) {
        visited[u] = true;
        scc.push_back(u);
        
        for (int v : revAdj[u]) {
            if (!visited[v]) {
                dfs2(v, visited, scc);
            }
        }
    }
    
    std::vector<std::vector<int>> kosaraju() {
        std::vector<bool> visited(V, false);
        std::stack<int> st;
        
        // First DFS to fill stack
        for (int i = 0; i < V; ++i) {
            if (!visited[i]) {
                dfs1(i, visited, st);
            }
        }
        
        // Reset visited array
        std::fill(visited.begin(), visited.end(), false);
        
        std::vector<std::vector<int>> sccs;
        
        // Second DFS on reversed graph
        while (!st.empty()) {
            int u = st.top();
            st.pop();
            
            if (!visited[u]) {
                std::vector<int> scc;
                dfs2(u, visited, scc);
                sccs.push_back(scc);
            }
        }
        
        return sccs;
    }
};
```

## Minimum Spanning Tree

### Kruskal's Algorithm

```cpp
#include <vector>
#include <algorithm>
#include <iostream>

struct Edge {
    int u, v, weight;
    
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

class DisjointSet {
private:
    std::vector<int> parent, rank;
    
public:
    DisjointSet(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; ++i) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int px = find(x), py = find(y);
        if (px == py) return;
        
        if (rank[px] < rank[py]) {
            parent[px] = py;
        } else if (rank[px] > rank[py]) {
            parent[py] = px;
        } else {
            parent[py] = px;
            rank[px]++;
        }
    }
};

class Graph {
private:
    int V, E;
    std::vector<Edge> edges;
    
public:
    Graph(int vertices, int edges) : V(vertices), E(edges) {}
    
    void addEdge(int u, int v, int weight) {
        edges.push_back({u, v, weight});
    }
    
    std::vector<Edge> kruskal() {
        std::vector<Edge> result;
        DisjointSet ds(V);
        
        // Sort edges by weight
        std::sort(edges.begin(), edges.end());
        
        for (const auto& edge : edges) {
            if (ds.find(edge.u) != ds.find(edge.v)) {
                result.push_back(edge);
                ds.unite(edge.u, edge.v);
            }
        }
        
        return result;
    }
};
```

### Prim's Algorithm

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

class Graph {
private:
    int V;
    std::vector<std::vector<std::pair<int, int>>> adj;
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }
    
    void addEdge(int u, int v, int weight) {
        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }
    
    std::vector<std::pair<int, int>> prim() {
        std::vector<bool> visited(V, false);
        std::vector<int> key(V, INT_MAX);
        std::vector<int> parent(V, -1);
        
        // Priority queue: {weight, vertex}
        std::priority_queue<std::pair<int, int>, 
                           std::vector<std::pair<int, int>>, 
                           std::greater<std::pair<int, int>>> pq;
        
        key[0] = 0;
        pq.push({0, 0});
        
        std::vector<std::pair<int, int>> result;
        
        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();
            
            if (visited[u]) continue;
            visited[u] = true;
            
            if (parent[u] != -1) {
                result.push_back({parent[u], u});
            }
            
            for (const auto& neighbor : adj[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;
                
                if (!visited[v] && weight < key[v]) {
                    key[v] = weight;
                    parent[v] = u;
                    pq.push({key[v], v});
                }
            }
        }
        
        return result;
    }
};
```

## Advanced Traversal

### Topological Sort

```cpp
#include <vector>
#include <queue>
#include <iostream>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adj;
    std::vector<int> inDegree;
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
        inDegree.resize(V, 0);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        inDegree[v]++;
    }
    
    std::vector<int> topologicalSort() {
        std::vector<int> result;
        std::queue<int> q;
        
        // Add vertices with 0 in-degree
        for (int i = 0; i < V; ++i) {
            if (inDegree[i] == 0) {
                q.push(i);
            }
        }
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            result.push_back(u);
            
            for (int v : adj[u]) {
                inDegree[v]--;
                if (inDegree[v] == 0) {
                    q.push(v);
                }
            }
        }
        
        if (result.size() != V) {
            std::cout << "Graph contains cycle" << std::endl;
            return {};
        }
        
        return result;
    }
};
```

### Eulerian Path/Circuit

```cpp
#include <vector>
#include <stack>
#include <iostream>

class Graph {
private:
    int V;
    std::vector<std::vector<int>> adj;
    
public:
    Graph(int vertices) : V(vertices) {
        adj.resize(V);
    }
    
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    void removeEdge(int u, int v) {
        auto it = std::find(adj[u].begin(), adj[u].end(), v);
        if (it != adj[u].end()) {
            adj[u].erase(it);
        }
    }
    
    void eulerianPath(int start) {
        std::stack<int> st;
        std::vector<int> path;
        
        st.push(start);
        
        while (!st.empty()) {
            int u = st.top();
            
            if (adj[u].empty()) {
                path.push_back(u);
                st.pop();
            } else {
                int v = adj[u].back();
                adj[u].pop_back();
                st.push(v);
            }
        }
        
        // Print path in reverse
        for (int i = path.size() - 1; i >= 0; --i) {
            std::cout << path[i];
            if (i > 0) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
};
```

## Summary

Advanced graph algorithms provide solutions for:
- **Shortest paths**: Dijkstra, Bellman-Ford, Floyd-Warshall
- **Network flow**: Ford-Fulkerson, Edmonds-Karp
- **Connectivity**: Tarjan's, Kosaraju's algorithms
- **Spanning trees**: Kruskal's, Prim's algorithms
- **Advanced traversal**: Topological sort, Eulerian paths

Key applications:
- **Routing**: Network routing, GPS navigation
- **Flow optimization**: Transportation, network capacity
- **Dependency resolution**: Build systems, package managers
- **Network design**: Minimum cost networks
- **Scheduling**: Task ordering, resource allocation

These algorithms form the foundation for solving complex graph problems in computer science and engineering applications.
