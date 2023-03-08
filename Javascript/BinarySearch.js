/**
 * @param {number[]} nums
 * @param {number} target
 * @return {number}
 */
var search = function(nums, target) {
    let lpos = 0, rpos = nums.length - 1;

        while (lpos <= rpos) {
            let mid = Math.floor((lpos + rpos) / 2);

            if (nums[mid] === target) return mid;
            (nums[mid] < target) ? (lpos = mid + 1) : (rpos = mid - 1);
        }

        return -1;
};