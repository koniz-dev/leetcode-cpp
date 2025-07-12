/**
 * @param {number[]} nums - The sorted array of integers
 * @param {number} target - The target value to search for
 * @return {number} - The index of the target value in the array if found, otherwise -1
 */
var search = function (nums, target) {
  let lpos = 0, rpos = nums.length - 1;
  while (lpos <= rpos) {
    let mid = Math.floor((lpos + rpos) / 2);
    if (nums[mid] === target) return mid;
    nums[mid] < target ? (lpos = mid + 1) : (rpos = mid - 1);
  }
  return -1;
};
