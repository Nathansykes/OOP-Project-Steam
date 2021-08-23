#pragma once

#include "Menu.h"
#include "StoreMenu.h"
#include <sstream>

class LoginUserMenu : public Menu
{
public:
	LoginUserMenu(const std::string& title, Application* app);
	void OutputOptions() final;
	bool HandleChoice(const char choice) final;
};