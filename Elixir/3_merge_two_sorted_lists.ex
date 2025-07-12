# Definition for singly-linked list.
#
# defmodule ListNode do
#   @type t :: %__MODULE__{
#           val: integer,
#           next: ListNode.t() | nil
#         }
#   defstruct val: 0, next: nil
# end

defmodule Solution do
  @spec merge_two_lists(list1 :: ListNode.t | nil, list2 :: ListNode.t | nil) :: ListNode.t | nil
  def merge_two_lists(list1, list2) do
    cond do
      is_nil(list1) -> list2
      is_nil(list2) -> list1
      list1.val < list2.val ->
        %ListNode{val: list1.val, next: merge_two_lists(list1.next, list2)}
      true ->
        %ListNode{val: list2.val, next: merge_two_lists(list1, list2.next)}
    end