;; 12.a)Definiti o functie care intoarce produsul scalar a doi vectori.
;; b)Sa  se  construiasca  ofunctie  care  intoarce  maximul  atomilor  numerici dintr-o lista, de la orice nivel.
;; c)Sa se scrie o functie care intoarce lista permutarilor unei liste date.
;; d)Sa  se  scrie  o  functie  care  intoarce  T  daca  o  lista  are  numar  par  de elemente  pe  primul  nivel  si  NIL  in  caz  contrar,  fara  sa  se  numere elementele listei.

;; a)

;;produs_scalar(a1..an b1..bm) = 1. 0, n=0
;;                               2. 0, m=0
;;                               3. a1 * b1 + produs_scalar(a2..an, b2..bm), altfel
(defun produs_scalar (a b)
  (cond 
    ((null a) 0)
    ((null b) 0)
    (t (+ (* (car a)(car b)) (produs_scalar (cdr a)(cdr b)) ))
  )
)


(print (produs_scalar '(1 2 3) '(4 5 6)))


;;b)

;; maxim_atomi_numerici (l1..ln) = 1. 0, n=0
;;                                 2. l1, daca l1 e numar si l1 > maxim_atomi_numerici (l2..ln)
;;                                 3. maxim_atomi_numerici (l1), daca maxim_atomi_numerici (l1) > maxim_atomi_numerici (l2..ln)
;;                                 4. maxim_atomi_numerici (l2..ln), altfel
(defun maxim_atomi_numerici (l)
    (cond
      ((null l) 0)
      ((numberp (car l)) (max (car l) (maxim_atomi_numerici (cdr l))))
      ((> (maxim_atomi_numerici (car l)) (maxim_atomi_numerici (cdr l))) (maxim_atomi_numerici (car l)))
      (t (maxim_atomi_numerici (cdr l)))
    )
)


(print (maxim_atomi_numerici '(1 (2 9) (4 (5 6)) 7)))




;;c)

;; insereaza_pozitii (lP e l1..ln) = 1. lPrepend (+) e), daca n=0
;;                                   2. ((lPrepend (+) e (+) l) (+) insereaza_pozitii((lPrepend (+) l1) e l2..ln)), altfel
(defun insereaza_pozitii (lPrepend e l)
  (cond
    ((null l) (list (append lPrepend (list e))))
    (t (append (list (append lPrepend (cons e l))) (insereaza_pozitii (append lPrepend (list (car l))) e (cdr l))))
  )
)

(print (insereaza_pozitii '() 1 '(2 3 4)))



;; insereaza_subliste (e l1..ln) = 1. insereaza_pozitii( nil e l1 ), n=1
;;                                 2. insereaza_pozitii( nil e l1 ) (+) insereaza_subliste(e l2..ln), altfel
(defun insereaza_subliste (e l)
  (cond
    ((null (cdr l)) (insereaza_pozitii '() e (car l)))
    (t (append (insereaza_pozitii '() e (car l)) (insereaza_subliste e (cdr l))))
  )
)

(print (insereaza_subliste 1 '((2 3) (4 5))))


;; permutari (l1..ln) = 1. NIL , n=0
;;                      2. (list l1), n=1
;;                      3. insereaza_subliste( l1 (permutari (l2..ln))), altfel
(defun permutari (l)
  (cond
    ((null l) nil)
    ((null (cdr l)) (list l))
    (t (insereaza_subliste (car l) (permutari (cdr l))))
  )
)


(print (permutari '(1 2 3)))






;;d)

;; verificare_nr_elem_par (l1..ln) = 1. T, n=0
;;                                   2. NIL, daca lista are un singur element
;;                                   3. verificare_nr_elem_par (l3..ln), altfel
(defun verificare_nr_elem_par (l)
  (cond ((null l) T)
        ((null (cdr l)) NIL)
        (t (verificare_nr_elem_par (cddr l)))
  )
)


(print (verificare_nr_elem_par '(1 2 3 4 5 (1 2 3))))


