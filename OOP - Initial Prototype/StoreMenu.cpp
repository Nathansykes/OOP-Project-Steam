#include "StoreMenu.h"


StoreMenu::StoreMenu(const std::string& title, Application* app) : Menu(title, app)
{
	Paint(); // required in constructor
}

void StoreMenu::OutputOptions()
{
	if (games.size() <= 0) 
	{
		for (int i = 0; i < app->getStore().games.size(); i++)
		{
			games.push_back(app->getStore().games[i]->item);
		}
	}

	Option('S',"Search By Name");
	Option('P',"Search By Price");
	Option('R',"Sort By Rating");
	Line();

	for (int i = 0; i < games.size(); i++)
	{
		if(Utils::StartsWith(games[i]->getName(), searchText) && (games[i]->getCost() > minPrice && games[i]->getCost() < maxPrice))			// search by price and name
		{
			std::stringstream ss;
			ss << std::left << std::setw(25) << games[i]->getName() << " Rating: " << std::setprecision(3) << games[i]->getRating() << "%";
			Option(i + 1, ss.str());
		}
	}
} 

bool sortRating(const Game* l1, const Game* l2)											// sorts rating by comparing games rating
{
	return l1->getRating() > l2->getRating();
}

bool StoreMenu::HandleChoice(const char choice)
{
	int index = choice - '1';

	if (index >= 0 && index < games.size())
	{
		GameMenu("GAME", app, games[index]->getName());
	}

	switch (choice) 
	{
		case 'S':
		{
			Line();
			searchText = Question("Search Name");										// sort by name
			minPrice = 0;
			maxPrice = 100000;
			break;
		}
		case 'P':
		{
			try {
				Line();
				minPrice = stoi(Question("Enter your minimum price"));					// asks for price to be inputted
				maxPrice = stoi(Question("Enter your maximum price"));
			}
			catch(std::exception e)
			{
				minPrice = 0;
				maxPrice = 10000;
			}
			
			searchText = "";
			break;
		}
		case 'R':
		{
			std::sort(games.begin(), games.end(), sortRating);					// sort rating by function
			break;
		}
		default:
			break;
	}

	return false;
}