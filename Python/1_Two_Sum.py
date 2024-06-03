class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        # Create a dictionary to store the number and its index
        temp = {}

        # Iterate through the array
        for index, value in enumerate(nums):
            # Calculate the difference needed to achieve the target
            j = target - value
            # Check if the difference exists in the dictionary
            if j in temp:
                # If found, return the indices of the two numbers
                return [temp[j], index]
            # Otherwise, store the current number and its index in the dictionary
            temp[value] = index