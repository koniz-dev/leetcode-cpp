/**
 * Example:
 * var li = ListNode(5)
 * var v = li.`val`
 * Definition for singly-linked list.
 * class ListNode(var `val`: Int) {
 *     var next: ListNode? = null
 * }
 */
class Solution {
    fun mergeTwoLists(list1: ListNode?, list2: ListNode?): ListNode? {
        if (list1 == null) return list2
        if (list2 == null) return list1
        var mergedHead: ListNode?
        if (list1.`val` < list2.`val`) {
            mergedHead = list1
            list1 = list1.next
        } else {
            mergedHead = list2
            list2 = list2.next
        }
        var current = mergedHead
        while (list1 != null && list2 != null) {
            if (list1.`val` < list2.`val`) {
                current!!.next = list1
                list1 = list1.next
            } else {
                current!!.next = list2
                list2 = list2.next
            }
            current = current!!.next
        }
        current!!.next = list1 ?: list2
        return mergedHead
    }
}