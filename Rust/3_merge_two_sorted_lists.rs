// Definition for singly-linked list.
// #[derive(PartialEq, Eq, Clone, Debug)]
// pub struct ListNode {
//   pub val: i32,
//   pub next: Option<Box<ListNode>>
// }
// 
// impl ListNode {
//   #[inline]
//   fn new(val: i32) -> Self {
//     ListNode {
//       next: None,
//       val
//     }
//   }
// }
impl Solution {
    pub fn merge_two_lists(list1: Option<Box<ListNode>>, list2: Option<Box<ListNode>>) -> Option<Box<ListNode>> {
        match (list1, list2) {
            (None, _) => list2,
            (_, None) => list1,
            (Some(mut l1), Some(mut l2)) => {
                if l1.val < l2.val {
                    let next = l1.next.take();
                    l1.next = merge_two_lists(next, Some(l2));
                    Some(l1)
                } else {
                    let next = l2.next.take();
                    l2.next = merge_two_lists(Some(l1), next);
                    Some(l2)
                }
            }
        }
    }
}