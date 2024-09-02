#pragma once
#include "service.h"
#include "VectorDinamic.h"
class UI
{
	LocatarService& srv;
public:
	UI(LocatarService& srv) : srv{ srv } {}
	UI(const UI& other) = delete;
	void startUI();
};
