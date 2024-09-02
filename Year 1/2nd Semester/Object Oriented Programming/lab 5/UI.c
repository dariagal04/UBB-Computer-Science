//#pragma warning(disable : 4996)

#include "UI.h"

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
* Read offer from standard input and add offer to the store
*/
void add_offer(Service* l)
{
	printf("Type: ");
	char type[15];
	scanf_s("%s", type, 15);
	printf("Surface: ");
	double surface;
	int rez1 = scanf("%lf", &surface);
	if (rez1 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}
	printf("Address: ");
	char address[31];
	int rez3 = scanf(" %[^\n]", address);
	if (rez3 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}
	printf("Price: ");
	double price;
	int rez2 = scanf("%lf", &price);
	if (rez2 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}

	int error = addOffer(l, type, surface, address, price);
	if (error != 0)
		printf("Invalid offer!\n\n");
	else
		printf("Offer added!\n\n");
}


/*
* Delete an offer
*/
void delete_offer(Service* l)
{
	printf("Type: ");
	char type[15];
	scanf_s("%s", type, 15);
	printf("Surface: ");
	double surface;
	int rez1 = scanf("%lf", &surface);
	if (rez1 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}

	printf("Address: ");
	char address[31];
	int rez3 = scanf(" %[^\n]", address);
	if (rez3 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}
	printf("Price: ");
	double price;
	int rez2 = scanf("%lf", &price);
	if (rez2 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}

	int invalid = 0;
	int ok = findOffer(l, type, surface, address, price, &invalid);

	if (invalid == 1)
		printf("Invalid offer!\n\n");
	else
	{
		if (ok == -1)
			printf("The offer does not exist!\n\n");
		else
		{
			deleteOffer(l, ok);
			printf("Offer deleted!\n\n");
		}
	}
}

/*
* Update an offer
*/
void update_offer(Service* l)
{
	printf("Type: ");
	char type[15];
	scanf_s("%s", type, 15);
	printf("Surface: ");
	double surface;
	int rez1 = scanf("%lf", &surface);
	if (rez1 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}
	printf("Address: ");
	char address[31];
	int rez3 = scanf(" %[^\n]", address);
	if (rez3 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}
	printf("Price: ");
	double price;
	int rez2 = scanf("%lf", &price);
	if (rez2 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}

	int invalid = 0;
	int ok = findOffer(l, type, surface, address, price, &invalid);

	if (invalid == 1)
		printf("Invalid offer!\n\n");
	else
	{
		if (ok == -1)
			printf("The offer does not exist!\n\n");
		else
		{
			printf("Offer found. Please enter the modifications or -1 if you do not wish to modify the requested argument.\n");
			printf("New type: ");
			scanf_s("%s", type, 15);
			printf("New surface: ");
			int rez4 = scanf("%lf", &surface);
			if (rez4 != 1)
			{
				printf("Eroare la citire!\n\n");
				return;
			}
			printf("New address: ");
			int rez5 = scanf(" %[^\n]", address);
			if (rez5 != 1)
			{
				printf("Eroare la citire!\n\n");
				return;
			}
			printf("New price: ");
			int rez6 = scanf("%lf", &price);
			if (rez6 != 1)
			{
				printf("Eroare la citire!\n\n");
				return;
			}

			int error = updateOffer(l, type, surface, address, price, ok);
			if (error != 0)
				printf("Invalid offer!\n\n");
			else
				printf("Offer updated!\n\n");
		}
	}
}

/*
* Print the offers in a specific order
*/
void print_ordered(MyListAgentie* l)
{
	printf("Insert the sorting type( 1 for ascendent, 0 for descendent): ");
	int sortare;
	int rez1 = scanf("%d", &sortare);
	if (rez1 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}
	MyListAgentie* l_sorted = createEmpty();
	if (sortare == 1)
	{
		l_sorted = sortedAscOffers(l);//, cmpType, cmpPrice);
		printAllOffers(l_sorted);
	}
	else if (sortare == 0)
	{
		l_sorted = sortedDescOffers(l);//, cmpType, cmpPrice);
		printAllOffers(l_sorted);
	}
	else
	{
		printf("Invalid sorting type!\n\n");
	}
	destroy(l_sorted);
}

/*
* Print all offers
*/
void printAllOffers(MyListAgentie* l)
{
	printf("OFFERS:\n");
	for (int i = 0; i < size(l); i++)
	{
		Offer* o = get(l, i);
		printf("Type: %s, Surface: %lf, Addres: %s, Price: %lf\n", o->type, o->surface, o->address, o->price);
	}
}

/*
* Filters offers
*/
void filterOffers(Service* l)
{
	printf("Insert the key which you want to filter by (surface, price or type): ");
	char cheie[15];
	int rez2 = scanf("%s", cheie);
	if (rez2 != 1)
	{
		printf("Eroare la citire!\n\n");
		return;
	}
	cheie[strlen(cheie)] = '\0';
	if (strcmp(cheie, "price") != 0 && strcmp(cheie, "type") != 0 && strcmp(cheie, "surface") != 0)
		printf("Invalid key!\n\n");
	else
	{
		MyListAgentie* filtered = createEmpty(); 
		if (strcmp(cheie, "price") == 0)
		{
			printf("Insert the number: ");
			double nr;
			int rez1 = scanf("%lf", &nr);
			if (rez1 != 1)
			{
				printf("Eroare la citire!\n\n");
				return;
			}
			filtered = filterPrice(l, nr); 
		}
		else if (strcmp(cheie, "type") == 0)
		{
			printf("Insert substring:");
			char filterStr[30];
			scanf_s("%s", filterStr, 30);
			filtered = filterType(l, filterStr);
		}
		else if (strcmp(cheie, "surface") == 0)
		{
			printf("Insert the number: ");
			double nr;
			int rez3 = scanf("%lf", &nr);
			if (rez3 != 1)
			{
				printf("Eroare la citire!\n\n");
				return;
			}
			filtered = filterSurface(l, nr);
		}
		printAllOffers(&filtered);
		destroy(filtered);
	}
}

void ui_undo(Service* o) {
	int undo = service_undo(o);
	if (undo == 0) {
		printf("Nu se mai poate face undo!\n");
	}
	else
		printf("Undo executat cu succes!\n");
}