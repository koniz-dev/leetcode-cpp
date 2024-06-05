func twoSum(nums []int, target int) []int {
    // Create a map to store the indices of numbers
    numIndices := make(map[int]int)
    
    // Iterate through the array of numbers
    for i, num := range nums {
        // Calculate the complement needed to achieve the target
        complement := target - num
        
        // If the complement exists in the map, return the indices of the current number and its complement
        if complementIndex, ok := numIndices[complement]; ok {
            return []int{complementIndex, i}
        }
        
        // Store the current number's index for future reference
        numIndices[num] = i
    }
    
    // If no solution is found, return an empty slice
    return []int{}
}