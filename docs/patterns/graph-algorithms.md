# 🕸️ Graph Algorithms

## 📚 Overview
**Graph Algorithms** are algorithms that solve problems on graphs, including path finding, minimum spanning tree, connected components, and many other problems.

## 🎯 **When to Use**
- **Network problems** - Social networks, computer networks
- **Path finding** - Shortest path, all paths
- **Connectivity** - Connected components, bridges, articulation points
- **Cycles** - Cycle detection, topological sorting
- **Flow problems** - Maximum flow, minimum cut

## 🚀 **Core Algorithms**

### **1. Depth-First Search (DFS)**
```cpp
// DFS Recursive
void dfs(vector<vector<int>>& graph, int node, vector<bool>& visited) {
    visited[node] = true;
    cout << node << " ";  // Process node
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfs(graph, neighbor, visited);
        }
    }
}

// DFS Iterative with Stack
void dfsIterative(vector<vector<int>>& graph, int start) {
    vector<bool> visited(graph.size(), false);
    stack<int> st;
    st.push(start);
    
    while (!st.empty()) {
        int node = st.top();
        st.pop();
        
        if (!visited[node]) {
            visited[node] = true;
            cout << node << " ";  // Process node
            
            // Push unvisited neighbors
            for (int i = graph[node].size() - 1; i >= 0; i--) {
                int neighbor = graph[node][i];
                if (!visited[neighbor]) {
                    st.push(neighbor);
                }
            }
        }
    }
}
```

**Time Complexity**: O(V + E)  
**Space Complexity**: O(V)

### **2. Breadth-First Search (BFS)**
```cpp
// BFS for Shortest Path
vector<int> bfsShortestPath(vector<vector<int>>& graph, int start) {
    int n = graph.size();
    vector<int> distance(n, -1);
    queue<int> q;
    
    distance[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        for (int neighbor : graph[node]) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[node] + 1;
                q.push(neighbor);
            }
        }
    }
    
    return distance;
}

// BFS for Level Order
vector<vector<int>> bfsLevelOrder(vector<vector<int>>& graph, int start) {
    vector<vector<int>> levels;
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    
    q.push(start);
    visited[start] = true;
    
    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        
        for (int i = 0; i < levelSize; i++) {
            int node = q.front();
            q.pop();
            currentLevel.push_back(node);
            
            for (int neighbor : graph[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        
        levels.push_back(currentLevel);
    }
    
    return levels;
}
```

**Time Complexity**: O(V + E)  
**Space Complexity**: O(V)

### **3. Topological Sort**
```cpp
// Topological Sort using DFS
vector<int> topologicalSort(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<int> result;
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfsTopo(graph, i, visited, result);
        }
    }
    
    reverse(result.begin(), result.end());
    return result;
}

void dfsTopo(vector<vector<int>>& graph, int node, vector<bool>& visited, vector<int>& result) {
    visited[node] = true;
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            dfsTopo(graph, neighbor, visited, result);
        }
    }
    
    result.push_back(node);
}

// Topological Sort using Kahn's Algorithm (BFS)
vector<int> topologicalSortKahn(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<int> inDegree(n, 0);
    
    // Calculate in-degrees
    for (int i = 0; i < n; i++) {
        for (int neighbor : graph[i]) {
            inDegree[neighbor]++;
        }
    }
    
    // Add nodes with 0 in-degree to queue
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (inDegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> result;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);
        
        for (int neighbor : graph[node]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }
    
    return result.size() == n ? result : vector<int>{};
}
```

## 🔍 **Advanced Algorithms**

### **1. Dijkstra's Shortest Path**
```cpp
// Dijkstra's Algorithm for weighted graphs
vector<int> dijkstra(vector<vector<pair<int, int>>>& graph, int start) {
    int n = graph.size();
    vector<int> distance(n, INT_MAX);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    distance[start] = 0;
    pq.push({0, start});
    
    while (!pq.empty()) {
        int dist = pq.top().first;
        int node = pq.top().second;
        pq.pop();
        
        if (dist > distance[node]) continue;
        
        for (auto& [neighbor, weight] : graph[node]) {
            int newDist = distance[node] + weight;
            if (newDist < distance[neighbor]) {
                distance[neighbor] = newDist;
                pq.push({newDist, neighbor});
            }
        }
    }
    
    return distance;
}
```

### **2. Union-Find (Disjoint Set)**
```cpp
class UnionFind {
private:
    vector<int> parent, rank;
    
public:
    UnionFind(int n) : parent(n), rank(n, 0) {
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }
    
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);  // Path compression
        }
        return parent[x];
    }
    
    void unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        
        if (rootX == rootY) return;
        
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootY] = rootX;
            rank[rootX]++;
        }
    }
    
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};
```

### **3. Cycle Detection**
```cpp
// Detect cycle in undirected graph
bool hasCycleUndirected(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfsCycleUndirected(graph, i, -1, visited)) {
                return true;
            }
        }
    }
    return false;
}

bool dfsCycleUndirected(vector<vector<int>>& graph, int node, int parent, vector<bool>& visited) {
    visited[node] = true;
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (dfsCycleUndirected(graph, neighbor, node, visited)) {
                return true;
            }
        } else if (neighbor != parent) {
            return true;  // Back edge found
        }
    }
    return false;
}

// Detect cycle in directed graph
bool hasCycleDirected(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<bool> visited(n, false);
    vector<bool> recStack(n, false);
    
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            if (dfsCycleDirected(graph, i, visited, recStack)) {
                return true;
            }
        }
    }
    return false;
}

bool dfsCycleDirected(vector<vector<int>>& graph, int node, vector<bool>& visited, vector<bool>& recStack) {
    visited[node] = true;
    recStack[node] = true;
    
    for (int neighbor : graph[node]) {
        if (!visited[neighbor]) {
            if (dfsCycleDirected(graph, neighbor, visited, recStack)) {
                return true;
            }
        } else if (recStack[neighbor]) {
            return true;  // Back edge found
        }
    }
    
    recStack[node] = false;
    return false;
}
```

## 🔍 **Problem Examples**

### **Easy Level**
- [200. Number of Islands](https://leetcode.com/problems/number-of-islands/)
- [733. Flood Fill](https://leetcode.com/problems/flood-fill/)
- [997. Find the Town Judge](https://leetcode.com/problems/find-the-town-judge/)

### **Medium Level**
- [207. Course Schedule](https://leetcode.com/problems/course-schedule/)
- [210. Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
- [547. Number of Provinces](https://leetcode.com/problems/number-of-provinces/)
- [743. Network Delay Time](https://leetcode.com/problems/network-delay-time/)

### **Hard Level**
- [787. Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)
- [1192. Critical Connections in a Network](https://leetcode.com/problems/critical-connections-in-a-network/)
- [1631. Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/)

## 💡 **Key Insights**

### **1. Graph Representation**
```cpp
// Adjacency List (most common)
vector<vector<int>> graph;  // Unweighted
vector<vector<pair<int, int>>> graph;  // Weighted

// Adjacency Matrix
vector<vector<int>> graph;  // graph[i][j] = weight or 0/1

// Edge List
vector<tuple<int, int, int>> edges;  // {from, to, weight}
```

### **2. Visited vs Processing States**
```cpp
// For cycle detection in directed graphs
vector<bool> visited(n, false);      // Fully processed
vector<bool> processing(n, false);   // Currently in recursion stack
```

### **3. Path Reconstruction**
```cpp
// Store parent nodes to reconstruct path
vector<int> parent(n, -1);

// During BFS/DFS
parent[neighbor] = node;

// Reconstruct path
vector<int> path;
for (int curr = end; curr != -1; curr = parent[curr]) {
    path.push_back(curr);
}
reverse(path.begin(), path.end());
```

## 🎯 **C++23 Modern Implementation**

### **Using std::ranges and std::views**
```cpp
// Modern C++23 approach with ranges
auto bfsModern = [&](const auto& graph, int start) -> std::vector<int> {
    std::vector<int> distance(graph.size(), -1);
    std::queue<int> q;
    
    distance[start] = 0;
    q.push(start);
    
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        
        // Process neighbors using std::ranges
        auto neighbors = graph[node] | std::views::filter([&](int neighbor) {
            return distance[neighbor] == -1;
        });
        
        for (int neighbor : neighbors) {
            distance[neighbor] = distance[node] + 1;
            q.push(neighbor);
        }
    }
    
    return distance;
};
```

### **Using std::priority_queue with custom comparator**
```cpp
// Modern priority queue usage
auto dijkstraModern = [&](const auto& graph, int start) -> std::vector<int> {
    int n = graph.size();
    std::vector<int> distance(n, std::numeric_limits<int>::max());
    
    // Use std::greater for min-heap
    std::priority_queue<std::pair<int, int>, 
                       std::vector<std::pair<int, int>>, 
                       std::greater<>> pq;
    
    distance[start] = 0;
    pq.emplace(0, start);
    
    while (!pq.empty()) {
        auto [dist, node] = pq.top();
        pq.pop();
        
        if (dist > distance[node]) continue;
        
        for (const auto& [neighbor, weight] : graph[node]) {
            int newDist = distance[node] + weight;
            if (newDist < distance[neighbor]) {
                distance[neighbor] = newDist;
                pq.emplace(newDist, neighbor);
            }
        }
    }
    
    return distance;
};
```

## 📊 **Complexity Analysis**

| Algorithm | Time | Space | Best For |
|-----------|------|-------|----------|
| DFS/BFS | O(V + E) | O(V) | Traversal, connectivity |
| Topological Sort | O(V + E) | O(V) | DAG problems |
| Dijkstra | O((V + E) log V) | O(V) | Shortest path (positive weights) |
| Union-Find | O(α(V)) | O(V) | Connectivity, MST |

## 🎓 **Practice Problems by Category**

### **Traversal Problems**
1. [Number of Islands](https://leetcode.com/problems/number-of-islands/)
2. [Flood Fill](https://leetcode.com/problems/flood-fill/)
3. [Clone Graph](https://leetcode.com/problems/clone-graph/)

### **Topological Sort**
1. [Course Schedule](https://leetcode.com/problems/course-schedule/)
2. [Course Schedule II](https://leetcode.com/problems/course-schedule-ii/)
3. [Alien Dictionary](https://leetcode.com/problems/alien-dictionary/)

### **Shortest Path**
1. [Network Delay Time](https://leetcode.com/problems/network-delay-time/)
2. [Cheapest Flights Within K Stops](https://leetcode.com/problems/cheapest-flights-within-k-stops/)
3. [Path With Minimum Effort](https://leetcode.com/problems/path-with-minimum-effort/)

### **Connectivity**
1. [Number of Provinces](https://leetcode.com/problems/number-of-provinces/)
2. [Critical Connections](https://leetcode.com/problems/critical-connections-in-a-network/)
3. [Redundant Connection](https://leetcode.com/problems/redundant-connection/)

## 🔗 **Related Patterns**
- **Tree Traversal** - DFS/BFS on trees
- **Dynamic Programming** - Graph DP problems
- **Backtracking** - Path finding and exploration
- **Greedy** - MST algorithms

## 🚀 **Optimization Tips**

### **1. Early Termination**
```cpp
// Stop early when target is found
if (node == target) return true;
```

### **2. Bidirectional BFS**
```cpp
// Search from both ends to reduce time
// Especially effective when target is far from start
```

### **3. A* Algorithm**
```cpp
// Use heuristic to guide search
// Combine with priority queue
```

---

**Remember**: Graph Algorithms require understanding of basic patterns. Practice to master them! 🚀
