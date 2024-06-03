/**
 * Solution 1: Faster
 * @param nums - The array of integers
 * @param target - The target sum
 * @returns The indices of the two numbers that add up to the target
 */
function twoSum(nums: number[], target: number): number[] {
    // Create an object to store the number and its index
    const result: { [key: number]: number } = {};

    // Iterate through the array
    for (let i = 0; i < nums.length; i++) {
        // Calculate the difference needed to achieve the target
        const temp = target - nums[i];

        // Check if the difference exists in the object
        if (result.hasOwnProperty(temp))
            // If found, return the indices of the two numbers
            return [result[temp], i];

        // Otherwise, store the current number and its index in the object
        result[nums[i]] = i;
    }

    // If no solution is found, return an empty array
    return [];
}

/**
 * Solution 2: Slower
 * @param nums - The array of integers
 * @param target - The target sum
 * @returns The indices of the two numbers that add up to the target
 */
function twoSum_v2(nums: number[], target: number): number[] {
    // Create a Map to store the number and its index
    const store = new Map<number, number>();
    const result: number[] = [];

    // Iterate through the array
    nums.forEach((item, index) => {
        // Check if the complement exists in the Map
        if (store.has(item)) {
            // If found, push the indices of the two numbers to the result array
            result.push(store.get(item)!, index);
        } else {
            // Otherwise, calculate the difference needed to achieve the target
            const diff = target - item;
            // Store the difference and its index in the Map
            store.set(diff, index);
        }
    });

    // If no solution is found, return an empty array
    return result;
}
