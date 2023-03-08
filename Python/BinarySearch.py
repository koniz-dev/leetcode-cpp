class Solution(object):
    def search(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """
        lpos = 0
        rpos = len(nums) - 1

        while lpos <= rpos:
            mid = (lpos + rpos) / 2

            if nums[mid] == target: return mid
            if nums[mid] < target:
                lpos = mid + 1
            else:
                rpos = mid - 1

        return -1
    
# Python3
class Solution:
    def search(self, nums: List[int], target: int) -> int:
        lpos = 0
        rpos = len(nums) - 1

        while lpos <= rpos:
            mid = (lpos + rpos) // 2

            if nums[mid] == target: return mid
            if nums[mid] < target:
                lpos = mid + 1
            else:
                rpos = mid - 1

        return -1