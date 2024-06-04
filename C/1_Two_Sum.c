/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    *returnSize = 2; // Setting the size of the returned array to 2

    // Allocating memory for the returned array
    int *resultArray = malloc(2 * sizeof(int));

    // Nested loop to find two numbers that sum up to the target
    for (int i = 0; i < numsSize; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            // Checking if the sum of the current pair equals the target
            if (nums[i] + nums[j] == target)
            {
                resultArray[0] = i; // Storing the index of the first number
                resultArray[1] = j; // Storing the index of the second number
                return resultArray; // Returning the array containing the indices
            }
        }
    }

    return -1; // Returning -1 if no such pair is found
}
