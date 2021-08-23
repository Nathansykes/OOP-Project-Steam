#include "LoginUserMenu.h"

LoginUserMenu::LoginUserMenu(const std::string& title, Application* app) : Menu(title, app)
{
	Paint();
}

void LoginUserMenu::OutputOptions()
{
	if (app->getCurrentUser() != nullptr) 
	{
		std::stringstream ss;																			// String stream 
		ss << "You are logged in as : " << app->getCurrentUser()->getUsername();						// String stream is made up
		Line(ss.str());																					// Line = string stream
		Line();																							// Line to add a space
	}

	for (int i = 0; i < app->getCurrentAccount()->getUsers().size(); i++)									// for each user that is part of the current account.
	{
		Option(i+1, app->getCurrentAccount()->getUsers()[i]->item->getUsername());							// display an index alongside the users name.
	}
}

bool LoginUserMenu::HandleChoice(const char choice)
{
	std::string password = "";
	int choiceInt = choice - '0';
	choiceInt -= 1;

	for (int i = 0; i < app->getCurrentAccount()->getUsers().size(); i++)									// for each user that is part of the current account.
	{
		if (choiceInt == i)
		{
			if (app->getCurrentAccount()->getUsers()[i]->item->isGuest())									// if the chosen user is guest
			{
				app->LoginGuest();			// no password needed
				break;
			}
			else
			{
				Line();
				password = Question("Please input password");											// else, a password is needed
				app->LoginUser(app->getCurrentAccount()->getUsers()[i]->item->getUsername(), password);
				break;
				// login user is called
			}
		}
	}

	return false;																				
}