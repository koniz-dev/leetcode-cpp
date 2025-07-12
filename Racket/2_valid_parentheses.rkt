#lang racket
(define (isValid s)
  (define stack '())
  (define (open? c) (member c '(#\( #\{ #\[)))
  (define (match? o c)
    (or (and (eqv? o #\() (eqv? c #\)))
        (and (eqv? o #\{) (eqv? c #\}))
        (and (eqv? o #\[) (eqv? c #\]))))
  (let loop ([chars (string->list s)] [stack stack])
    (cond
      [(null? chars) (null? stack)]
      [(open? (car chars)) (loop (cdr chars) (cons (car chars) stack))]
      [(member (car chars) '(#\) #\} #\]))
       (and (not (null? stack)) (match? (car stack) (car chars))
            (loop (cdr chars) (cdr stack)))]
      [else (loop (cdr chars) stack)])))
