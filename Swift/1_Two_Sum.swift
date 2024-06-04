class Solution {
    func twoSum(_ nums: [Int], _ target: Int) -> [Int] {
        var numIndices = [Int: Int]() // Create an empty dictionary to store the indices of numbers
        
        // Loop through the array of numbers
        for (index, num) in nums.enumerated() {
            // Calculate the complement needed to achieve the target
            let complement = target - num
            
            // If the complement exists in the dictionary, return the indices of the current number and its complement
            if let complementIndex = numIndices[complement] {
                return [complementIndex, index]
            }
            
            // Store the current number's index for future reference
            numIndices[num] = index
        }
        
        // If no solution is found, return an empty array
        return []
    }
}
