#include <vector>
#include <unordered_set>
#include <iostream>

using namespace std;

class Solution {
public:
    // Most Efficient Solution: Using Hash Set
    // Time Complexity: O(n)
    // Space Complexity: O(n)
    bool containsDuplicate(vector<int>& nums) {
        unordered_set<int> seen;
        
        for (int num : nums) {
            if (seen.find(num) != seen.end()) {
                return true;
            }
            seen.insert(num);
        }
        
        return false;
    }
};

// Test cases
int main() {
    Solution solution;
    
    // Test Case 1: Contains duplicates
    vector<int> nums1 = {1, 2, 3, 1};
    cout << "Test 1: [1, 2, 3, 1] -> " << (solution.containsDuplicate(nums1) ? "true" : "false") << endl;
    
    // Test Case 2: No duplicates
    vector<int> nums2 = {1, 2, 3, 4};
    cout << "Test 2: [1, 2, 3, 4] -> " << (solution.containsDuplicate(nums2) ? "true" : "false") << endl;
    
    // Test Case 3: Multiple duplicates
    vector<int> nums3 = {1, 1, 1, 3, 3, 4, 3, 2, 4, 2};
    cout << "Test 3: [1, 1, 1, 3, 3, 4, 3, 2, 4, 2] -> " << (solution.containsDuplicate(nums3) ? "true" : "false") << endl;
    
    // Test Case 4: Empty array
    vector<int> nums4 = {};
    cout << "Test 4: [] -> " << (solution.containsDuplicate(nums4) ? "true" : "false") << endl;
    
    // Test Case 5: Single element
    vector<int> nums5 = {1};
    cout << "Test 5: [1] -> " << (solution.containsDuplicate(nums5) ? "true" : "false") << endl;
    
    return 0;
}
