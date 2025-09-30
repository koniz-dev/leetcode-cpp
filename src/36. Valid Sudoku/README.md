# [36. Valid Sudoku](https://leetcode.com/problems/valid-sudoku/)

## Problem Statement
Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

1. Each row must contain the digits 1-9 without repetition
2. Each column must contain the digits 1-9 without repetition  
3. Each of the nine 3x3 sub-boxes must contain the digits 1-9 without repetition

**Note:**
- A Sudoku board (partially filled) could be valid but is not necessarily solvable.
- Only the filled cells need to be validated according to the mentioned rules.

## Examples

### Example 1: Valid Sudoku
**Input:**
```
board = [
["5","3",".",".","7",".",".",".","."],
["6",".",".","1","9","5",".",".","."],
[".","9","8",".",".",".",".","6","."],
["8",".",".",".","6",".",".",".","3"],
["4",".",".","8",".","3",".",".","1"],
["7",".",".",".","2",".",".",".","6"],
[".","6",".",".",".",".","2","8","."],
[".",".",".","4","1","9",".",".","5"],
[".",".",".",".","8",".",".","7","9"]
]
```

**Output:** `true`

**Explanation:** This is a valid Sudoku board. All filled cells follow the three rules:
- No duplicate numbers in any row
- No duplicate numbers in any column  
- No duplicate numbers in any 3x3 sub-box

### Example 2: Invalid Sudoku
**Input:**
```
board = [
["8","3",".",".","7",".",".",".","."],
["6",".",".","1","9","5",".",".","."],
[".","9","8",".",".",".",".","6","."],
["8",".",".",".","6",".",".",".","3"],
["4",".",".","8",".","3",".",".","1"],
["7",".",".",".","2",".",".",".","6"],
[".","6",".",".",".",".","2","8","."],
[".",".",".","4","1","9",".",".","5"],
[".",".",".",".","8",".",".","7","9"]
]
```

**Output:** `false`

**Explanation:** Same as Example 1, except with the 5 in the top left corner being modified to 8. Since there are two 8's in the top left 3x3 sub-box, it is invalid.

**Visual Analysis:**
```
Top-left 3x3 box:
8 3 .     ← Two 8's in this box!
6 . .     ← Invalid!
. 9 8
```

## Solutions

### 1. Optimized Solution (Single Pass with Bitsets) - `optimized.cpp`
**Time Complexity:** O(n²) where n = 9 (board size)  
**Space Complexity:** O(n²) where n = 9 (board size)

Uses three arrays of `bitset<9>` to track seen numbers in rows, columns, and 3x3 boxes. Single pass through the board with mathematical box indexing.

**Key DSA Concepts:**
- **Hash Set Technique**: Using bitsets for O(1) lookup and insertion
- **Mathematical Indexing**: Convert 2D coordinates to 1D box index using `(row/3)*3 + (col/3)`
- **Single Pass Algorithm**: Check all three conditions simultaneously
- **Bit Manipulation**: Efficient storage using 9 bits per set instead of 9 booleans

**Key C++ Concepts Used:**
- `array<bitset<9>, 9>` - Fixed-size arrays of bitsets for efficient space usage
- `bitset<9>` - Bit manipulation for set operations
- Character arithmetic (`board[i][j] - '1'`) for 0-based indexing
- Mathematical box indexing formula

### 2. Three Separate Passes (Current Implementation) - `main.cpp`
**Time Complexity:** O(n²) where n = 9 (board size)  
**Space Complexity:** O(n²) where n = 9 (board size)

Checks rows, then columns, then 3x3 boxes in separate passes. Simple but less efficient than single-pass solution.

**Key DSA Concepts:**
- **Multiple Pass Algorithm**: Separate validation for each constraint
- **Boolean Arrays**: Using `bool seen[10]` for tracking duplicates
- **Nested Loop Structure**: Different loop patterns for different constraints

**Key C++ Concepts Used:**
- `bool seen[10]` - Fixed-size boolean arrays
- Nested for loops with different step sizes
- Character to integer conversion (`board[i][j] - '0'`)

### 3. Hash Set with Strings (Alternative)
**Time Complexity:** O(n²) where n = 9 (board size)  
**Space Complexity:** O(n²) where n = 9 (board size)

Uses `unordered_set<string>` to track "row:num", "col:num", "box:num" combinations.

```cpp
bool isValidSudoku(vector<vector<char>>& board) {
    unordered_set<string> seen;
    
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (board[i][j] == '.') continue;
            
            string num = string(1, board[i][j]);
            
            // Create unique identifiers for row, column, and box
            string rowKey = "row" + to_string(i) + num;
            string colKey = "col" + to_string(j) + num;
            string boxKey = "box" + to_string((i/3)*3 + (j/3)) + num;
            
            // Check if any identifier already exists
            if (seen.count(rowKey) || seen.count(colKey) || seen.count(boxKey)) {
                return false;
            }
            
            // Add all three identifiers to the set
            seen.insert(rowKey);
            seen.insert(colKey);
            seen.insert(boxKey);
        }
    }
    
    return true;
}
```

**Key Points:**
- Very readable and intuitive approach
- Higher space complexity due to string overhead
- Slower due to string operations
- Easy to understand and debug

## DSA Knowledge Points

### Hash Set Techniques
- **Duplicate Detection**: Using hash sets for O(1) lookup time
- **Mathematical Indexing**: Converting 2D coordinates to 1D indices
- **Bit Manipulation**: Using bitsets for efficient set operations

### Optimization Techniques
- **Single Pass**: Check all constraints simultaneously
- **Early Exit**: Return false as soon as duplicate is found
- **Space Efficiency**: Use bitsets instead of boolean arrays

### Algorithm Analysis
- **Time Complexity**: O(n²) where n = 9 - must check all n×n cells
- **Space Complexity**: O(n²) where n = 9 - board storage + tracking sets
- **Input Constraints**: Leveraging fixed 9x9 board size for optimization

## C++ Knowledge Points

### Containers
- **`array<bitset<9>, 9>`**: Fixed-size arrays of bitsets for efficient space usage
- **`bitset<9>`**: Bit manipulation for set operations
- **`vector<vector<char>>`**: 2D vector for board representation

### C++ Features
- **Character arithmetic**: `board[i][j] - '1'` for 0-based indexing
- **Mathematical operations**: Box index calculation `(row/3)*3 + (col/3)`
- **STL containers**: Using standard library for efficient operations

### Memory Management
- **Stack allocation**: Fixed-size arrays for small, known ranges
- **Efficient iteration**: Single pass through the board

## Related Problems
- [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) - Solve the sudoku
- [51. N-Queens](https://leetcode.com/problems/n-queens/) - Similar constraint satisfaction
- [52. N-Queens II](https://leetcode.com/problems/n-queens-ii/) - Count solutions

## Practice Tips
1. **Understand box indexing** - practice converting (row,col) to box index
2. **Consider space vs time trade-offs** - bitsets vs boolean arrays
3. **Think about early termination** - return false as soon as duplicate found
4. **Use appropriate data structures** - bitsets for small sets, hash maps for larger
5. **Master mathematical indexing** - essential for 2D to 1D conversions

## Learning Objectives
- Master hash set techniques for duplicate detection
- Understand mathematical indexing for 2D problems
- Learn bit manipulation with bitsets
- Practice single-pass optimization strategies
- Develop intuition for constraint satisfaction problems
