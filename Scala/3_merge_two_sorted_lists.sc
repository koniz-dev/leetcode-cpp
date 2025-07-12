/**
 * Definition for singly-linked list.
 * class ListNode(_x: Int = 0, _next: ListNode = null) {
 *   var next: ListNode = _next
 *   var x: Int = _x
 * }
 */
object Solution {
    def mergeTwoLists(list1: ListNode, list2: ListNode): ListNode = {
    if (list1 == null) return list2
    if (list2 == null) return list1
    var mergedHead: ListNode = null
    if (list1.value < list2.value) {
      mergedHead = list1
      list1 = list1.next
    } else {
      mergedHead = list2
      list2 = list2.next
    }
    var current = mergedHead
    while (list1 != null && list2 != null) {
      if (list1.value < list2.value) {
        current.next = list1
        list1 = list1.next
      } else {
        current.next = list2
        list2 = list2.next
      }
      current = current.next
    }
    current.next = if (list1 != null) list1 else list2
    mergedHead
  }
}
