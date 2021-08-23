#include "LoginAccountMenu.h"


LoginAccountMenu::LoginAccountMenu(const std::string& title, Application* app) : Menu(title, app) 
{
	Paint();
}

void LoginAccountMenu::OutputOptions() 
{
	Option('L',"Login");
}

bool LoginAccountMenu::HandleChoice(const char choice) 
{
	std::string email = "";
	std::string password = "";
	bool tryAgain = true;

	switch(choice) 
	{
		case 'L':
			while(tryAgain)
			{
				this->Line();
				email =	this->Question("Please input email");
				this->Line();
				password = this->Question("Please input password");
				this->Line();

				app->LoginAccount(email, password);

				if (app->IsAccountLoggedIn())
				{
					tryAgain = false;
					std::string title;
					title = "Main Menu";
					MainMenu mainMenu(title, app);
				}
				else
				{		
					this->BlockingMessage("Incorrect Password. Press enter to try again : ");
					this->Paint();
			
					tryAgain = true;
				}
			}
			break;
		
		default:
			break;
	}

	return false;
}