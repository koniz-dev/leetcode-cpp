/**
 * @param nums - The array of integers
 * @param target - The target sum
 * @returns The indices of the two numbers that add up to the target
 */
export function twoSum(nums: number[], target: number): number[] {
    const result: { [key: number]: number } = {};
    for (let i = 0; i < nums.length; i++) {
        const temp = target - nums[i];
        if (result.hasOwnProperty(temp))
            return [result[temp], i];
        result[nums[i]] = i;
    }
    return [];
}