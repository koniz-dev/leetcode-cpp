# @param {Integer[]} nums
# @param {Integer} target
# @return {Integer[]}
def two_sum(nums, target)
    num_indices = {}
    nums.each_with_index do |num, index|
      complement = target - num
      if num_indices.key?(complement)
        return [num_indices[complement], index]
      end
      num_indices[num] = index
    end
    []
end