from typing import List

class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        """
        Finds two numbers in the array that add up to the target.

        Args:
            nums: A list of integers.
            target: The target sum.

        Returns:
            A list of two indices corresponding to the numbers that add up to the target.
        """
        temp = {}
        for index, value in enumerate(nums):
            j = target - value
            if j in temp:
                return [temp[j], index]
            temp[value] = index
