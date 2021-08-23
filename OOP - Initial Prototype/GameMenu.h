#pragma once
#include <string>
#include <vector>
#include "Date.h"

#include "menu.h"
class GameMenu : public Menu
{
	public:
		GameMenu(const std::string& title, Application* app, const std::string& game);
		void OutputOptions() final;
		bool HandleChoice(const char choice) final;
	private:
		std::string game;
		bool hasGame = false;
		Game* gamePtr;
};

