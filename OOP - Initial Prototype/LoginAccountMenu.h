#pragma once

#include "Menu.h"
#include "MainMenu.h"
#include "StoreMenu.h"

class LoginAccountMenu : public Menu
{
public:
	LoginAccountMenu(const std::string& title, Application* app);
	void OutputOptions() final;
	bool HandleChoice(const char choice) final;
};

