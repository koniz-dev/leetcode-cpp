/**
 * @param nums - The sorted array of integers
 * @param target - The target value to search for
 * @returns The index of the target value in the array if found, otherwise -1
 */
export function search(nums: number[], target: number): number {
    let lpos: number = 0;
    let rpos: number = nums.length - 1;
    while (lpos <= rpos) {
        let mid: number = Math.floor((lpos + rpos) / 2);
        if (nums[mid] === target)
            return mid;
        (nums[mid] < target) ? (lpos = mid + 1) : (rpos = mid - 1);
    }
    return -1;
}
