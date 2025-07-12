/**
 * Definition for a singly-linked list.
 * class ListNode {
 *     public $val = 0;
 *     public $next = null;
 *     function __construct($val = 0, $next = null) {
 *         $this->val = $val;
 *         $this->next = $next;
 *     }
 * }
 */
class Solution {

    /**
     * @param ListNode $list1
     * @param ListNode $list2
     * @return ListNode
     */
    function mergeTwoLists($list1, $list2) {
        if ($list1 === null) return $list2;
        if ($list2 === null) return $list1;
        $mergedHead = null;
        if ($list1->val < $list2->val) {
            $mergedHead = $list1;
            $list1 = $list1->next;
        } else {
            $mergedHead = $list2;
            $list2 = $list2->next;
        }
        $current = $mergedHead;
        while ($list1 !== null && $list2 !== null) {
            if ($list1->val < $list2->val) {
                $current->next = $list1;
                $list1 = $list1->next;
            } else {
                $current->next = $list2;
                $list2 = $list2->next;
            }
            $current = $current->next;
        }
        $current->next = $list1 !== null ? $list1 : $list2;
        return $mergedHead;
    }
}