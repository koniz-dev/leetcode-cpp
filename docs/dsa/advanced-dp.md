# Advanced Dynamic Programming Techniques

## Overview

Advanced dynamic programming techniques extend beyond basic DP to solve complex optimization problems, handle multiple constraints, and optimize memory usage. These techniques include state compression, digit DP, tree DP, and advanced optimization strategies.

## State Compression DP

### Bitmask DP for TSP

```cpp
#include <vector>
#include <climits>
#include <iostream>

class TSPBitmask {
private:
    std::vector<std::vector<int>> graph;
    std::vector<std::vector<int>> dp;
    int n;
    
    int solve(int pos, int mask) {
        if (mask == (1 << n) - 1) {
            return graph[pos][0]; // Return to starting city
        }
        
        if (dp[pos][mask] != -1) {
            return dp[pos][mask];
        }
        
        int minCost = INT_MAX;
        for (int next = 0; next < n; ++next) {
            if ((mask & (1 << next)) == 0) { // City not visited
                int newMask = mask | (1 << next);
                int cost = graph[pos][next] + solve(next, newMask);
                minCost = std::min(minCost, cost);
            }
        }
        
        return dp[pos][mask] = minCost;
    }
    
public:
    TSPBitmask(const std::vector<std::vector<int>>& g) : graph(g), n(g.size()) {
        dp.resize(n, std::vector<int>(1 << n, -1));
    }
    
    int findMinCost() {
        return solve(0, 1); // Start from city 0, mark it as visited
    }
    
    void printPath() {
        std::vector<int> path;
        int pos = 0;
        int mask = 1;
        path.push_back(0);
        
        while (mask != (1 << n) - 1) {
            int next = -1;
            int minCost = INT_MAX;
            
            for (int i = 0; i < n; ++i) {
                if ((mask & (1 << i)) == 0) {
                    int newMask = mask | (1 << i);
                    int cost = graph[pos][i] + dp[i][newMask];
                    if (cost < minCost) {
                        minCost = cost;
                        next = i;
                    }
                }
            }
            
            path.push_back(next);
            pos = next;
            mask |= (1 << next);
        }
        
        path.push_back(0); // Return to start
        
        std::cout << "Optimal path: ";
        for (int city : path) {
            std::cout << city << " ";
        }
        std::cout << std::endl;
    }
};
```

### Subset Sum with State Compression

```cpp
#include <vector>
#include <iostream>

class SubsetSumBitmask {
private:
    std::vector<int> nums;
    std::vector<bool> dp;
    int target;
    
public:
    SubsetSumBitmask(const std::vector<int>& numbers, int sum) 
        : nums(numbers), target(sum) {
        dp.resize(1 << nums.size(), false);
    }
    
    bool canMakeSum() {
        dp[0] = true; // Empty subset
        
        for (int mask = 0; mask < (1 << nums.size()); ++mask) {
            if (!dp[mask]) continue;
            
            for (int i = 0; i < nums.size(); ++i) {
                if ((mask & (1 << i)) == 0) { // Element not used
                    int newMask = mask | (1 << i);
                    int currentSum = 0;
                    
                    // Calculate current sum for this mask
                    for (int j = 0; j < nums.size(); ++j) {
                        if (newMask & (1 << j)) {
                            currentSum += nums[j];
                        }
                    }
                    
                    if (currentSum <= target) {
                        dp[newMask] = true;
                    }
                }
            }
        }
        
        return dp[(1 << nums.size()) - 1];
    }
    
    std::vector<int> getSubset() {
        if (!canMakeSum()) return {};
        
        int mask = (1 << nums.size()) - 1;
        std::vector<int> subset;
        
        while (mask > 0) {
            for (int i = nums.size() - 1; i >= 0; --i) {
                if (mask & (1 << i)) {
                    int prevMask = mask ^ (1 << i);
                    if (dp[prevMask]) {
                        subset.push_back(nums[i]);
                        mask = prevMask;
                        break;
                    }
                }
            }
        }
        
        return subset;
    }
};
```

## Digit Dynamic Programming

### Count Numbers with Given Constraints

```cpp
#include <vector>
#include <string>
#include <iostream>

class DigitDP {
private:
    std::string number;
    std::vector<std::vector<std::vector<int>>> dp;
    int targetSum;
    
    int solve(int pos, int sum, bool tight) {
        if (pos == number.length()) {
            return sum == targetSum ? 1 : 0;
        }
        
        if (dp[pos][sum][tight] != -1) {
            return dp[pos][sum][tight];
        }
        
        int limit = tight ? (number[pos] - '0') : 9;
        int count = 0;
        
        for (int digit = 0; digit <= limit; ++digit) {
            bool newTight = tight && (digit == limit);
            int newSum = sum + digit;
            
            if (newSum <= targetSum) {
                count += solve(pos + 1, newSum, newTight);
            }
        }
        
        return dp[pos][sum][tight] = count;
    }
    
public:
    DigitDP(const std::string& num, int sum) : number(num), targetSum(sum) {
        dp.resize(num.length(), std::vector<std::vector<int>>(sum + 1, std::vector<int>(2, -1)));
    }
    
    int countNumbers() {
        return solve(0, 0, true);
    }
    
    // Count numbers in range [L, R] with given constraints
    static int countInRange(const std::string& L, const std::string& R, int targetSum) {
        DigitDP dpR(R, targetSum);
        int countR = dpR.countNumbers();
        
        // Subtract count for numbers less than L
        std::string LMinus1 = L;
        int i = LMinus1.length() - 1;
        while (i >= 0 && LMinus1[i] == '0') {
            LMinus1[i] = '9';
            i--;
        }
        if (i >= 0) {
            LMinus1[i]--;
        }
        
        DigitDP dpL(LMinus1, targetSum);
        int countL = dpL.countNumbers();
        
        return countR - countL;
    }
};
```

### Sum of Numbers with Given Constraints

```cpp
#include <vector>
#include <string>
#include <iostream>

class DigitDPSum {
private:
    std::string number;
    std::vector<std::vector<std::vector<std::pair<int, int>>>> dp;
    int targetSum;
    
    std::pair<int, int> solve(int pos, int sum, bool tight) {
        if (pos == number.length()) {
            return {sum == targetSum ? 1 : 0, sum == targetSum ? 0 : 0};
        }
        
        if (dp[pos][sum][tight].first != -1) {
            return dp[pos][sum][tight];
        }
        
        int limit = tight ? (number[pos] - '0') : 9;
        int count = 0;
        long long totalSum = 0;
        
        for (int digit = 0; digit <= limit; ++digit) {
            bool newTight = tight && (digit == limit);
            int newSum = sum + digit;
            
            if (newSum <= targetSum) {
                auto result = solve(pos + 1, newSum, newTight);
                count += result.first;
                totalSum += result.second + (long long)result.first * digit * pow(10, number.length() - 1 - pos);
            }
        }
        
        return dp[pos][sum][tight] = {count, (int)(totalSum % 1000000007)};
    }
    
public:
    DigitDPSum(const std::string& num, int sum) : number(num), targetSum(sum) {
        dp.resize(num.length(), std::vector<std::vector<std::pair<int, int>>>(sum + 1, 
            std::vector<std::pair<int, int>>(2, {-1, -1})));
    }
    
    std::pair<int, int> getCountAndSum() {
        return solve(0, 0, true);
    }
};
```

## Tree Dynamic Programming

### Maximum Independent Set in Tree

```cpp
#include <vector>
#include <iostream>

struct TreeNode {
    int val;
    std::vector<TreeNode*> children;
    
    TreeNode(int v) : val(v) {}
};

class TreeDP {
private:
    std::vector<std::vector<int>> dp;
    
    void solve(TreeNode* node, TreeNode* parent) {
        // dp[node][0] = maximum independent set excluding current node
        // dp[node][1] = maximum independent set including current node
        
        dp[node->val][0] = 0; // Exclude current node
        dp[node->val][1] = 1; // Include current node
        
        for (TreeNode* child : node->children) {
            if (child != parent) {
                solve(child, node);
                
                // If we exclude current node, we can include or exclude children
                dp[node->val][0] += std::max(dp[child->val][0], dp[child->val][1]);
                
                // If we include current node, we must exclude children
                dp[node->val][1] += dp[child->val][0];
            }
        }
    }
    
public:
    TreeDP(TreeNode* root) {
        // Assuming node values are 0 to n-1
        dp.resize(1000, std::vector<int>(2, 0));
        solve(root, nullptr);
    }
    
    int getMaxIndependentSet(TreeNode* node) {
        return std::max(dp[node->val][0], dp[node->val][1]);
    }
    
    std::vector<int> getIndependentSet(TreeNode* node, TreeNode* parent) {
        std::vector<int> result;
        
        if (dp[node->val][1] > dp[node->val][0]) {
            // Include current node
            result.push_back(node->val);
            for (TreeNode* child : node->children) {
                if (child != parent) {
                    auto childSet = getIndependentSet(child, node);
                    result.insert(result.end(), childSet.begin(), childSet.end());
                }
            }
        } else {
            // Exclude current node
            for (TreeNode* child : node->children) {
                if (child != parent) {
                    auto childSet = getIndependentSet(child, node);
                    result.insert(result.end(), childSet.begin(), childSet.end());
                }
            }
        }
        
        return result;
    }
};
```

### Tree Diameter with DP

```cpp
#include <vector>
#include <iostream>

class TreeDiameterDP {
private:
    std::vector<std::vector<int>> graph;
    std::vector<int> dp;
    int diameter;
    
    int dfs(int node, int parent) {
        int maxDepth = 0;
        int secondMaxDepth = 0;
        
        for (int child : graph[node]) {
            if (child != parent) {
                int depth = dfs(child, node);
                
                if (depth > maxDepth) {
                    secondMaxDepth = maxDepth;
                    maxDepth = depth;
                } else if (depth > secondMaxDepth) {
                    secondMaxDepth = depth;
                }
            }
        }
        
        // Update diameter
        diameter = std::max(diameter, maxDepth + secondMaxDepth);
        
        // Return maximum depth from this node
        return maxDepth + 1;
    }
    
public:
    TreeDiameterDP(const std::vector<std::vector<int>>& g) : graph(g) {
        int n = graph.size();
        dp.resize(n);
        diameter = 0;
        
        dfs(0, -1);
    }
    
    int getDiameter() const {
        return diameter;
    }
    
    std::pair<int, int> getEndpoints() {
        // Find one endpoint by doing DFS from any node
        std::vector<int> depth(graph.size(), 0);
        std::vector<int> parent(graph.size(), -1);
        
        std::function<void(int, int)> dfs1 = [&](int node, int p) {
            parent[node] = p;
            for (int child : graph[node]) {
                if (child != p) {
                    depth[child] = depth[node] + 1;
                    dfs1(child, node);
                }
            }
        };
        
        dfs1(0, -1);
        
        // Find node with maximum depth
        int endpoint1 = 0;
        for (int i = 1; i < graph.size(); ++i) {
            if (depth[i] > depth[endpoint1]) {
                endpoint1 = i;
            }
        }
        
        // Find other endpoint by doing DFS from endpoint1
        std::fill(depth.begin(), depth.end(), 0);
        std::fill(parent.begin(), parent.end(), -1);
        
        dfs1(endpoint1, -1);
        
        int endpoint2 = endpoint1;
        for (int i = 0; i < graph.size(); ++i) {
            if (depth[i] > depth[endpoint2]) {
                endpoint2 = i;
            }
        }
        
        return {endpoint1, endpoint2};
    }
};
```

## Advanced Optimization Techniques

### Convex Hull Trick

```cpp
#include <vector>
#include <deque>
#include <iostream>

class ConvexHullTrick {
private:
    struct Line {
        long long m, b;
        double x;
        
        Line(long long slope, long long intercept) : m(slope), b(intercept), x(-1e18) {}
        
        double intersect(const Line& other) const {
            if (m == other.m) return 1e18;
            return (double)(other.b - b) / (m - other.m);
        }
        
        long long eval(long long x) const {
            return m * x + b;
        }
    };
    
    std::deque<Line> hull;
    
public:
    void addLine(long long m, long long b) {
        Line newLine(m, b);
        
        while (hull.size() >= 2) {
            Line& last = hull[hull.size() - 2];
            Line& current = hull.back();
            
            double x = last.intersect(newLine);
            if (x <= last.x) {
                hull.pop_back();
            } else {
                break;
            }
        }
        
        if (!hull.empty()) {
            newLine.x = hull.back().intersect(newLine);
        }
        
        hull.push_back(newLine);
    }
    
    long long query(long long x) {
        while (hull.size() >= 2 && hull[1].x <= x) {
            hull.pop_front();
        }
        
        return hull.front().eval(x);
    }
    
    // For queries in decreasing order
    long long queryDecreasing(long long x) {
        while (hull.size() >= 2 && hull[hull.size() - 2].x >= x) {
            hull.pop_back();
        }
        
        return hull.back().eval(x);
    }
};

// Example usage: Maximum value of f(x) = max(m_i * x + b_i)
class MaxValueOptimizer {
private:
    ConvexHullTrick cht;
    
public:
    void addFunction(long long m, long long b) {
        cht.addLine(m, b);
    }
    
    long long getMaxValue(long long x) {
        return cht.query(x);
    }
};
```

### Divide and Conquer Optimization

```cpp
#include <vector>
#include <climits>
#include <iostream>

class DivideConquerDP {
private:
    std::vector<std::vector<int>> dp;
    std::vector<int> cost;
    
    void solve(int l, int r, int optL, int optR, int k) {
        if (l > r) return;
        
        int mid = (l + r) / 2;
        int bestOpt = optL;
        int bestCost = INT_MAX;
        
        for (int opt = optL; opt <= std::min(mid, optR); ++opt) {
            int currentCost = (opt == 0 ? 0 : dp[k - 1][opt - 1]) + 
                             getCost(opt, mid);
            
            if (currentCost < bestCost) {
                bestCost = currentCost;
                bestOpt = opt;
            }
        }
        
        dp[k][mid] = bestCost;
        
        solve(l, mid - 1, optL, bestOpt, k);
        solve(mid + 1, r, bestOpt, optR, k);
    }
    
    int getCost(int l, int r) {
        // Implement your cost function here
        // Example: sum of squares
        int sum = 0;
        for (int i = l; i <= r; ++i) {
            sum += cost[i];
        }
        return sum * sum;
    }
    
public:
    DivideConquerDP(const std::vector<int>& c, int k) : cost(c) {
        int n = cost.size();
        dp.resize(k + 1, std::vector<int>(n, INT_MAX));
        
        // Base case: k = 1
        for (int i = 0; i < n; ++i) {
            dp[1][i] = getCost(0, i);
        }
        
        // Solve for k > 1
        for (int k_val = 2; k_val <= k; ++k_val) {
            solve(0, n - 1, 0, n - 1, k_val);
        }
    }
    
    int getMinCost(int k, int n) {
        return dp[k][n - 1];
    }
};
```

### Monotone Queue Optimization

```cpp
#include <vector>
#include <deque>
#include <iostream>

class MonotoneQueueDP {
private:
    std::vector<int> dp;
    std::deque<int> q;
    
public:
    MonotoneQueueDP(int n) : dp(n, INT_MAX) {}
    
    // For problems where we need to find minimum in sliding window
    void addCandidate(int index, int value) {
        while (!q.empty() && dp[q.back()] >= value) {
            q.pop_back();
        }
        q.push_back(index);
    }
    
    void removeCandidate(int index) {
        while (!q.empty() && q.front() <= index) {
            q.pop_front();
        }
    }
    
    int getMin() {
        return q.empty() ? INT_MAX : dp[q.front()];
    }
    
    // Example: Minimum cost to reach position i with maximum jump k
    void solveMinCostJump(const std::vector<int>& cost, int maxJump) {
        int n = cost.size();
        dp[0] = cost[0];
        
        for (int i = 1; i < n; ++i) {
            // Remove candidates that are too far back
            removeCandidate(i - maxJump - 1);
            
            // Add current position as candidate
            addCandidate(i - 1, dp[i - 1]);
            
            // Get minimum cost from valid candidates
            int minCost = getMin();
            if (minCost != INT_MAX) {
                dp[i] = minCost + cost[i];
            }
        }
    }
};
```

## Memory Optimization

### Rolling Array Technique

```cpp
#include <vector>
#include <iostream>

class RollingArrayDP {
public:
    // 0-1 Knapsack with O(W) space
    int knapsackOptimized(const std::vector<int>& weights, 
                          const std::vector<int>& values, int W) {
        int n = weights.size();
        std::vector<int> dp(W + 1, 0);
        
        for (int i = 0; i < n; ++i) {
            for (int w = W; w >= weights[i]; --w) {
                dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
            }
        }
        
        return dp[W];
    }
    
    // LCS with O(min(m,n)) space
    int lcsOptimized(const std::string& str1, const std::string& str2) {
        int m = str1.length();
        int n = str2.length();
        
        if (m < n) {
            return lcsOptimized(str2, str1);
        }
        
        std::vector<int> dp(n + 1, 0);
        
        for (int i = 1; i <= m; ++i) {
            int prev = 0;
            for (int j = 1; j <= n; ++j) {
                int temp = dp[j];
                if (str1[i - 1] == str2[j - 1]) {
                    dp[j] = prev + 1;
                } else {
                    dp[j] = std::max(dp[j], dp[j - 1]);
                }
                prev = temp;
            }
        }
        
        return dp[n];
    }
};
```

## Summary

Advanced DP techniques provide solutions for:
- **State compression**: Bitmask DP for combinatorial problems
- **Digit DP**: Number theory and counting problems
- **Tree DP**: Tree-based optimization problems
- **Optimization**: Convex hull trick, divide and conquer
- **Memory optimization**: Rolling arrays, space reduction

Key applications:
- **Combinatorial optimization**: TSP, subset sum
- **Number theory**: Digit constraints, range queries
- **Tree problems**: Independent sets, diameter
- **Function optimization**: Linear functions, cost functions
- **Resource constraints**: Limited memory, time optimization

These techniques extend DP to solve complex problems efficiently while managing memory and time constraints.
