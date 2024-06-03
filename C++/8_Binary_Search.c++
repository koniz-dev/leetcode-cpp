class Solution {
public:
    int search(vector<int>& nums, int target) {
        // Initialize left and right pointers
        int lpos = 0, rpos = nums.size() - 1, mid = 0;

        // Perform binary search
        while (lpos <= rpos) {
            mid = (lpos + rpos) / 2; // Calculate middle index

            // Check if target is found
            if (nums[mid] == target) 
                return mid;

            // Adjust left and right pointers based on target and middle value
            // Ternary operator is used for concise code
            (nums[mid] < target) ? (lpos = mid + 1) : (rpos = mid - 1);
        }

        // If target is not found, return -1
        return -1;
    }
};
