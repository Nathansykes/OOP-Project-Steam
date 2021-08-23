#pragma once
#include "Menu.h"
#include"Guest.h"
#include "User.h"
#include "Utils.h"
#include <sstream>
#include <vector>
#include <algorithm>

class AddGuestGamesMenu : public Menu
{
public:
	AddGuestGamesMenu(const std::string& title, Application* app);
	void OutputOptions() final;
	bool HandleChoice(const char choice) final;
};

