class Solution {
    fun twoSum(nums: IntArray, target: Int): IntArray {
        // Create a mutable map to store the indices of numbers
        val numIndices = mutableMapOf<Int, Int>()
        
        // Iterate through the array of numbers
        for (i in nums.indices) {
            // Calculate the complement needed to achieve the target
            val complement = target - nums[i]
            
            // If the complement exists in the map, return the indices of the current number and its complement
            if (numIndices.containsKey(complement)) {
                return intArrayOf(numIndices[complement]!!, i)
            }
            
            // Store the current number's index for future reference
            numIndices[nums[i]] = i
        }
        
        // If no solution is found, return an empty array
        return intArrayOf()
    }
}
