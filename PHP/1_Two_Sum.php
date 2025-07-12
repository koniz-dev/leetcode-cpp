class Solution {
    /**
     * @param Integer[] $nums
     * @param Integer $target
     * @return Integer[]
     */
    function twoSum($nums, $target) {
        $numIndices = array();
        foreach ($nums as $index => $num) {
            $complement = $target - $num;
            if (isset($numIndices[$complement])) {
                return array($numIndices[$complement], $index);
            }
            $numIndices[$num] = $index;
        }
        return array();
    }
}
