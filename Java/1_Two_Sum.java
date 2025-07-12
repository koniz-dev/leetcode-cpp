import java.util.HashMap;
import java.util.Map;

public class Solution {
    public int[] twoSum(int[] nums, int target) {
        Map<Integer, Integer> result = new HashMap<>();
        for (int i = 0; i < nums.length; i++) {
            int complement = target - nums[i];
            if (result.containsKey(complement)) {
                return new int[]{result.get(complement), i};
            } else {
                result.put(nums[i], i);
            }
        }
        return null;
    }
}
