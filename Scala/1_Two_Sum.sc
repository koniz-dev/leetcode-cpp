object Solution {
    def twoSum(nums: Array[Int], target: Int): Array[Int] = {
        // Create a mutable map to store the indices of numbers
        val numIndices = scala.collection.mutable.Map[Int, Int]()
        var result: Array[Int] = Array()

        // Use scala.util.control.Breaks.breakable to allow breaking out of the loop
        scala.util.control.Breaks.breakable {
            // Iterate through the array of numbers
            for (i <- nums.indices) {
                // Calculate the complement needed to achieve the target
                val complement = target - nums(i)

                // If the complement exists in the map, set the result and break
                if (numIndices.contains(complement)) {
                    result = Array(numIndices(complement), i)
                    scala.util.control.Breaks.break()
                }

                // Store the current number's index for future reference
                numIndices(nums(i)) = i
            }
        }

        // Return the result array
        result
    }
}