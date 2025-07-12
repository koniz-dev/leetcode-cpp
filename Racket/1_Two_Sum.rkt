(define/contract (two-sum nums target)
  ;; Contract: two-sum takes a list of exact integers and an exact integer as input
  ;;           and returns a list of exact integers representing the indices of two numbers
  ;;           in the input list that add up to the target.
  (-> (listof exact-integer?) exact-integer? (listof exact-integer?))
  
  ;; Function body
  (define (helper nums target index seen)
    (cond
      [(null? nums) '()]
      
      [(hash-ref seen (- target (car nums)) #f)
       ;; If yes, return the current index and the index of the complement
       (list (hash-ref seen (- target (car nums))) index)]
      
      [else (begin
              (hash-set! seen (car nums) index)
              (helper (cdr nums) target (add1 index) seen))]))

  (helper nums target 0 (make-hash)))