class Solution {
  List<int> twoSum(List<int> nums, int target) {
    // Create a map to store the indices of numbers
    Map<int, int> numIndices = {};

    // Iterate through the array of numbers
    for (int i = 0; i < nums.length; i++) {
      // Calculate the complement needed to achieve the target
      int complement = target - nums[i];

      // If the complement exists in the map, return the indices of the current number and its complement
      if (numIndices.containsKey(complement)) {
        return [numIndices[complement]!, i];
      }

      // Store the current number's index for future reference
      numIndices[nums[i]] = i;
    }

    // If no solution is found, return an empty list
    return [];
  }
}