#include "DeleteUserMenu.h"

DeleteUserMenu::DeleteUserMenu(const std::string& title, Application* app) : Menu(title, app)
{
	Paint();
}

void DeleteUserMenu::OutputOptions()
{

	Player* p = dynamic_cast<Player*>(app->getCurrentUser());

	if (p->isAdmin())
	{
		for (int i = 0; i < app->getCurrentAccount()->getUsers().size(); i++)
		{
			Option(i + 1, app->getCurrentAccount()->getUsers()[i]->item->getUsername());
		}
	}

}

bool DeleteUserMenu::HandleChoice(const char choice)
{
	int choiceInt = choice - '0';
	choiceInt -= 1;

	for (int i = 0; i < app->getCurrentAccount()->getUsers().size(); i++)
	{
		if (choiceInt == i)
		{
			std::ostringstream question;
			Line();
			question << "Are you sure you want to remove " << app->getCurrentAccount()->getUsers()[i]->item->getUsername() << "? (y/n)";
			Line();

			std::string answer = Question(question.str());

			if (answer == "y" || answer == "Y") 
			{
				app->getCurrentAccount()->getUsers().deleteOne(app->getCurrentAccount()->getUsers()[i]->item);
			}
		}
	}

	return false;
}
