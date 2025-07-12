// Solution 1: Binary Search Implementation
public class Solution {
    public int Search(int[] nums, int target) {
        int lpos = 0, rpos = nums.Length - 1, mid = 0;
        while (lpos <= rpos) {
            mid = (lpos + rpos) / 2;
            if (nums[mid] == target) 
                return mid;
            if (nums[mid] < target)
                lpos = mid + 1;
            else
                rpos = mid - 1;
        }
        return -1;
    }
}

// Solution 2: Using Array.BinarySearch
public class Solution {
    public int Search(int[] nums, int target) {
        int index = Array.BinarySearch(nums, target);
        if (index < 0)
            return -1;
        else
            return index;
    }
}
