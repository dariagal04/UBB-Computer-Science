;11.  Sa se scrie o functie care sterge toate aparitiile unui atom de la toate nivelurile unei liste.

(defun sterge (l e)
	(cond
		((equal l e) nil)
		((listp l) (list (mapcan #'(lambda (lst) (sterge lst e)) l)))
		(t (list l))))

(print (sterge '(1 (2 3 (4 5 1)) (6 1 (7 8 1))) 1))





;sterge(l1..ln,e) = 
;1. [], daca l = e
;2. [], daca l = []
;3. sterge(l1,e) (+) sterge(l2,e) (+) ... (+) sterge(ln,e), daca l lista
;4. [l], daca l!=e si l nu e lista
