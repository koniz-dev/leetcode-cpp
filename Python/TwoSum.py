class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        temp = {}

        for index, value in enumerate(nums):
            j = target - value
            if j in temp: return [temp[j], index]
            temp[value] = index

# Python3
class Solution:
    def twoSum(self, nums: List[int], target: int) -> List[int]:
        temp = {}

        for index, value in enumerate(nums):
            j = target - value
            if j in temp: return [temp[j], index]
            temp[value] = index