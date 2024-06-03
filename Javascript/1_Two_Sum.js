/**
 * Solution 1: Faster
 * @param {number[]} nums - The array of integers
 * @param {number} target - The target sum
 * @return {number[]} - The indices of the two numbers that add up to the target
 */
var twoSum = function (nums, target) {
  // Create an object to store the number and its index
  const result = {};

  // Iterate through the array
  for (let i = 0; i < nums.length; i++) {
    // Calculate the difference needed to achieve the target
    let temp = target - nums[i];

    // Check if the difference exists in the object
    if (result.hasOwnProperty(temp))
      // If found, return the indices of the two numbers
      return [result[temp], i];

    // Otherwise, store the current number and its index in the object
    result[nums[i]] = i;
  }
};

/**
 * Solution 2: Slower
 * @param {number[]} nums - The array of integers
 * @param {number} target - The target sum
 * @return {number[]} - The indices of the two numbers that add up to the target
 */
var twoSum = function (nums, target) {
  // Create a Map to store the number and its index
  let store = new Map();
  let result = [];

  // Iterate through the array
  nums.forEach((item, index) => {
    // Check if the complement exists in the Map
    if (store.has(item)) {
      // If found, push the indices of the two numbers to the result array
      result.push(store.get(item), index);
    } else {
      // Otherwise, calculate the difference needed to achieve the target
      let diff = target - item;
      // Store the difference and its index in the Map
      store.set(diff, index);
    }
  });
  return result;
};
