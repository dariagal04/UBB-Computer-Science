#pragma once

#include "domain.h"
#include "MyList.h"
#include "service.h"

/// <summary>
/// functie care adauga participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void add_Part(MyList* le);

//void run();

void displayList(MyList* le);

/// <summary>
/// functie care sterge participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void del_Part(MyList* le);


/// <summary>
/// functie care schimba un participant
/// </summary>
/// <param name="surname"></param>
/// <param name="name"></param>
/// <param name="scor"></param>
/// <returns></returns>
void update_Part(MyList* le);