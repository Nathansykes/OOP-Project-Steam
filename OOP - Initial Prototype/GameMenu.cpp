#include "GameMenu.h"

GameMenu::GameMenu(const std::string& title, Application* app, const std::string& game) : Menu(title, app)
{
	this->game = game;
	for(int i = 0; i< app->getStore().games.length();i++)
	{
		if(game == app->getStore().games[i]->item->getName())
		{
			gamePtr = app->getStore().games[i]->item;
		}
	}

	Paint(); // required in constructor
}

void GameMenu::OutputOptions()
{	
	std::stringstream ss;
	ss << gamePtr->getName() << " Rating: " << std::setprecision(3) << gamePtr->getRating() << "%";
	Line();
	Line(ss.str());
	Line();
	Line(gamePtr->getDescription());
	Line();

	ss.str("");
	ss << "\n  Age Rating: " << gamePtr->getAgeRating();
	Line(ss.str()); 

	ss.str("");
	ss << "\n  Price: " << gamePtr->getCost() << " credits.\n";
	Line(ss.str());


	
	if (app->IsUserLoggedIn())
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
			for (int i = 0; i < p->getLibrary().size(); i++)
			{
				if (p->getLibrary()[i]->getName() == gamePtr->getName())
				{
					hasGame = true;
					Option('P', "Play Game");
					if (!p->getLibrary()[i]->isRated())
					{

						Option('+', "Like");

						Option('-', "Dislike");


					}
					else
					{
						Line();
						Line("Game Has Been Rated");
					}
					break;
				}
				else {
					hasGame = false;
				}
			}
			if (!hasGame)
			{
				Option('P', "Purchase Game");
			}
		}

		else if (app->getCurrentUser()->isGuest() && g != nullptr)
		{
			for (int i = 0; i < g->getLibrary().size(); i++)
			{
				if (g->getLibrary()[i]->getName() == gamePtr->getName())
				{
					hasGame = true;
					Option('P', "Play Game");
					break;
				}
				else {
					hasGame = false;
				}
			}
		}
	}

}


bool GameMenu::HandleChoice(const char choice)
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

	bool rated = true;
	LibraryItem* libPtr = nullptr;
	if (p != nullptr)
	{
		for (int i = 0; i < p->getLibrary().size(); i++)
		{
			if (!p->getLibrary()[i]->isRated())
			{
				rated = false;
				libPtr = p->getLibrary()[i];
			}
		}
		switch (choice)
		{
		case 'P'://play the game
		{
			if (hasGame)
			{
				for (int i = 0; i < p->getLibrary().size(); i++)
				{
					if (p->getLibrary()[i]->getName() == gamePtr->getName())
					{
						p->getLibrary()[i]->addPlayTime();
					}
				}
				//p->library[] = p->library[index]->getPlayTime() + Utils::randomTime();
				//p->library[index]->setPlayTime((double)playTime);
			}
			else //purchase game
			{
				if (p->getCredits() > gamePtr->getCost())
				{

					//LibraryItem gamePurchased(Date(), , 0);
					p->getLibrary().push_back(new LibraryItem(Date(), gamePtr, 0, false));

					p->removeCredits(gamePtr->getCost());
					std::stringstream ss;
					ss << "\n You now own " << gamePtr->getName();
					Line(ss.str());
					std::cin.get();
				}
				else
				{
					Line(" Not Enough credits! \n");
					std::cin.get();
				}
				//BlockingMessage("Not implemented, press return to continue");
			}
			break;
		}



		case '+':
		{
			if (!rated)
			{
				gamePtr->addLike();
				libPtr->setRated(true);
			}
			break;
		}
		case '-':
		{
			if (!rated)
			{
				gamePtr->addDislike();
				libPtr->setRated(true);
			}
			break;
		}

		default:
			break;
		}
	}

	else if (app->getCurrentUser()->isGuest() && g != nullptr)
	{
		switch (choice)
		{
		case 'P'://play the game
		{
			for (int i = 0; i < g->getLibrary().size(); i++)
			{
				if (g->getLibrary()[i]->getName() == gamePtr->getName())
				{
					g->getLibrary()[i]->addPlayTime();
				}
			}
		}

		}
	}
	return false;
}
