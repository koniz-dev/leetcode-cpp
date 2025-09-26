# 36. Valid Sudoku

## Problem Statement
Determine if a 9x9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:

1. Each row must contain the digits 1-9 without repetition
2. Each column must contain the digits 1-9 without repetition  
3. Each of the nine 3x3 sub-boxes must contain the digits 1-9 without repetition

**Note:**
- A Sudoku board (partially filled) could be valid but is not necessarily solvable
- Only the filled cells need to be validated according to the mentioned rules

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

**Explanation:** This is a valid Sudoku board. All filled cells follow the rules:
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

## DSA Concepts Used

### 1. Hash Set / Set Data Structure
- **Purpose**: Track seen numbers efficiently with O(1) lookup and insertion
- **Implementation**: Using `bitset<9>` for space efficiency
- **Why Important**: Avoids nested loops for duplicate checking

### 2. Mathematical Indexing
- **Purpose**: Convert 2D coordinates to 1D box index
- **Formula**: `boxIndex = (row / 3) * 3 + (col / 3)`
- **Why Important**: Enables single-pass validation

### 3. Bit Manipulation
- **Purpose**: Efficient storage and operations on sets of 9 elements
- **Benefits**: Space-efficient (9 bits vs 9 booleans), fast operations
- **Modern C++**: `bitset<9>` provides clean interface

## Solution Approaches

### Approach 1: Three Separate Passes (Original)
```cpp
// Check rows, then columns, then boxes separately
// Time: O(1), Space: O(1) - but 3 passes through board
```

**Pros:**
- Simple to understand and implement
- Clear separation of concerns

**Cons:**
- Three separate passes through the board
- More code duplication
- Less efficient than single-pass solution

### Approach 2: Single Pass with Hash Sets (Optimized)
```cpp
// Use three arrays of bitsets for rows, columns, and boxes
// Single pass with O(1) operations
```

**Pros:**
- Single pass through the board
- Most efficient time complexity
- Clean, readable code
- Space-efficient using bitsets

**Cons:**
- Slightly more complex logic
- Requires understanding of mathematical indexing

### Approach 3: Hash Set with Strings (Alternative)
```cpp
// Use unordered_set<string> to track "row:num", "col:num", "box:num"
```

**Pros:**
- Very readable and intuitive
- Easy to debug

**Cons:**
- Higher space complexity due to string overhead
- Slower due to string operations

## Complexity Analysis

### Time Complexity: O(1)
- **Explanation**: Fixed 81 cells to check, each with O(1) operations
- **Operations**: 81 iterations × (3 lookups + 3 insertions) = constant time

### Space Complexity: O(1)
- **Explanation**: Fixed space for 27 bitsets (9 rows + 9 cols + 9 boxes)
- **Storage**: 27 × 9 bits = 243 bits ≈ 30 bytes

## Step-by-Step Execution

### Example 1 Execution (Valid Board)
Let's trace through the optimized solution with the valid board:

```cpp
// Initialize: rows[9], cols[9], boxes[9] all empty bitsets

// Check position (0,0): board[0][0] = '5'
num = '5' - '1' = 4
boxIndex = (0/3)*3 + (0/3) = 0
// Check: rows[0][4], cols[0][4], boxes[0][4] all false ✓
// Set: rows[0].set(4), cols[0].set(4), boxes[0].set(4)

// Check position (0,1): board[0][1] = '3'  
num = '3' - '1' = 2
boxIndex = (0/3)*3 + (1/3) = 0
// Check: rows[0][2], cols[1][2], boxes[0][2] all false ✓
// Set: rows[0].set(2), cols[1].set(2), boxes[0].set(2)

// Continue for all filled cells...
// Result: All checks pass, return true
```

### Example 2 Execution (Invalid Board)
```cpp
// Check position (0,0): board[0][0] = '8'
num = '8' - '1' = 7
boxIndex = (0/3)*3 + (0/3) = 0
// Check: rows[0][7], cols[0][7], boxes[0][7] all false ✓
// Set: rows[0].set(7), cols[0].set(7), boxes[0].set(7)

// Check position (2,2): board[2][2] = '8'
num = '8' - '1' = 7  
boxIndex = (2/3)*3 + (2/3) = 0  // Same box as (0,0)!
// Check: rows[2][7], cols[2][7] false ✓, but boxes[0][7] true ✗
// Return false immediately - duplicate found in box 0
```

## Key Learning Points

### 1. Mathematical Indexing for 2D to 1D Conversion
```cpp
// Convert (row, col) to box index
int boxIndex = (row / 3) * 3 + (col / 3);

// Example: (4, 7) -> (4/3)*3 + (7/3) = 1*3 + 2 = 5
// Box 5 is the middle-right 3x3 box
```

### 2. Bitset for Efficient Set Operations
```cpp
bitset<9> seen;           // 9 bits for numbers 0-8
seen.set(num);           // Mark number as seen
if (seen[num]) { ... }   // Check if number seen
```

### 3. Single-Pass Optimization
- Instead of checking rows, then columns, then boxes separately
- Check all three conditions simultaneously in one pass
- Reduces time complexity from 3×O(1) to O(1)

## Modern C++ Features Used

### 1. `std::array` with `std::bitset`
```cpp
array<bitset<9>, 9> rows{}, cols{}, boxes{};
```
- **Benefits**: Stack allocation, compile-time size, zero initialization
- **Alternative**: `vector<bitset<9>>` (heap allocation)

### 2. Range-based for loops
```cpp
for (int i = 0; i < 9; ++i) {
    for (int j = 0; j < 9; ++j) {
        // Process board[i][j]
    }
}
```

### 3. Efficient Character to Number Conversion
```cpp
int num = board[i][j] - '1';  // Convert '1'-'9' to 0-8
```

## Common Pitfalls

### 1. Off-by-One Errors
- **Problem**: Using `board[i][j] - '0'` gives 1-9, but array indices are 0-8
- **Solution**: Use `board[i][j] - '1'` for 0-based indexing

### 2. Box Index Calculation
- **Problem**: Incorrect formula for 3x3 box indexing
- **Solution**: `(row/3)*3 + (col/3)` correctly maps to 0-8 box indices

### 3. Space vs Time Trade-offs
- **Problem**: Using boolean arrays instead of bitsets
- **Solution**: Bitsets provide same functionality with less space

## Related Problems
- [37. Sudoku Solver](https://leetcode.com/problems/sudoku-solver/) - Solve the sudoku
- [51. N-Queens](https://leetcode.com/problems/n-queens/) - Similar constraint satisfaction
- [52. N-Queens II](https://leetcode.com/problems/n-queens-ii/) - Count solutions

## Practice Recommendations
1. **Implement all three approaches** to understand trade-offs
2. **Practice box indexing** with different coordinate examples
3. **Experiment with bitset operations** for set manipulation
4. **Try solving Sudoku Solver** to apply validation logic
