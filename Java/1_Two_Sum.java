import java.util.HashMap;
import java.util.Map;

public class Solution {
    public int[] twoSum(int[] nums, int target) {
        // Create a map to store numbers and their indices
        Map<Integer, Integer> result = new HashMap<>();

        // Iterate through the array
        for (int i = 0; i < nums.length; i++) {
            // Calculate the complement for the current number
            int complement = target - nums[i];

            // Check if the complement exists in the map
            if (result.containsKey(complement)) {
                // If found, return the indices of the two numbers
                return new int[]{result.get(complement), i};
            } else {
                // Otherwise, add the current number and its index to the map
                result.put(nums[i], i);
            }
        }

        // If no solution is found, return null
        return null;
    }
}
