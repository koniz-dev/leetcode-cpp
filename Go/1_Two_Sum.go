func twoSum(nums []int, target int) []int {
    numIndices := make(map[int]int)
    for i, num := range nums {
        complement := target - num
        if complementIndex, ok := numIndices[complement]; ok {
            return []int{complementIndex, i}
        }
        numIndices[num] = i
    }
    return []int{}
}