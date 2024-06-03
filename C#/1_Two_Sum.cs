public class Solution {
    public int[] TwoSum(int[] nums, int target) {
        // Create a dictionary to store numbers and their indices
        Dictionary<int, int> result = new Dictionary<int, int>();

        // Iterate through the array
        for (int i = 0; i < nums.Length; i++) {
            // Calculate the complement for the current number
            int complement = target - nums[i];

            // Check if the complement exists in the dictionary
            if (result.ContainsKey(complement)) {
                // If found, return the indices of the two numbers
                return new [] { result[complement], i };
            } else {
                // Otherwise, add the current number and its index to the dictionary
                result[nums[i]] = i;
            }
        }

        // If no solution is found, return null
        return null;
    }
}
