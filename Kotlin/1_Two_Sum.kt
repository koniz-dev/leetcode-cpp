class Solution {
    fun twoSum(nums: IntArray, target: Int): IntArray {
        val numIndices = mutableMapOf<Int, Int>()
        for (i in nums.indices) {
            val complement = target - nums[i]
            if (numIndices.containsKey(complement)) {
                return intArrayOf(numIndices[complement]!!, i)
            }
            numIndices[nums[i]] = i
        }
        return intArrayOf()
    }
}
