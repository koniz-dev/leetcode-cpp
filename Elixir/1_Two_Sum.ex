defmodule Solution do
  @spec two_sum(nums :: [integer], target :: integer) :: [integer]
  def two_sum(nums, target) do
    two_sum_helper(nums, target, 0, %{}, [])
  end

  defp two_sum_helper([], _, _, _, _), do: []  # Base case: Empty list, no solution found
  defp two_sum_helper([num | rest], target, index, seen, result) do
    complement = target - num
    case Map.get(seen, complement) do
      nil -> 
        new_seen = Map.put(seen, num, index)
        two_sum_helper(rest, target, index + 1, new_seen, result)
      other -> [other, index]
    end
  end
end
