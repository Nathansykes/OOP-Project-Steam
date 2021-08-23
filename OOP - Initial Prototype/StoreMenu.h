#pragma once

#include "Menu.h"
#include "GameMenu.h"
#include <string>
#include <vector>
#include <algorithm>

class StoreMenu : public Menu
{
public:
	StoreMenu(const std::string& title, Application* app);
	void OutputOptions() final;
	bool HandleChoice(const char choice) final;
private:
	std::string searchText = "";
	std::vector<Game*> games = { };
	int minPrice = 0;
	int maxPrice = 10000;
};
