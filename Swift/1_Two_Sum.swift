class Solution {
    func twoSum(_ nums: [Int], _ target: Int) -> [Int] {
        var numIndices = [Int: Int]()
        for (index, num) in nums.enumerated() {
            let complement = target - num
            if let complementIndex = numIndices[complement] {
                return [complementIndex, index]
            }
            numIndices[num] = index
        }
        return []
    }
}
