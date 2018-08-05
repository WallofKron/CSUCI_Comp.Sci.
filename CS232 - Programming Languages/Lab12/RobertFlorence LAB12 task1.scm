(begin (display "Arbitrary function: "))
(define funcn((read)))
(begin (display "List: "))
(define lst ((read)))

(define perform(lambda(funcn list)
			(if (null? lst) 
				0
				(apply (funcn (car lst) (perform (cdr list)))))))