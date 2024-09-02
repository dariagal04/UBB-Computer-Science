#pragma once

#include "Agentie.h"
#include "MyListAgentie.h"
#include "AgentieService.h"

/*
* Add an offer
*/
void add_offer(Service* l);

/*
* Delete an offer
*/
void delete_offer(Service* l);

/*
* Update an offer
*/
void update_offer(Service* l);

/*
* Print the offers in a specific order
*/
void print_ordered(MyListAgentie* l);

void printAllOffers(MyListAgentie* l);

/*
* Filters offers by type
*/
void filterOffers(Service* l);

void ui_undo(Service* o);