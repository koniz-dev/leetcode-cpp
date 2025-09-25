#include <vector>
using namespace std;

class Solution {
public:
    /*
     * Product of Array Except Self - Optimized Solution using Array Manipulation
     * 
     * Approach:
     * - First pass: Calculate left products and store in result array
     * - Second pass: Calculate right products on-the-fly and multiply with left products
     * - This eliminates the need for separate prefix and suffix arrays
     * 
     * Time Complexity: O(n) - Two passes through the array
     * Space Complexity: O(1) - Only using the result array (excluding input/output)
     */
    vector<int> productExceptSelf(vector<int>& nums) {
        const int n = nums.size();
        vector<int> result(n);
        
        // First pass: Calculate left products
        // result[i] = product of all elements to the left of i
        result[0] = 1;
        for (int i = 1; i < n; ++i) {
            result[i] = result[i - 1] * nums[i - 1];
        }
        
        // Second pass: Calculate right products and multiply with left products
        // Use a variable to track right product to avoid extra space
        int rightProduct = 1;
        for (int i = n - 1; i >= 0; --i) {
            result[i] *= rightProduct;  // Multiply left product with right product
            rightProduct *= nums[i];    // Update right product for next iteration
        }
        
        return result;
    }
};
