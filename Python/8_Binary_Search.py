class Solution(object):
    def search(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        # Initialize left and right pointers
        lpos = 0
        rpos = len(nums) - 1

        # Perform binary search
        while lpos <= rpos:
            # Calculate middle index
            mid = (lpos + rpos) // 2

            # Check if target is found
            if nums[mid] == target: 
                return mid
            
            # Adjust left and right pointers based on target and middle value
            if nums[mid] < target:
                lpos = mid + 1
            else:
                rpos = mid - 1

        # If target is not found, return -1
        return -1