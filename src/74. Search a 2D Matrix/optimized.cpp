#include <vector>
using namespace std;

class Solution {
public:
    /*
     * Search a 2D Matrix - Optimized Solution using Binary Search
     * 
     * Approach:
     * - Treat the 2D matrix as a flattened 1D sorted array
     * - Use binary search on the virtual flattened array
     * - Convert 1D index to 2D coordinates: row = index / n, col = index % n
     * - Compare middle element with target to determine search direction
     * - If middle element equals target, return true
     * - If middle element is less than target, search right half
     * - If middle element is greater than target, search left half
     * - Continue until left > right, indicating target not found
     * 
     * Time Complexity: O(log(m*n)) - Binary search on m*n elements
     * Space Complexity: O(1) - Only using constant extra space for pointers
     */
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int m = matrix.size();        // Number of rows
        int n = matrix[0].size();    // Number of columns
        
        // Treat matrix as flattened 1D array: total elements = m * n
        int left = 0;                 // Left boundary (first element in flattened array)
        int right = m * n - 1;        // Right boundary (last element in flattened array)
        
        // Binary search on the virtual flattened array
        while (left <= right) {
            // Calculate middle index in flattened array
            int mid = left + (right - left) / 2;
            
            // Convert 1D index to 2D coordinates
            // row = mid / n (integer division gives row number)
            // col = mid % n (remainder gives column number)
            int cell = matrix[mid / n][mid % n];
            
            // Found the target
            if (cell == target) {
                return true;
            }
            // Target is in the right half (target > cell)
            else if (cell < target) {
                left = mid + 1;  // Narrow search to right half, exclude mid
            }
            // Target is in the left half (target < cell)
            else {
                right = mid - 1; // Narrow search to left half, exclude mid
            }
        }
        
        // Target not found in the matrix
        return false;
    }
};

