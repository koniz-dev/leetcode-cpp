/**
 * @param {number[]} nums - The array of integers
 * @param {number} target - The target sum
 * @return {number[]} - The indices of the two numbers that add up to the target
 */
var twoSum = function (nums, target) {
  const result = {};
  for (let i = 0; i < nums.length; i++) {
    let temp = target - nums[i];
    if (result.hasOwnProperty(temp))
      return [result[temp], i];
    result[nums[i]] = i;
  }
};