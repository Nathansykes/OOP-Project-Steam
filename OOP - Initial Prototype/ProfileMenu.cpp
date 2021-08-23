#include "ProfileMenu.h"


ProfileMenu::ProfileMenu(const std::string& title, Application* app) : Menu(title, app)
{
	Paint(); // required in constructor
}


void ProfileMenu::OutputOptions()
{

	if (app->getCurrentUser() != nullptr)
	{

		Guest* g = nullptr;
		Player* p = nullptr;

		if (app->getCurrentUser()->isGuest())
		{
			g = dynamic_cast<Guest*>(app->getCurrentUser());
		}
		else
		{
			p = dynamic_cast<Player*>(app->getCurrentUser());
		}
	
		if (p != nullptr)
		{

			if (p->isAdmin())
			{

				std::stringstream ss;
				ss << "Current Profile : " << app->getCurrentUser()->getUsername() << " (Admin)";
				Line(ss.str());
			}
			else
			{
				std::stringstream ss;
				ss << "Current Profile : " << app->getCurrentUser()->getUsername();
				Line(ss.str());
			}

			std::stringstream ss;
			ss << "My Credits : " << p->getCredits();
			Line(ss.str());
			Line();
			Option('G', "Sort games alphabetically");
			Option('D', "Sort games by date purchased \n");

			Line(" Owned Games : ");
			Line();

			bool NoGames = true;
			for (int i = 0; i < p->getLibrary().size(); i++)
			{
				NoGames = false;
				Option(i + 1, p->getLibrary()[i]->getName(), Utils::displayTime(p->getLibrary()[i]->getPlayTime()), p->getLibrary()[i]->getPurchaseDate().displayDateNumFormat());
			}
			if (NoGames)
			{
				Line(" None");
				Line();
			}
			Line();
			Option('P', "Buy Credits");
			if (p->isAdmin())
			{
				Option('C', "Create new profile");
				Option('F', "Delete a profile");
				Option('A', "Add guest games");
			}
		}

		else if (app->getCurrentUser()->isGuest() && g != nullptr)
		{
			Option('G', "Sort games alphabetically");
			Option('D', "Sort games by date purchased \n");

			Line(" Owned Games : ");
			Line();
			
			bool NoGames = true;
			for (int i = 0; i < g->getLibrary().size(); i++)
			{
				NoGames = false;
				// adding 1 so the display is nicer for the user

				Option(i + 1, g->getLibrary()[i]->getName(), Utils::displayTime(g->getLibrary()[i]->getPlayTime()), g->getLibrary()[i]->getPurchaseDate().displayDateNumFormat());

			}
			if (NoGames)
			{
				Line(" None");
				Line();
			}
			Line();
		}

	}
}

bool sortDate(const LibraryItem* l1, const LibraryItem* l2)
{
	return l1->getPurchaseDate() < l2->getPurchaseDate();
}

bool compareFunction(const LibraryItem* l1, const LibraryItem* l2)
{
	return l1->getName() < l2->getName();
}

bool ProfileMenu::HandleChoice(const char choice)
{
	Guest* g = nullptr;
	Player* p = nullptr;

	if (app->getCurrentUser()->isGuest())
	{
		g = dynamic_cast<Guest*>(app->getCurrentUser());
	}
	else
	{
		p = dynamic_cast<Player*>(app->getCurrentUser());
	}

	if (p != nullptr)
	{
		std::string newName;
		std::string newPassword;
		int addCredits = 0;
		std::stringstream ss;

		switch (choice)
		{
		case 'G':
			std::sort(p->getLibrary().begin(), p->getLibrary().end(), compareFunction);
			break;
		case 'D':
			std::sort(p->getLibrary().begin(), p->getLibrary().end(), sortDate);
			break;
		case 'P':
			Line();
			addCredits = stoi(Question("How many credits would you like to buy?"));
			p->setCredits(addCredits);

			ss << "Thanks for buying " << addCredits << " ,they have successfully added to your account!";
			Line(ss.str());
			Line();
			break;

		case 'C':
			if (p->isAdmin())
			{
				newName = Question("Enter the new profile");
				Line();
				newPassword = Question("Enter a password for the new profile");

				Player* player = new Player(newName, newPassword, Date(), 0);
				app->getCurrentAccount()->getUsers().addAtEnd(player);
			}

			break;
		case 'F':
			if (p->isAdmin())
			{
				DeleteUserMenu deleteUserMenu("Remove User", app);
			}
			break;
		case 'A':
			if (p->isAdmin())
			{
				AddGuestGamesMenu addGuestGamesMenu("Add Games To Guest", app);
			}
		default:

			// since we are using numbers here we shift the char down by '1'
			// this puts '1' as 0, '2' as 1, '3' as 2, '4' as 3, etc.
			// this reverses the + 1 above and lets us do the range check below
			int index = choice - '1';

			int playTime = 0;

			if (index >= 0 && index < p->getLibrary().size())
			{
				//playTime = p->getLibrary()[index]->getPlayTime() + Utils::randomTime();
				//p->getLibrary()[index]->setPlayTime((double)playTime);
				// go to game detail page
				GameMenu("GAME", app, p->getLibrary()[index]->getName());
			}
			break;
		}
	}



	else if (app->getCurrentUser()->isGuest() && g != nullptr)
	{
		std::stringstream ss;

		switch (choice)
		{
		case 'G':
			std::sort(p->getLibrary().begin(), g->getLibrary().end(), compareFunction);
			break;
		case 'D':
			std::sort(p->getLibrary().begin(), g->getLibrary().end(), sortDate);
			break;

		default:

			// since we are using numbers here we shift the char down by '1'
			// this puts '1' as 0, '2' as 1, '3' as 2, '4' as 3, etc.
			// this reverses the + 1 above and lets us do the range check below
			int index = choice - '1';

			int playTime = 0;

			if (index >= 0 && index < g->getLibrary().size())
			{
				//playTime = p->getLibrary()[index]->getPlayTime() + Utils::randomTime();
				//p->library[index]->setPlayTime((double)playTime);
				// go to game detail page, then play game there
				GameMenu("GAME", app, g->getLibrary()[index]->getName());
			}
			break;
		}
	}
	return false;
}
