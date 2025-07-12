class Solution {
public:
    int search(vector<int>& nums, int target) {
        int lpos = 0, rpos = nums.size() - 1, mid = 0;
        while (lpos <= rpos) {
            mid = (lpos + rpos) / 2;
            if (nums[mid] == target) 
                return mid;
            (nums[mid] < target) ? (lpos = mid + 1) : (rpos = mid - 1);
        }
        return -1;
    }
};
