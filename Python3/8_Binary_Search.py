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
        lpos: int = 0
        rpos: int = len(nums) - 1
        while lpos <= rpos:
            mid: int = (lpos + rpos) // 2
            if nums[mid] == target: 
                return mid
            if nums[mid] < target:
                lpos = mid + 1
            else:
                rpos = mid - 1
        return -1
