;6. Sa se construiasca lista nodurilor unui arbore de tipul (1) parcurs in
;inordine.



; parcurg(l1..ln, nv, nm, s1..sm) = 1. (s1..sm (+) l1..ln), daca nv = 1 + nm
;	                                  2. nil, daca l e vida
;	                                  3. parcurg(l3..ln, nv+1, nm+l2, s1..sm (+) l1 (+) l2), altfel
(defun parcurg(l nv nm s)
 (cond
    ((= nv (+ 1 nm)) (list s l))
    ((null l) nil)
    (t (parcurg (cddr l) (+ 1 nv) (+ (cadr l) nm) (append s (list (car l) (cadr l)))))
 )
)

(print(parcurg '(A 2 B 2 C 0 D 0 E 0) 0 0 nil))



; stang(l1..ln) = parte stanga , unde (parte stanga+ parte dreapta) = parcurg(l3..ln, 0, 0, ())
;
(defun stang(arb)
     (car (parcurg (cddr arb) 0 0 nil))
)

(print (stang '(A 2 B 2 C 0 D 0 E 0)))



; drept(l1..ln) = parte dreapta , unde (parte stanga+ parte dreapta) = parcurg(l3..ln, 0, 0, ())
;
(defun drept(arb)
    (cadr (parcurg (cddr arb) 0 0 nil))
)
(print (drept '(A 2 B 2 C 0 D 0 E 0)))



; inordine(l1..ln) = 1. (), daca l e vida
;	                   2. inordine(stang(l1..ln)) (+) l1 (+) inordine(drept(l1..ln)), altfel
(defun inordine(l)
 (cond
    ((null l) nil)
    (t (append (inordine (stang l)) (list (car l)) (inordine (drept l))))
 )
)

(print (inordine '(A 2 B 2 C 0 D 0 E 0)))






