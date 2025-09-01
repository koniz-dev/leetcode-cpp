# 🔄 Backtracking

## 📚 Overview
**Backtracking** is an algorithmic technique that tries all possible solutions to find one that satisfies the conditions. It uses systematic "trial and error".

## 🎯 **When to Use**
- **Combinatorial problems** - Find all combinations, permutations
- **Constraint satisfaction** - Sudoku, N-Queens, coloring
- **Path finding** - Find paths in maze, graph
- **Subset problems** - Find all subsets satisfying conditions
- **Optimization problems** - Find optimal solutions

## 🚀 **Core Pattern**

### **1. Basic Backtracking Template**
```cpp
void backtrack(vector<int>& nums, vector<int>& path, vector<vector<int>>& result) {
    // Base case - solution found
    if (isValidSolution(path)) {
        result.push_back(path);
        return;
    }
    
    // Try all possible choices
    for (int i = 0; i < nums.size(); i++) {
        // Skip invalid choices
        if (isValidChoice(nums[i], path)) {
            // Make choice
            path.push_back(nums[i]);
            
            // Recurse
            backtrack(nums, path, result);
            
            // Undo choice (backtrack)
            path.pop_back();
        }
    }
}
```

**Time Complexity**: O(branching_factor^depth)  
**Space Complexity**: O(depth) - Recursion stack

### **2. Subsets Generation**
```cpp
// Find all subsets of array
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> path;
    
    backtrackSubsets(nums, 0, path, result);
    return result;
}

void backtrackSubsets(vector<int>& nums, int start, vector<int>& path, 
                     vector<vector<int>>& result) {
    // Add current path to result
    result.push_back(path);
    
    // Try all remaining elements
    for (int i = start; i < nums.size(); i++) {
        path.push_back(nums[i]);
        backtrackSubsets(nums, i + 1, path, result);
        path.pop_back();
    }
}
```

### **3. Permutations Generation**
```cpp
// Find all permutations of array
vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    vector<int> path;
    vector<bool> used(nums.size(), false);
    
    backtrackPermute(nums, used, path, result);
    return result;
}

void backtrackPermute(vector<int>& nums, vector<bool>& used, vector<int>& path,
                     vector<vector<int>>& result) {
    // Base case
    if (path.size() == nums.size()) {
        result.push_back(path);
        return;
    }
    
    // Try all unused elements
    for (int i = 0; i < nums.size(); i++) {
        if (!used[i]) {
            used[i] = true;
            path.push_back(nums[i]);
            
            backtrackPermute(nums, used, path, result);
            
            used[i] = false;
            path.pop_back();
        }
    }
}
```

## 🔍 **Advanced Patterns**

### **1. N-Queens Problem**
```cpp
// Solve N-Queens problem
vector<vector<string>> solveNQueens(int n) {
    vector<vector<string>> result;
    vector<string> board(n, string(n, '.'));
    vector<bool> cols(n, false);
    vector<bool> diag1(2*n-1, false);  // Main diagonal
    vector<bool> diag2(2*n-1, false);  // Anti-diagonal
    
    backtrackNQueens(n, 0, board, cols, diag1, diag2, result);
    return result;
}

void backtrackNQueens(int n, int row, vector<string>& board,
                     vector<bool>& cols, vector<bool>& diag1, vector<bool>& diag2,
                     vector<vector<string>>& result) {
    if (row == n) {
        result.push_back(board);
        return;
    }
    
    for (int col = 0; col < n; col++) {
        if (isValidPosition(row, col, cols, diag1, diag2, n)) {
            // Place queen
            board[row][col] = 'Q';
            cols[col] = diag1[row+col] = diag2[row-col+n-1] = true;
            
            backtrackNQueens(n, row + 1, board, cols, diag1, diag2, result);
            
            // Remove queen
            board[row][col] = '.';
            cols[col] = diag1[row+col] = diag2[row-col+n-1] = false;
        }
    }
}

bool isValidPosition(int row, int col, vector<bool>& cols, vector<bool>& diag1,
                    vector<bool>& diag2, int n) {
    return !cols[col] && !diag1[row+col] && !diag2[row-col+n-1];
}
```

### **2. Sudoku Solver**
```cpp
// Solve Sudoku
void solveSudoku(vector<vector<char>>& board) {
    solveSudokuHelper(board);
}

bool solveSudokuHelper(vector<vector<char>>& board) {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == '.') {
                // Try all digits 1-9
                for (char digit = '1'; digit <= '9'; digit++) {
                    if (isValidSudoku(board, row, col, digit)) {
                        board[row][col] = digit;
                        
                        if (solveSudokuHelper(board)) {
                            return true;  // Solution found
                        }
                        
                        board[row][col] = '.';  // Backtrack
                    }
                }
                return false;  // No valid digit found
            }
        }
    }
    return true;  // All cells filled
}

bool isValidSudoku(vector<vector<char>>& board, int row, int col, char digit) {
    // Check row
    for (int c = 0; c < 9; c++) {
        if (board[row][c] == digit) return false;
    }
    
    // Check column
    for (int r = 0; r < 9; r++) {
        if (board[r][col] == digit) return false;
    }
    
    // Check 3x3 box
    int boxRow = 3 * (row / 3);
    int boxCol = 3 * (col / 3);
    for (int r = boxRow; r < boxRow + 3; r++) {
        for (int c = boxCol; c < boxCol + 3; c++) {
            if (board[r][c] == digit) return false;
        }
    }
    
    return true;
}
```

### **3. Combination Sum**
```cpp
// Find all combinations with sum equal to target
vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    vector<vector<int>> result;
    vector<int> path;
    
    // Sort to avoid duplicate combinations
    sort(candidates.begin(), candidates.end());
    
    backtrackCombinationSum(candidates, target, 0, path, result);
    return result;
}

void backtrackCombinationSum(vector<int>& candidates, int target, int start,
                           vector<int>& path, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(path);
        return;
    }
    
    if (target < 0) return;
    
    for (int i = start; i < candidates.size(); i++) {
        // Skip duplicates
        if (i > start && candidates[i] == candidates[i-1]) continue;
        
        path.push_back(candidates[i]);
        backtrackCombinationSum(candidates, target - candidates[i], i, path, result);
        path.pop_back();
    }
}
```

## 🔍 **Problem Examples**

### **Easy Level**
- [78. Subsets](https://leetcode.com/problems/subsets/)
- [46. Permutations](https://leetcode.com/problems/permutations/)
- [77. Combinations](https://leetcode.com/problems/combinations/)

### **Medium Level**
- [39. Combination Sum](https://leetcode.com/problems/combination-sum/)
- [40. Combination Sum II](https://leetcode.com/problems/combination-sum-ii/)
- [47. Permutations II](https://leetcode.com/problems/permutations-ii/)
- [51. N-Queens](https://leetcode.com/problems/n-queens/)

### **Hard Level**
- [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)
- [52. N-Queens II](https://leetcode.com/problems/n-queens-ii/)
- [980. Unique Paths III](https://leetcode.com/problems/unique-paths-iii/)

## 💡 **Key Insights**

### **1. State Management**
```cpp
// Manage current state
struct State {
    vector<int> path;
    int currentSum;
    int remainingTarget;
    vector<bool> used;
    
    State() : currentSum(0), remainingTarget(0) {}
};

void backtrackWithState(State& state, vector<vector<int>>& result) {
    if (state.remainingTarget == 0) {
        result.push_back(state.path);
        return;
    }
    
    // Process current state...
}
```

### **2. Pruning (Pruning)**
```cpp
// Stop early if no solution is found
void backtrackWithPruning(vector<int>& nums, int target, int start,
                         vector<int>& path, vector<vector<int>>& result) {
    // Early termination
    if (target < 0) return;
    
    // Pruning: if remaining sum is too large
    int remainingSum = 0;
    for (int i = start; i < nums.size(); i++) {
        remainingSum += nums[i];
    }
    if (remainingSum < target) return;
    
    // Continue with normal backtracking...
}
```

### **3. Duplicate Handling**
```cpp
// Handle duplicates in combinations
void backtrackNoDuplicates(vector<int>& nums, int target, int start,
                          vector<int>& path, vector<vector<int>>& result) {
    if (target == 0) {
        result.push_back(path);
        return;
    }
    
    for (int i = start; i < nums.size(); i++) {
        // Skip duplicates
        if (i > start && nums[i] == nums[i-1]) continue;
        
        path.push_back(nums[i]);
        backtrackNoDuplicates(nums, target - nums[i], i + 1, path, result);
        path.pop_back();
    }
}
```

## 🎯 **C++23 Modern Implementation**

### **Using std::ranges and std::views**
```cpp
// Modern C++23 approach with ranges
auto generateSubsets = [&](const auto& nums) -> std::vector<std::vector<int>> {
    std::vector<std::vector<int>> result;
    std::vector<int> path;
    
    auto backtrack = [&](auto&& self, int start) -> void {
        result.push_back(path);
        
        for (int i : std::views::iota(start, static_cast<int>(nums.size()))) {
            path.push_back(nums[i]);
            self(self, i + 1);
            path.pop_back();
        }
    };
    
    backtrack(backtrack, 0);
    return result;
};
```

### **Using std::function for Backtracking Strategy**
```cpp
// Strategy pattern for backtracking
using BacktrackStrategy = std::function<void(const std::vector<int>&, int, std::vector<int>&)>;

auto createBacktrackStrategy(const std::string& type) -> BacktrackStrategy {
    if (type == "subsets") {
        return [](const auto& nums, int start, auto& path) {
            // Subsets logic
        };
    } else if (type == "permutations") {
        return [](const auto& nums, int start, auto& path) {
            // Permutations logic
        };
    }
    
    return [](const auto&, int, auto&) {};
}
```

## 📊 **Complexity Analysis**

| Pattern | Time | Space | Best For |
|---------|------|-------|----------|
| Subsets | O(2^n) | O(n) | Combination problems |
| Permutations | O(n!) | O(n) | Ordering problems |
| N-Queens | O(n^n) | O(n) | Constraint satisfaction |
| Sudoku | O(9^(n²)) | O(n²) | Grid problems |

## 🎓 **Practice Problems by Category**

### **Subset Problems**
1. [Subsets](https://leetcode.com/problems/subsets/)
2. [Subsets II](https://leetcode.com/problems/subsets-ii/)
3. [Combination Sum](https://leetcode.com/problems/combination-sum/)

### **Permutation Problems**
1. [Permutations](https://leetcode.com/problems/permutations/)
2. [Permutations II](https://leetcode.com/problems/permutations-ii/)
3. [Next Permutation](https://leetcode.com/problems/next-permutation/)

### **Constraint Satisfaction**
1. [N-Queens](https://leetcode.com/problems/n-queens/)
2. [Sudoku Solver](https://leetcode.com/problems/sudoku-solver/)
3. [Valid Sudoku](https://leetcode.com/problems/valid-sudoku/)

### **Path Finding**
1. [Unique Paths III](https://leetcode.com/problems/unique-paths-iii/)
2. [Word Search](https://leetcode.com/problems/word-search/)
3. [Word Search II](https://leetcode.com/problems/word-search-ii/)

## 🔗 **Related Patterns**
- **DFS** - Depth-first search on graph/tree
- **Dynamic Programming** - Memoization for overlapping subproblems
- **Greedy** - Heuristics to reduce search space
- **Bit Manipulation** - State compression for small problems

## 🚀 **Optimization Tips**

### **1. Early Termination**
```cpp
// Stop early if possible
if (path.size() > maxLength) return;
if (currentSum > target) return;
```

### **2. State Compression**
```cpp
// Use bit manipulation for small problems
unsigned int used = 0;  // 32 bits for 32 elements
used |= (1 << i);       // Mark as used
used &= ~(1 << i);      // Mark as unused
```

### **3. Memoization**
```cpp
// Cache results to avoid recalculating
unordered_map<string, bool> memo;

bool canSolve(string state) {
    if (memo.count(state)) return memo[state];
    
    bool result = solveBacktracking(state);
    memo[state] = result;
    return result;
}
```

---

**Remember**: Backtracking needs practice to identify patterns and optimize. Practice to become proficient! 🚀
