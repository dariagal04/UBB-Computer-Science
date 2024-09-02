#include <stdio.h>


/*
-mainul apeleaza subprogramul problema8.
-in subprogram se imparte fiecare element din inmultirea n! la p atat timp cat este impartire exacta pentru a calcula de cate ori
apare p in descompunerea tuturor elementelor
-mainul salveaza rezultatul si il afiseaza
*/


int problema8(int n, int p)
{
	int nr = 0, i; // nr este suma puterilor la care apare p in fiecare din descompunerile elementelor inmultirii n!, nr intreg, i intreg
	for (i = 1; i <= n; i++)
	{
		int t = i; // t intreg copie a lui i
		while (t % p == 0) 
		{
			t = t / p; 
			nr += 1;
			//cat timp t se imparte exact la p, creste puterea nr
		}
	}
	return nr;
}

int problema9(int* l, int n)
{
	//printf("%x", l[1]);

	int i, p2 = 0, p5 = 0;
	for (i = 1; i <= n; i++)
	{
		int copie = *(l+i);
		//printf("%d", copie);
		while (copie % 2 == 0 && copie>0)
		{
			//printf("copia e egala cu %d\n", copie);
			copie = copie / 2;
			p2 = p2 + 1;
		}
		// se calculeaza la ce putere se gaseste 2 in toate numerele
		while (copie % 5 == 0 && copie > 0)
		{

			copie = copie / 2;
			p5 = p5 + 1;
		}
		// se calculeaza la ce putere se gaseste 5 in toate numerele
	}
	if (p2 > p5)
		return p5;
	return p2;
	// se returneaza puterea minima dintre p2 si p5 <=> la ce putere apare 10 in produsul final
}

void meniu()
{
	printf("0. exit\n1. Tipareste exponentul la care numarul prim p apare in descompunerea in factori primi a numarului N = 1 * 2*...*n(n natural nenul dat).\n2.Citeste un sir de numere naturale nenule terminat cu 0 si determina numarul cifrelor 0 in care se termina numarul produs al numerelor citite.\n");
}

int main()
{
	int n, p, prob, prob2, optiune = 1, x, l[100], i;


	while (1)
	{
		meniu(); 
		printf("optiune = ");
		scanf_s("%d", &optiune);
		if (optiune == 0)
			return 0;
		else
		{
			if (optiune == 1)
			{
				printf("n = ");
				scanf_s("%d", &n);
				printf("p = ");
				scanf_s("%d", &p);
				// se citesc optiune intreg, n intreg, p intreg, se defineste prob intreg
				prob = problema8(n, p);
				printf("%d ! contine %d de %d in descompunere\n", n, prob, p);
			}
			if (optiune == 2)
			{
				i = 0;
				int x = 1;
				while(x)
				{
					scanf_s("%d", &x);
					//printf("s-a citit nr");
					i = i + 1;
					l[i] = x;
					//printf("%d ", l[i]);
				}
				prob2 = problema9(l, i);
				printf("sunt %d de 0 la finalul produsului\n", prob2);
			}
		}

	}
	return 0;
    
}
//p8:




/*
pre conditii: n, p intregi
post conditii: nr(rezultatul) intreg si n! / (p^(nr+j)) nu e intreg , unde j>0
*/