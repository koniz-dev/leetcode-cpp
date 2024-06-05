# @param {Integer[]} nums
# @param {Integer} target
# @return {Integer[]}
def two_sum(nums, target)
    # Create a hash to store the indices of numbers
    num_indices = {}

    # Iterate through the array of numbers
    nums.each_with_index do |num, index|
      # Calculate the complement needed to achieve the target
      complement = target - num

      # If the complement exists in the hash, return the indices of the current number and its complement
      if num_indices.key?(complement)
        return [num_indices[complement], index]
      end

      # Store the current number's index for future reference
      num_indices[num] = index
    end

    # If no solution is found, return an empty array
    []
end