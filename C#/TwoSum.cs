public class Solution {
    public int[] TwoSum(int[] nums, int target) {
        Dictionary<int, int> result = new Dictionary<int, int>();

        for (int i = 0; i < nums.Length; i++) {
            int j = target - nums[i];

            if (result.ContainsKey(j)) {
                return new []{result[j], i};
            }
            else {
                result[nums[i]] = i;
            }
            
        }

        return null;
    }
}