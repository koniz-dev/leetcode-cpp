# Network Flow Algorithms

## Overview

Network flow algorithms solve problems involving the flow of resources through networks with capacity constraints. These algorithms are fundamental to transportation, telecommunications, and many optimization problems.

## Maximum Flow

### Ford-Fulkerson Algorithm

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

class FordFulkerson {
private:
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;
    std::vector<int> parent;
    int V;
    
    bool bfs(int source, int sink) {
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
    
public:
    FordFulkerson(const std::vector<std::vector<int>>& cap) : capacity(cap), V(cap.size()) {
        flow.resize(V, std::vector<int>(V, 0));
        parent.resize(V);
    }
    
    int maxFlow(int source, int sink) {
        int maxFlow = 0;
        
        while (bfs(source, sink)) {
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
    
    void printFlow() {
        std::cout << "Flow matrix:" << std::endl;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (flow[i][j] > 0) {
                    std::cout << i << " -> " << j << ": " << flow[i][j] << std::endl;
                }
            }
        }
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
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow;
    std::vector<int> parent;
    int V;
    
    bool bfs(int source, int sink) {
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
    
public:
    EdmondsKarp(const std::vector<std::vector<int>>& cap) : capacity(cap), V(cap.size()) {
        flow.resize(V, std::vector<int>(V, 0));
        parent.resize(V);
    }
    
    int maxFlow(int source, int sink) {
        int maxFlow = 0;
        
        while (bfs(source, sink)) {
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

### Dinic's Algorithm

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

class Dinic {
private:
    struct Edge {
        int to, capacity, flow, reverse;
        
        Edge(int t, int c, int r) : to(t), capacity(c), flow(0), reverse(r) {}
    };
    
    std::vector<std::vector<Edge>> graph;
    std::vector<int> level;
    std::vector<int> ptr;
    int V;
    
    bool bfs(int source, int sink) {
        std::fill(level.begin(), level.end(), -1);
        level[source] = 0;
        
        std::queue<int> q;
        q.push(source);
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            for (const Edge& edge : graph[u]) {
                if (level[edge.to] == -1 && edge.capacity > edge.flow) {
                    level[edge.to] = level[u] + 1;
                    q.push(edge.to);
                }
            }
        }
        
        return level[sink] != -1;
    }
    
    int dfs(int u, int sink, int flow) {
        if (u == sink) return flow;
        
        for (int& i = ptr[u]; i < graph[u].size(); ++i) {
            Edge& edge = graph[u][i];
            
            if (level[edge.to] == level[u] + 1 && edge.capacity > edge.flow) {
                int minFlow = std::min(flow, edge.capacity - edge.flow);
                int pushed = dfs(edge.to, sink, minFlow);
                
                if (pushed > 0) {
                    edge.flow += pushed;
                    graph[edge.to][edge.reverse].flow -= pushed;
                    return pushed;
                }
            }
        }
        
        return 0;
    }
    
public:
    Dinic(int vertices) : V(vertices) {
        graph.resize(V);
        level.resize(V);
        ptr.resize(V);
    }
    
    void addEdge(int from, int to, int capacity) {
        graph[from].emplace_back(to, capacity, graph[to].size());
        graph[to].emplace_back(from, 0, graph[from].size() - 1);
    }
    
    int maxFlow(int source, int sink) {
        int maxFlow = 0;
        
        while (bfs(source, sink)) {
            std::fill(ptr.begin(), ptr.end(), 0);
            
            while (int flow = dfs(source, sink, INT_MAX)) {
                maxFlow += flow;
            }
        }
        
        return maxFlow;
    }
};
```

## Minimum Cost Maximum Flow

### Successive Shortest Path

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

class MinCostMaxFlow {
private:
    struct Edge {
        int to, capacity, cost, flow, reverse;
        
        Edge(int t, int c, int cost, int r) 
            : to(t), capacity(c), cost(cost), flow(0), reverse(r) {}
    };
    
    std::vector<std::vector<Edge>> graph;
    std::vector<int> distance;
    std::vector<int> parent;
    std::vector<int> parentEdge;
    int V;
    
    bool bellmanFord(int source) {
        std::fill(distance.begin(), distance.end(), INT_MAX);
        distance[source] = 0;
        
        for (int i = 0; i < V - 1; ++i) {
            for (int u = 0; u < V; ++u) {
                if (distance[u] == INT_MAX) continue;
                
                for (int j = 0; j < graph[u].size(); ++j) {
                    const Edge& edge = graph[u][j];
                    if (edge.capacity > edge.flow) {
                        int v = edge.to;
                        int newDist = distance[u] + edge.cost;
                        
                        if (newDist < distance[v]) {
                            distance[v] = newDist;
                            parent[v] = u;
                            parentEdge[v] = j;
                        }
                    }
                }
            }
        }
        
        return distance[V - 1] != INT_MAX;
    }
    
public:
    MinCostMaxFlow(int vertices) : V(vertices) {
        graph.resize(V);
        distance.resize(V);
        parent.resize(V);
        parentEdge.resize(V);
    }
    
    void addEdge(int from, int to, int capacity, int cost) {
        graph[from].emplace_back(to, capacity, cost, graph[to].size());
        graph[to].emplace_back(from, 0, -cost, graph[from].size() - 1);
    }
    
    std::pair<int, int> minCostMaxFlow(int source, int sink) {
        int maxFlow = 0;
        int totalCost = 0;
        
        while (bellmanFord(source)) {
            int pathFlow = INT_MAX;
            
            // Find minimum residual capacity
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                int edgeIndex = parentEdge[v];
                pathFlow = std::min(pathFlow, graph[u][edgeIndex].capacity - graph[u][edgeIndex].flow);
            }
            
            // Update flow
            for (int v = sink; v != source; v = parent[v]) {
                int u = parent[v];
                int edgeIndex = parentEdge[v];
                
                graph[u][edgeIndex].flow += pathFlow;
                graph[v][graph[u][edgeIndex].reverse].flow -= pathFlow;
                
                totalCost += pathFlow * graph[u][edgeIndex].cost;
            }
            
            maxFlow += pathFlow;
        }
        
        return {maxFlow, totalCost};
    }
};
```

## Bipartite Matching

### Maximum Bipartite Matching

```cpp
#include <vector>
#include <iostream>

class BipartiteMatching {
private:
    std::vector<std::vector<int>> graph;
    std::vector<int> matchR;
    std::vector<bool> seen;
    int V;
    
    bool bpm(int u) {
        for (int v : graph[u]) {
            if (!seen[v]) {
                seen[v] = true;
                
                if (matchR[v] < 0 || bpm(matchR[v])) {
                    matchR[v] = u;
                    return true;
                }
            }
        }
        return false;
    }
    
public:
    BipartiteMatching(int vertices) : V(vertices) {
        graph.resize(V);
        matchR.resize(V, -1);
    }
    
    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }
    
    int maxMatching() {
        int result = 0;
        
        for (int u = 0; u < V; ++u) {
            seen.assign(V, false);
            if (bpm(u)) {
                result++;
            }
        }
        
        return result;
    }
    
    std::vector<std::pair<int, int>> getMatching() {
        std::vector<std::pair<int, int>> matching;
        
        for (int v = 0; v < V; ++v) {
            if (matchR[v] != -1) {
                matching.push_back({matchR[v], v});
            }
        }
        
        return matching;
    }
};
```

### Hopcroft-Karp Algorithm

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

class HopcroftKarp {
private:
    std::vector<std::vector<int>> graph;
    std::vector<int> pairU, pairV;
    std::vector<int> dist;
    int U, V;
    
    bool bfs() {
        std::queue<int> q;
        
        for (int u = 0; u < U; ++u) {
            if (pairU[u] == -1) {
                dist[u] = 0;
                q.push(u);
            } else {
                dist[u] = INT_MAX;
            }
        }
        
        dist[U] = INT_MAX;
        
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            
            if (dist[u] < dist[U]) {
                for (int v : graph[u]) {
                    if (dist[pairV[v]] == INT_MAX) {
                        dist[pairV[v]] = dist[u] + 1;
                        q.push(pairV[v]);
                    }
                }
            }
        }
        
        return dist[U] != INT_MAX;
    }
    
    bool dfs(int u) {
        if (u != U) {
            for (int v : graph[u]) {
                if (dist[pairV[v]] == dist[u] + 1) {
                    if (dfs(pairV[v])) {
                        pairU[u] = v;
                        pairV[v] = u;
                        return true;
                    }
                }
            }
            dist[u] = INT_MAX;
            return false;
        }
        return true;
    }
    
public:
    HopcroftKarp(int leftVertices, int rightVertices) 
        : U(leftVertices), V(rightVertices) {
        graph.resize(U);
        pairU.resize(U, -1);
        pairV.resize(V, -1);
        dist.resize(U + 1);
    }
    
    void addEdge(int u, int v) {
        graph[u].push_back(v);
    }
    
    int maxMatching() {
        int result = 0;
        
        while (bfs()) {
            for (int u = 0; u < U; ++u) {
                if (pairU[u] == -1) {
                    if (dfs(u)) {
                        result++;
                    }
                }
            }
        }
        
        return result;
    }
};
```

## Circulation Problems

### Circulation with Demands

```cpp
#include <vector>
#include <queue>
#include <climits>
#include <iostream>

class CirculationWithDemands {
private:
    std::vector<std::vector<int>> capacity;
    std::vector<int> demand;
    std::vector<int> supply;
    int V;
    
    bool hasFeasibleCirculation() {
        // Check if total supply equals total demand
        int totalSupply = 0, totalDemand = 0;
        for (int s : supply) totalSupply += s;
        for (int d : demand) totalDemand += d;
        
        return totalSupply == totalDemand;
    }
    
    std::vector<std::vector<int>> createFlowNetwork() {
        // Add source and sink
        int source = V, sink = V + 1;
        std::vector<std::vector<int>> flowNetwork(V + 2, std::vector<int>(V + 2, 0));
        
        // Connect source to supply nodes
        for (int i = 0; i < V; ++i) {
            if (supply[i] > 0) {
                flowNetwork[source][i] = supply[i];
            }
        }
        
        // Connect demand nodes to sink
        for (int i = 0; i < V; ++i) {
            if (demand[i] > 0) {
                flowNetwork[i][sink] = demand[i];
            }
        }
        
        // Copy original capacities
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                flowNetwork[i][j] = capacity[i][j];
            }
        }
        
        return flowNetwork;
    }
    
public:
    CirculationWithDemands(const std::vector<std::vector<int>>& cap, 
                           const std::vector<int>& d, const std::vector<int>& s)
        : capacity(cap), demand(d), supply(s), V(cap.size()) {}
    
    bool hasCirculation() {
        if (!hasFeasibleCirculation()) {
            return false;
        }
        
        auto flowNetwork = createFlowNetwork();
        FordFulkerson ff(flowNetwork);
        
        int maxFlow = ff.maxFlow(V, V + 1);
        
        // Check if all supply and demand constraints are satisfied
        int totalSupply = 0;
        for (int s : supply) totalSupply += s;
        
        return maxFlow == totalSupply;
    }
};
```

## Multi-Commodity Flow

### Two-Commodity Flow

```cpp
#include <vector>
#include <iostream>

class TwoCommodityFlow {
private:
    std::vector<std::vector<int>> capacity;
    std::vector<std::vector<int>> flow1, flow2;
    int V;
    
    bool isFeasible(int commodity1, int commodity2) {
        // Check if both commodities can flow without exceeding capacities
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (flow1[i][j] + flow2[i][j] > capacity[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }
    
public:
    TwoCommodityFlow(const std::vector<std::vector<int>>& cap) : capacity(cap), V(cap.size()) {
        flow1.resize(V, std::vector<int>(V, 0));
        flow2.resize(V, std::vector<int>(V, 0));
    }
    
    bool findTwoCommodityFlow(int source1, int sink1, int demand1,
                              int source2, int sink2, int demand2) {
        // First, find flow for commodity 1
        FordFulkerson ff1(capacity);
        int flow1Value = ff1.maxFlow(source1, sink1);
        
        if (flow1Value < demand1) {
            return false; // Cannot satisfy demand for commodity 1
        }
        
        // Update capacities for commodity 2
        auto residualCapacity = capacity;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                residualCapacity[i][j] -= flow1[i][j];
            }
        }
        
        // Find flow for commodity 2
        FordFulkerson ff2(residualCapacity);
        int flow2Value = ff2.maxFlow(source2, sink2);
        
        if (flow2Value < demand2) {
            return false; // Cannot satisfy demand for commodity 2
        }
        
        return true;
    }
};
```

## Applications

### Assignment Problem

```cpp
#include <vector>
#include <iostream>

class AssignmentProblem {
private:
    std::vector<std::vector<int>> cost;
    int n;
    
public:
    AssignmentProblem(const std::vector<std::vector<int>>& c) : cost(c), n(c.size()) {}
    
    int solve() {
        // Create bipartite graph
        BipartiteMatching bm(n);
        
        // Add edges with costs
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (cost[i][j] < INT_MAX) {
                    bm.addEdge(i, j);
                }
            }
        }
        
        return bm.maxMatching();
    }
};
```

### Transportation Problem

```cpp
#include <vector>
#include <iostream>

class TransportationProblem {
private:
    std::vector<int> supply;
    std::vector<int> demand;
    std::vector<std::vector<int>> cost;
    int m, n; // m suppliers, n destinations
    
public:
    TransportationProblem(const std::vector<int>& s, const std::vector<int>& d,
                         const std::vector<std::vector<int>>& c)
        : supply(s), demand(d), cost(c), m(s.size()), n(d.size()) {}
    
    int solve() {
        // Create flow network
        int source = m + n, sink = m + n + 1;
        std::vector<std::vector<int>> capacity(m + n + 2, std::vector<int>(m + n + 2, 0));
        
        // Connect source to suppliers
        for (int i = 0; i < m; ++i) {
            capacity[source][i] = supply[i];
        }
        
        // Connect destinations to sink
        for (int i = 0; i < n; ++i) {
            capacity[m + i][sink] = demand[i];
        }
        
        // Connect suppliers to destinations
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                capacity[i][m + j] = INT_MAX;
            }
        }
        
        FordFulkerson ff(capacity);
        return ff.maxFlow(source, sink);
    }
};
```

## Summary

Network flow algorithms provide solutions for:
- **Maximum flow**: Ford-Fulkerson, Edmonds-Karp, Dinic's
- **Minimum cost flow**: Successive shortest path
- **Bipartite matching**: Maximum matching, Hopcroft-Karp
- **Circulation**: Flow with supply/demand constraints
- **Multi-commodity flow**: Multiple flow types

Key applications:
- **Transportation**: Supply chain optimization
- **Telecommunications**: Network capacity planning
- **Assignment**: Job assignment, resource allocation
- **Scheduling**: Task scheduling, resource management
- **Routing**: Network routing, traffic flow

These algorithms form the foundation for solving complex network optimization problems in various domains.
