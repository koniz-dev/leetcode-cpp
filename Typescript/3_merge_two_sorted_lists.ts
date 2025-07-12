class ListNode {
    val: number;
    next: ListNode | null;
    constructor(val?: number, next?: ListNode | null) {
        this.val = val === undefined ? 0 : val;
        this.next = next === undefined ? null : next;
    }
}

export function mergeTwoLists(list1: ListNode | null, list2: ListNode | null): ListNode | null {
    if (!list1) return list2;
    if (!list2) return list1;

    let mergedHead: ListNode | null = null;
    if (list1.val < list2.val) {
        mergedHead = list1;
        list1 = list1.next;
    } else {
        mergedHead = list2;
        list2 = list2.next;
    }

    let current: ListNode | null = mergedHead;

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