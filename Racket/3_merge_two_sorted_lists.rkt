; Definition for singly-linked list:
#|

; val : integer?
; next : (or/c list-node? #f)
(struct list-node
  (val next) #:mutable #:transparent)

; constructor
(define (make-list-node [val 0])
  (list-node val #f))

|#

(define/contract (merge-two-lists list1 list2)
  (-> (or/c list-node? #f) (or/c list-node? #f) (or/c list-node? #f))
  (cond
    [(not list1) list2]
    [(not list2) list1]
    [else
     (if (< (list-node-val list1) (list-node-val list2))
         (list-node (list-node-val list1)
                    (merge-two-lists (list-node-next list1) list2))
         (list-node (list-node-val list2)
                    (merge-two-lists list1 (list-node-next list2))))]))