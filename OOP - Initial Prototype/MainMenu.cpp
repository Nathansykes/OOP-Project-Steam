#include "MainMenu.h"



MainMenu::MainMenu(const std::string& title, Application* app) : Menu(title, app)
{
	Paint(); // required in constructor
}

void MainMenu::OutputOptions()
{
	Option('S', "Browse Store");

	if (app->IsUserLoggedIn())
	{
		Option('P', "View Profile");
		Option('L', "Logout User");
	}
	else
	{
		Option('L', "Login User");
	}

	Option('E', "Logout Account");
}

bool MainMenu::HandleChoice(const char choice)
{
	switch (choice)
	{
		case 'S':
		{
			StoreMenu("STORE", app);
		} 
		break;

		case 'L':
		{
			if (app->IsUserLoggedIn())
			{
				app->LogoutUser();
			}
			else
			{
				LoginUserMenu("LOGIN", app);
			}
		} 
		break;

		case 'P':
		{
			if (app->IsUserLoggedIn())
			{
				ProfileMenu("PROFILE", app);
			}
		} 
		break;
		case 'E':
		{
			if (app->IsAccountLoggedIn())
			{
				Line();
				std::string answer = Question("Are you sure? (y/n)");
				if (answer == "y" || answer == "Y")
				{
					app->LogoutAccount();
					return true;
				}
			}
		}
		break;
	}

	return false;
}