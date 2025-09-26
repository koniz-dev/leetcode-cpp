#include <vector>
#include <array>
#include <bitset>
using namespace std;

class Solution {
public:
    /*
     * Valid Sudoku - Optimized Solution using Hash Sets and Bit Manipulation
     * 
     * Approach:
     * - Use three separate hash sets to track seen numbers in rows, columns, and 3x3 boxes
     * - Use bitset for efficient space usage (9 bits per set instead of 9 booleans)
     * - Single pass through the board with O(1) lookup and insertion
     * - Calculate 3x3 box index using mathematical formula: (row/3)*3 + (col/3)
     * 
     * Time Complexity: O(n²) where n = 9 - Must check all n×n cells
     * Space Complexity: O(n²) where n = 9 - Board storage + 27 bitsets (9 rows + 9 cols + 9 boxes)
     */
    bool isValidSudoku(vector<vector<char>>& board) {
        // Use bitset for efficient space usage - 9 bits per set
        array<bitset<9>, 9> rows{}, cols{}, boxes{};
        
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                if (board[i][j] == '.') continue;
                
                // Convert char to 0-based index (1-9 -> 0-8)
                int num = board[i][j] - '1';
                
                // Calculate 3x3 box index using mathematical formula
                int boxIndex = (i / 3) * 3 + (j / 3);
                
                // Check if number already exists in row, column, or box
                if (rows[i][num] || cols[j][num] || boxes[boxIndex][num]) {
                    return false;  // Duplicate found, invalid sudoku
                }
                
                // Mark number as seen in row, column, and box
                rows[i].set(num);
                cols[j].set(num);
                boxes[boxIndex].set(num);
            }
        }
        
        return true;  // All checks passed, valid sudoku
    }
};
