#include "AddGuestGamesMenu.h"

AddGuestGamesMenu::AddGuestGamesMenu(const std::string& title, Application* app) : Menu(title, app)
{
	Paint();																																							// required in constructor
}


void AddGuestGamesMenu::OutputOptions()
{
	if (app->getCurrentUser() != nullptr)																																// if the current user is not a null pointer
	{
		Player* p = dynamic_cast<Player*>(app->getCurrentUser());																										// downcast User pointer to be a Player pointer

		if (p->isAdmin())																																				// if the current player is an admin
		{	
			Line("Add Games To Guest");																																	// we allow them to add games to the guests account.
			
			bool NoGames = true;																																		// if there are no games in the library we use this variable to make the console look neater when this is the case.
			for (int i = 0; i < p->getLibrary().size(); i++)																													// for all games in players library
			{
				NoGames = false;																																		// no games is set to false as we have games in the library.
																																										// adding 1 so the display is nicer for the user
				Option(i + 1, p->getLibrary()[i]->getName(), Utils::displayTime(p->getLibrary()[i]->getPlayTime()), p->getLibrary()[i]->getPurchaseDate().displayDateNumFormat());		// display admins games.
			}
			if (NoGames)
			{
				Line(" None");
			}
			
		}
	}
}


bool AddGuestGamesMenu::HandleChoice(const char choice)																														// Handle Choice
{
	
	Player* p = dynamic_cast<Player*>(app->getCurrentUser());																											// downcast User pointer to be a Player pointer

	int index = choice - '1';
	Game* gamePtr = nullptr;
	Guest* g = nullptr;

	for(int i = 0; i < app->getStore().games.size(); i++)
	{
		if(p->getLibrary()[index]->getName() == app->getStore().games[i]->item->getName())
		{
			gamePtr = app->getStore().games[i]->item;
			break;
		}
	}

	for(int i = 0; i < app->getCurrentAccount()->getUsers().size(); i++)
	{
		if(app->getCurrentAccount()->getUsers()[i]->item->isGuest())
		{
			g = dynamic_cast<Guest*>(app->getCurrentAccount()->getUsers()[i]->item);
			if (index >= 0 && index < g->getLibrary().size())
			{
				if (gamePtr != nullptr)
				{
					g->getLibrary().push_back(new LibraryItem(Date(), gamePtr, 0,true));

					std::stringstream ss;
					ss << gamePtr->getName() << " added to guest library";
					Line(ss.str());
				}
			}
			break;
		}
	}
	return false;
}