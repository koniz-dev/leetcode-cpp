class Solution {
    /**
     * @param Integer[] $nums
     * @param Integer $target
     * @return Integer[]
     */
    function twoSum($nums, $target) {
        $numIndices = array(); // Create an empty associative array to store the indices of numbers
        
        // Loop through the array of numbers
        foreach ($nums as $index => $num) {
            // Calculate the complement needed to achieve the target
            $complement = $target - $num;
            
            // If the complement exists in the array of numbers, return the indices of the current number and its complement
            if (isset($numIndices[$complement])) {
                return array($numIndices[$complement], $index);
            }
            
            // Store the current number's index for future reference
            $numIndices[$num] = $index;
        }
        
        // If no solution is found, return an empty array
        return array();
    }
}
