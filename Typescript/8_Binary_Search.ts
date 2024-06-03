/**
 * @param nums - The sorted array of integers
 * @param target - The target value to search for
 * @returns The index of the target value in the array if found, otherwise -1
 */
function search(nums: number[], target: number): number {
    // Initialize left and right pointers
    let lpos: number = 0;
    let rpos: number = nums.length - 1;

    // Perform binary search
    while (lpos <= rpos) {
        // Calculate middle index
        let mid: number = Math.floor((lpos + rpos) / 2);

        // Check if target is found
        if (nums[mid] === target)
            return mid;

        // Adjust left and right pointers based on target and middle value
        // Ternary operator is used for concise code
        (nums[mid] < target) ? (lpos = mid + 1) : (rpos = mid - 1);
    }

    // If target is not found, return -1
    return -1;
}
