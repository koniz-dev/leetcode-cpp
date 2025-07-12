/**
 * Definition for singly-linked list.
 * function ListNode(val, next) {
 *     this.val = (val===undefined ? 0 : val)
 *     this.next = (next===undefined ? null : next)
 * }
 */
/**
 * @param {ListNode} list1
 * @param {ListNode} list2
 * @return {ListNode}
 */
var mergeTwoLists = function (list1, list2) {
    if (!list1) return list2;
    if (!list2) return list1;
    let mergedHead = null;
    if (list1.val < list2.val) {
        mergedHead = list1;
        list1 = list1.next;
    } else {
        mergedHead = list2;
        list2 = list2.next;
    }
    let current = mergedHead;
    while (list1 && list2) {
        if (list1.val < list2.val) {
            current.next = list1;
            list1 = list1.next;
        } else {
            current.next = list2;
            list2 = list2.next;
        }
        current = current.next;
    }
    current.next = list1 ? list1 : list2;
    return mergedHead;
}
