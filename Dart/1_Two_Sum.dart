class Solution {
  List<int> twoSum(List<int> nums, int target) {
    Map<int, int> numIndices = {};
    for (int i = 0; i < nums.length; i++) {
      int complement = target - nums[i];
      if (numIndices.containsKey(complement)) {
        return [numIndices[complement]!, i];
      }
      numIndices[nums[i]] = i;
    }
    return [];
  }
}