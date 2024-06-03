from typing import List

class Solution:
    def search(self, nums: List[int], target: int) -> int:
        """
        Binary search algorithm to find the target in a sorted list.

        Args:
            nums: A list of integers representing the sorted array.
            target: The integer value to search for.

        Returns:
            The index of the target in the list if found, otherwise -1.
        """
        # Initialize left and right pointers
        lpos: int = 0
        rpos: int = len(nums) - 1

        # Perform binary search
        while lpos <= rpos:
            # Calculate middle index
            mid: int = (lpos + rpos) // 2

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
