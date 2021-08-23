#pragma once
#include <vector>
#include <algorithm>
#include "Menu.h"
#include "DeleteUserMenu.h"
#include "AddGuestGamesMenu.h"
#include "GameMenu.h"
#include "User.h"
#include "Utils.h"

class ProfileMenu : public Menu
{
public:
	ProfileMenu(const std::string& title, Application* app);
	void OutputOptions() final;
	bool HandleChoice(const char choice) final;
private:
};

