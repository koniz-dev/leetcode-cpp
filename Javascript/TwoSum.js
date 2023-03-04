/**
 * Solution 1
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

/**
 * Solution 2
 * @param {number[]} nums
 * @param {number} target
 * @return {number[]}
 */
var twoSum = function(nums, target) {
    let store = new Map();
    let result = [];

    nums.forEach((item, index) => {
        if (store.has(item)) {
            result.push(store.get(item), index);
        } else {
            let diff= target -item;
            store.set(diff, index);
        }
    })
    return result;
};