// Solution 1: Binary Search Implementation
public class Solution {
    public int Search(int[] nums, int target) {
        // Initialize left and right pointers
        int lpos = 0, rpos = nums.Length - 1, mid = 0;

        // Perform binary search
        while (lpos <= rpos) {
            mid = (lpos + rpos) / 2; // Calculate middle index

            // Check if target is found
            if (nums[mid] == target) 
                return mid;
            
            // Adjust left and right pointers based on target and middle value
            if (nums[mid] < target)
                lpos = mid + 1; // Move to the right half
            else
                rpos = mid - 1; // Move to the left half
        }

        // If target is not found, return -1
        return -1;
    }
}

// Solution 2: Using Array.BinarySearch
public class Solution {
    public int Search(int[] nums, int target) {
        // Use built-in BinarySearch method
        int index = Array.BinarySearch(nums, target);

        // If index is negative, target is not found
        if (index < 0)
            return -1;
        else
            return index;
    }
}
