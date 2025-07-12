object Solution {
    def twoSum(nums: Array[Int], target: Int): Array[Int] = {
        val numIndices = scala.collection.mutable.Map[Int, Int]()
        var result: Array[Int] = Array()
        scala.util.control.Breaks.breakable {
            for (i <- nums.indices) {
                val complement = target - nums(i)
                if (numIndices.contains(complement)) {
                    result = Array(numIndices(complement), i)
                    scala.util.control.Breaks.break()
                }
                numIndices(nums(i)) = i
            }
        }
        result
    }
}