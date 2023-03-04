/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var twoSum = function(nums, target) {
    const result = {}

    for (let i = 0; i < nums.length; i++) {
        let temp = target - nums[i]

        if (result.hasOwnProperty(temp)) return [result[temp], i]
        result[nums[i]] = i
    }
};