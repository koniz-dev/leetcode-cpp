public class Solution {
    public int[] TwoSum(int[] nums, int target) {
        Dictionary<int, int> result = new Dictionary<int, int>();
        for (int i = 0; i < nums.Length; i++) {
            int complement = target - nums[i];
            if (result.ContainsKey(complement)) {
                return new [] { result[complement], i };
            } else {
                result[nums[i]] = i;
            }
        }
        return null;
    }
}
