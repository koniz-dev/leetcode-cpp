# 🧠 Dynamic Programming (DP)

## 📚 Overview
**Dynamic Programming** is a powerful technique that uses memoization to avoid recalculating results of subproblems.

## 🎯 **When to Use**
- **Optimization problems** - Find optimal values (min/max)
- **Counting problems** - Count number of ways to perform
- **Subsequence problems** - LCS, LIS, subsequence
- **Partition problems** - Partition array/string into parts
- **Tree/Graph problems** - Path finding, tree traversal

## 🚀 **Core Concepts**

### **1. Optimal Substructure**
```cpp
// A large problem can be broken down into optimal subproblems
// Example: Fibonacci
int fib(int n) {
    if (n <= 1) return n;
    return fib(n-1) + fib(n-2);  // Optimal substructure
}
```

### **2. Overlapping Subproblems**
```cpp
// Subproblems are solved multiple times
// DP stores results to avoid recalculating
vector<int> dp(n + 1, -1);

int fibMemo(int n) {
    if (n <= 1) return n;
    if (dp[n] != -1) return dp[n];  // Return cached result
    
    dp[n] = fibMemo(n-1) + fibMemo(n-2);
    return dp[n];
}
```

## 🔧 **Implementation Approaches**

### **1. Top-Down (Memoization)**
```cpp
// Recursive with cache
class Solution {
private:
    vector<int> dp;
    
    int solve(int n) {
        // Base case
        if (n <= 1) return n;
        
        // Check cache
        if (dp[n] != -1) return dp[n];
        
        // Recursive case
        dp[n] = solve(n-1) + solve(n-2);
        return dp[n];
    }
    
public:
    int fib(int n) {
        dp.resize(n + 1, -1);
        return solve(n);
    }
};
```

**Time Complexity**: O(n)  
**Space Complexity**: O(n) + O(n) stack space

### **2. Bottom-Up (Tabulation)**
```cpp
// Iterative with table
int fibTabulation(int n) {
    if (n <= 1) return n;
    
    vector<int> dp(n + 1);
    dp[0] = 0;
    dp[1] = 1;
    
    for (int i = 2; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}
```

**Time Complexity**: O(n)  
**Space Complexity**: O(n)

### **3. Space Optimized**
```cpp
// Only store the necessary two values
int fibOptimized(int n) {
    if (n <= 1) return n;
    
    int prev = 0, curr = 1;
    for (int i = 2; i <= n; i++) {
        int next = prev + curr;
        prev = curr;
        curr = next;
    }
    
    return curr;
}
```

**Time Complexity**: O(n)  
**Space Complexity**: O(1)

## 🎯 **Common DP Patterns**

### **1. 1D DP - Linear Problems**
```cpp
// Climbing Stairs
int climbStairs(int n) {
    if (n <= 2) return n;
    
    vector<int> dp(n + 1);
    dp[1] = 1;
    dp[2] = 2;
    
    for (int i = 3; i <= n; i++) {
        dp[i] = dp[i-1] + dp[i-2];
    }
    
    return dp[n];
}
```

### **2. 2D DP - Matrix Problems**
```cpp
// Unique Paths
int uniquePaths(int m, int n) {
    vector<vector<int>> dp(m, vector<int>(n, 1));
    
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    
    return dp[m-1][n-1];
}
```

### **3. Knapsack Problems**
```cpp
// 0/1 Knapsack
int knapsack(vector<int>& weights, vector<int>& values, int capacity) {
    int n = weights.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    
    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= capacity; w++) {
            if (weights[i-1] <= w) {
                dp[i][w] = max(dp[i-1][w], 
                               dp[i-1][w - weights[i-1]] + values[i-1]);
            } else {
                dp[i][w] = dp[i-1][w];
            }
        }
    }
    
    return dp[n][capacity];
}
```

## 🔍 **Problem Categories**

### **Easy Level**
- [70. Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
- [198. House Robber](https://leetcode.com/problems/house-robber/)
- [509. Fibonacci Number](https://leetcode.com/problems/fibonacci-number/)

### **Medium Level**
- [62. Unique Paths](https://leetcode.com/problems/unique-paths/)
- [64. Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)
- [300. Longest Increasing Subsequence](https://leetcode.com/problems/longest-increasing-subsequence/)
- [322. Coin Change](https://leetcode.com/problems/coin-change/)

### **Hard Level**
- [72. Edit Distance](https://leetcode.com/problems/edit-distance/)
- [174. Dungeon Game](https://leetcode.com/problems/dungeon-game/)
- [312. Burst Balloons](https://leetcode.com/problems/burst-balloons/)

## 💡 **Key Insights**

### **1. State Definition**
```cpp
// Clearly define the state of DP
// dp[i][j] = result for subproblem from i to j
// dp[i] = result for subproblem ending at i
// dp[i][j][k] = result with constraint k
```

### **2. Transition Formula**
```cpp
// Write the state transition formula
// dp[i] = max(dp[i-1], dp[i-2] + nums[i])  // House Robber
// dp[i][j] = min(dp[i-1][j], dp[i][j-1]) + grid[i][j]  // Min Path Sum
```

### **3. Base Cases**
```cpp
// Handle basic cases
if (i == 0 || j == 0) return 1;  // Unique Paths
if (n <= 1) return n;             // Fibonacci
if (capacity == 0) return 0;      // Knapsack
```

## 🎯 **C++23 Modern Implementation**

### **Using std::ranges and std::views**
```cpp
// Modern C++23 approach with ranges
auto solveDP = [&](const auto& nums) -> int {
    if (nums.empty()) return 0;
    if (nums.size() == 1) return nums[0];
    
    std::vector<int> dp(nums.size());
    dp[0] = nums[0];
    dp[1] = std::max(nums[0], nums[1]);
    
    // Use std::ranges::iota for iteration
    for (int i : std::views::iota(2, static_cast<int>(nums.size()))) {
        dp[i] = std::max(dp[i-1], dp[i-2] + nums[i]);
    }
    
    return dp.back();
};
```

### **Using std::accumulate for State Transitions**
```cpp
// Calculate DP state with std::accumulate
auto calculateDP = [&](const auto& weights, const auto& values, int capacity) -> int {
    std::vector<int> dp(capacity + 1, 0);
    
    for (size_t i = 0; i < weights.size(); ++i) {
        for (int w = capacity; w >= weights[i]; --w) {
            dp[w] = std::max(dp[w], dp[w - weights[i]] + values[i]);
        }
    }
    
    return std::ranges::max(dp);
};
```

## 📊 **Complexity Analysis**

| Pattern | Time | Space | Best For |
|---------|------|-------|----------|
| 1D DP | O(n) | O(n) | Linear problems |
| 2D DP | O(m×n) | O(m×n) | Matrix problems |
| Knapsack | O(n×W) | O(W) | Optimization problems |
| LIS | O(n²) | O(n) | Subsequence problems |

## 🎓 **Practice Problems by Category**

### **Linear DP**
1. [Climbing Stairs](https://leetcode.com/problems/climbing-stairs/)
2. [House Robber](https://leetcode.com/problems/house-robber/)
3. [Fibonacci Number](https://leetcode.com/problems/fibonacci-number/)

### **Matrix DP**
1. [Unique Paths](https://leetcode.com/problems/unique-paths/)
2. [Minimum Path Sum](https://leetcode.com/problems/minimum-path-sum/)
3. [Dungeon Game](https://leetcode.com/problems/dungeon-game/)

### **String DP**
1. [Longest Common Subsequence](https://leetcode.com/problems/longest-common-subsequence/)
2. [Edit Distance](https://leetcode.com/problems/edit-distance/)
3. [Longest Palindromic Substring](https://leetcode.com/problems/longest-palindromic-substring/)

### **Optimization DP**
1. [Coin Change](https://leetcode.com/problems/coin-change/)
2. [0/1 Knapsack](https://leetcode.com/problems/ones-and-zeroes/)
3. [Burst Balloons](https://leetcode.com/problems/burst-balloons/)

## 🔗 **Related Patterns**
- **Greedy** - Choose optimal at each step
- **Divide and Conquer** - Break down problem into smaller parts
- **Backtracking** - Try all possibilities
- **Graph Algorithms** - Shortest path, tree problems

## 🚀 **Optimization Tips**

### **1. State Compression**
```cpp
// Use bit manipulation for state
// dp[mask] instead of dp[i][j][k]
```

### **2. Rolling Array**
```cpp
// Only store two rows for 2D DP
vector<int> curr(n), prev(n);
```

### **3. Early Termination**
```cpp
// Terminate early if possible
if (dp[i] >= target) break;
```

---

**Remember**: DP needs practice to identify patterns. Solve many problems to become proficient! 🚀
