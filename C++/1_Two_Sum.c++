// Solution 1: Faster
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // Initialize vectors to store index and value pairs
        vector<int> index, value, result;
        // Iterator for finding the complement value
        std::vector<int>::iterator it;

        // Iterate through the array
        for(int i = 0; i < nums.size(); i++) {
            // Calculate the complement for the current number
            int complement = target - nums[i];

            // Find the complement in the 'value' vector
            it = std::find(value.begin(), value.end(), complement);
            // If found, add the indices to the result vector
            if (it != value.end()) {
                result.push_back(index[it - value.begin()]);
                result.push_back(i);
                break; // Exit loop as we found the solution
            }
            else {
                // Otherwise, add the current number and its index to the vectors
                value.push_back(nums[i]);
                index.push_back(i);
            }
        }
        return result;
    }
};

// Solution 2: Slower
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> result;
        
        // Iterate through the array
        for(int i = 0; i < nums.size() - 1; i++) {
            // Iterate through the remaining elements
            for(int j = i + 1; j < nums.size(); j++) {
                // If the sum of two numbers equals the target, add their indices to the result vector
                if (nums[i] + nums[j] == target) {
                    result.push_back(i);
                    result.push_back(j);
                    break; // Exit the inner loop if solution found
                }
            }
        }
        
        return result;
    }
};
