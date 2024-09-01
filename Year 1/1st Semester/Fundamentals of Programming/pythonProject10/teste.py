import domeniu
import infrastructura
import business

def test_adaugare_nr_complex():
    assert infrastructura.adauga_nr_complex([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)], 9, 10) == [domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6), domeniu.creeaza_nrcomplex(7,8), domeniu.creeaza_nrcomplex(9,10)]


def test_adauga_pe_poz():
    assert infrastructura.adauga_pe_poz([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)], 9, 10, 2) == [domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4),domeniu.creeaza_nrcomplex(9,10), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)]

def test_sterge_de_pe_poz():
    assert infrastructura.sterge_depe_poz([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)], 3) == [domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6)]

def test_sterge_interval():
    assert business.sterg_interval([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)], 1, 2) == [domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)]

def test_inlocuire_nr_complex():
    assert infrastructura.inlocuire_nr_complex([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(3,4),domeniu.creeaza_nrcomplex(7,8)], 3, 4, 9, 10) == [domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(9,10), domeniu.creeaza_nrcomplex(9,10),domeniu.creeaza_nrcomplex(7,8)]

def test_tipareste_pi():
    assert infrastructura.tipareste_pi([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)], 1, 3, []) == [4, 6]

def test_modul_numar_maimic():
    assert business.modul_numar_maimic([domeniu.creeaza_nrcomplex(1,0), domeniu.creeaza_nrcomplex(10,0), domeniu.creeaza_nrcomplex(5,0),domeniu.creeaza_nrcomplex(11,0)], []) == [domeniu.creeaza_nrcomplex(1,0), domeniu.creeaza_nrcomplex(5,0)]

def test_modul_numar_egal():
    assert business.modul_numar_egal([domeniu.creeaza_nrcomplex(1,0), domeniu.creeaza_nrcomplex(10,0), domeniu.creeaza_nrcomplex(5,0),domeniu.creeaza_nrcomplex(11,0)], []) == [domeniu.creeaza_nrcomplex(10,0)]

def test_suma_subsecventa():
    assert business.suma_subsecventa([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)], 1, 3) == domeniu.creeaza_nrcomplex(8,10)


def test_prod_subsecventa():
    assert business.prod_subsecventa([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)], 1, 3) == domeniu.creeaza_nrcomplex(15,24)


def test_sorteaza_descrescator():
    assert infrastructura.sorteaza_descrescator([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(7,8)]) == [domeniu.creeaza_nrcomplex(7,8), domeniu.creeaza_nrcomplex(5,6), domeniu.creeaza_nrcomplex(3,4),domeniu.creeaza_nrcomplex(1,2)]

def test_filtrare_prime():
    assert business.filtrare_prime([domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(3,4), domeniu.creeaza_nrcomplex(5,6),domeniu.creeaza_nrcomplex(8,8)]) == [domeniu.creeaza_nrcomplex(1,2), domeniu.creeaza_nrcomplex(8,8)]

def test_filtrare_modul():
    assert business.filtrare_modul([domeniu.creeaza_nrcomplex(1,0), domeniu.creeaza_nrcomplex(10,0), domeniu.creeaza_nrcomplex(5,0),domeniu.creeaza_nrcomplex(11,0)], '=', 10) == [domeniu.creeaza_nrcomplex(1,0), domeniu.creeaza_nrcomplex(5,0),domeniu.creeaza_nrcomplex(11,0)]
def teste():
    test_prod_subsecventa()
    test_filtrare_modul()
    test_filtrare_prime()
    test_adauga_pe_poz()
    test_adaugare_nr_complex()
    test_inlocuire_nr_complex()
    test_modul_numar_egal()
    test_modul_numar_maimic()
    test_sorteaza_descrescator()
    test_sterge_de_pe_poz()
    test_sterge_interval()
    test_suma_subsecventa()
    test_tipareste_pi()
