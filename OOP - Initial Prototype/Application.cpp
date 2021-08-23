#include "Application.h"
#include <fstream>
#include <sstream>
#include <iostream>

//Constructors

Application::Application() : currentAccount(nullptr), currentUser(nullptr)
{
}

Application::~Application()
{
	for (int i = 0; i < accounts.size(); ++i)
	{
		delete accounts[i]->item;
	}
}

// Accessors

const bool Application::IsUserLoggedIn() const																	// Checks if there is a User logged in to the system. 
{
	return currentUser != nullptr;
}

const bool Application::IsAccountLoggedIn() const																// Checks if there is a User logged in to the system. 												
{
	return currentAccount != nullptr;
}

Account* Application::getCurrentAccount() const																	// Returns current account.
{
	return currentAccount;
}

User* Application::getCurrentUser() const																		// Return current user.
{
	return currentUser;
}

Store& Application::getStore()																					// Return store
{
	return store;
}

//Mutators

bool Application::LoginAccount(const std::string& email, const std::string& password)							// Login Account function.
{
	for (int i = 0; i < accounts.size(); i++)																	// For each account in accounts
	{
		if (accounts[i]->item->getEmail() == email && accounts[i]->item->getPassword() == password)							
		{
			currentAccount = accounts[i]->item;
			return true;
		}
	}
	return false;
}

bool Application::LoginUser(const std::string& username, const std::string& password)							// Login User very simular to Login Account
{
	for (int i = 0; i < currentAccount->getUsers().size(); i++) 
	{
		if (currentAccount->getUsers()[i]->item->getUsername() == username && currentAccount->getUsers()[i]->item->getPassword() == password)		// Checks both password and username matches from one user in users list
		{
			currentUser = currentAccount->getUsers()[i]->item;
			return true;
		}	
	}
	return false;
}

bool Application::LoginGuest()																					// Function for logging in guest, no password needed
{
	for (int i = 0; i < currentAccount->getUsers().size(); i++)
	{		
		if (currentAccount->getUsers()[i]->item->isGuest())
		{
			currentUser = currentAccount->getUsers()[i]->item;
			return true;
		}
	}
	return false;
}

void Application::LogoutUser()																					// Logout user function makes current user return nullptr
{
	currentUser = nullptr;
}

void Application::LogoutAccount()																				// Logout account function makes both current user and account nullptr
{
	currentUser = nullptr;
	currentAccount = nullptr;
}

Date convertDate(std::string& line)																				// Function used to convert line from persistance into a date object
{
	int day = 0;
	int month = 0;
	int year = 0;
	int count = 0;
	std::string delimiter = "-";

	size_t pos = 0;																								// Size_t = 0;
	std::string token;																							// Sets up a string as a 'token' which will save what we are getting out of the string we are converting, temporarliy.
	while ((pos = line.find(delimiter)) != std::string::npos)													// While there are still delimiters in the string.
	{
		token = line.substr(0, pos);																			// We set token to the substr between the beginning of the string and the delimiter.

		if (count == 0) { year = stoi(token); }																	// If it is the first actual value in the string it is a year value.
		if (count == 1) { month = stoi(token); }																// If it is the secons value in the string it is a month value.
		if (count == 2) { day == stoi(token); }																	// If it is third value in the string it is a day value.			

		line.erase(0, pos + delimiter.length());																// After each run of the while loop, the beginiing of the string (the value that has been found) is deleted along with the delimiter.
		count++;																								// Increases count so that we know if the next value is a month or day.
	}
	day = stoi(line);																							// After the function has run you can never get the last value from a string inside a loop, but the last token is the day.

	Date date = Date(day, month, year);																			// Instantiates a Date object using the values we have just found.

	return date;																								// Returns date.
}

void Application::Load()																						// Function to load in data from presistance file
{
	std::ifstream infile("data.txt");																			// Reads from data.txt
	std::string line;
	std::vector<std::string> lines = { };																		// We will seperate the data into 3 vectors of strings (helps break up for initalisation)
	std::vector<std::string> games = { };
	std::vector<std::string> accounts = { };

	while (std::getline(infile, line))																			// Reads in whole file into vector called lines
	{
		lines.push_back(line);
	}

	for (int i = 0; i < lines.size(); i++)																		// Loop through Lines
	{																											// We have done this so we can see which lines are stored ahead of our capitalised headers in the txt file
		if (lines[i] == "GAME")																					// If line equals GAME
		{
			games.push_back(lines[i]);																			// Add Header with additional 6 attributes to games string vector 
			games.push_back(lines[i + 1.0]);
			games.push_back(lines[i + 2.0]);
			games.push_back(lines[i + 3.0]);
			games.push_back(lines[i + 4.0]);
			games.push_back(lines[i + 5.0]);
			games.push_back(lines[i + 6.0]);
			games.push_back(lines[i + 7.0]);
		}
		if (lines[i] == "ACCOUNT")																				// Same process for account, however we store everything past game
		{
			int index = i;
			for (index; index < lines.size(); index++)
			{
				accounts.push_back(lines[index]);
			}
		}
	}

	for (int i = 0; i < games.size() - 6; i += 8)																// Loop through games vector 8 indexs a time
	{
		int counter = 0;																						// Break up all the data into variables
		std::string title = games[i + 2.0];
		std::string description = games[i + 3.0];
		int cost = stoi(games[i + 4.0]);
		int rating = stoi(games[i + 5.0]);
		int likes = stoi(games[i + 6.0]);
		int dislikes = stoi(games[i + 7.0]);

		getStore().games.addAtEnd(new Game(title, description, cost, rating, likes, dislikes));					// Instantiate a game object using the varibles 
	}

	std::reverse(accounts.begin(), accounts.end());																//** reverse so that library items can be read before the user then added to a list **
																												// and then attached to the user, then the list can be cleared ready for the next user
	std::vector<LibraryItem*> libraryItems = { };
	std::vector<User*> users = { };

	Account* account = nullptr;

	for (int i = 0; i < accounts.size(); i++)																	// Loop through our vector list of account
	{
		if (accounts[i] == "LIBRARY-ITEM")																		// If index is equal to a library item
		{
			int playTime = stoi(accounts[i - 3.0]);																// Store all attributes of library into varibles
			Date date = convertDate(accounts[i - 2.0]);
			int gameIndex = stoi(accounts[i - 1.0]);
			bool rated = false;

			if (accounts[i - 4.0] == "1") { rated = true; }
			
			Game* gamePtr = getStore().games[gameIndex]->item;

			libraryItems.push_back(new LibraryItem(date, gamePtr, playTime, rated));							// Instantiate a LibraryItem object using the varibles 
		}

		if (accounts[i] == "ACCOUNT-PLAYER")																	// Same process follows for Account-Player
		{
			Date date = convertDate(accounts[i - 1.0]);
			std::string name = accounts[i - 2.0];
			std::string password = accounts[i - 3.0];
			int credits = stoi(accounts[i - 4.0]);

			Player* player = new Player(name, password, date, credits);

			for (int x = 0; x < libraryItems.size(); x++)
			{
				player->getLibrary().push_back(libraryItems[x]);
			}

			users.push_back(player);
			libraryItems.clear();
		}

		if (accounts[i] == "ACCOUNT-ADMIN")																		// Furthermore for Admin
		{
			Date date = convertDate(accounts[i - 1.0]);
			std::string name = accounts[i - 2.0];
			std::string password = accounts[i - 3.0];
			int credits = stoi(accounts[i - 4.0]);

			Player* admin = new Admin(name, password, date, credits);

			for (int x = 0; x < libraryItems.size(); x++)
			{
				admin->getLibrary().push_back(libraryItems[x]);
			}

			users.push_back(admin);
			libraryItems.clear();
		}

		if (accounts[i] == "ACCOUNT-GUEST")																		// Additionally for guest
		{
			
			Guest* guest = new Guest("Guest", "", Date());
			
			for (int x = 0; x < libraryItems.size(); x++)
			{
				guest->getLibrary().push_back(libraryItems[x]);
			}
			users.push_back(guest);
			libraryItems.clear();
		}

		if (accounts[i] == "ACCOUNT")																			// Finally for Account the object will be related too
		{
			Date date = convertDate(accounts[i - 1.0]);
			std::string email = accounts[i - 2.0];
			std::string password = accounts[i - 3.0];

			Account* account = new Account(email, password, date);

			for (int x = 0; x < users.size(); x++)
			{
				account->getUsers().addAtEnd(users[x]);
			}

			this->accounts.addAtEnd(account);
			users.clear();
		}
	}
}

void Application::Save()																				// save state of appliction
{																																					
	std::ofstream Save("data.txt");																		//output to txt file

	if (!Save.fail())																															
	{
		for (int i = 0; i < getStore().games.size(); i++)												//loop through all the games
		{
			Game* tempGame = getStore().games[i]->item;
			Save << "GAME" << "\n";																		// add a game header 
			Save << i << "\n";
			Save << tempGame->getName() << "\n";
			Save << tempGame->getDescription() << "\n";
			Save << tempGame->getCost() << "\n";
			Save << tempGame->getAgeRating() << "\n";
			Save << tempGame->getLikes() << "\n";
			Save << tempGame->getDislikes() << "\n";													// add all the info about the game to new line
		}

		for (int i = 0; i < accounts.size(); i++)														// loop through all accounts
		{
			int day = accounts[i]->item->getCreated().getDay();										
			int month = accounts[i]->item->getCreated().getMonth();
			int year = accounts[i]->item->getCreated().getYear();										// get the parts of the date

			Save << "ACCOUNT" << "\n";																	// account header
			Save << year << "-" << month << "-" << day << "\n";											// format the date and write line
			Save << accounts[i]->item->getEmail() << "\n";
			Save << accounts[i]->item->getPassword() << "\n";

			accounts[i]->item->getUsers().reverse();													// reverse so it is written to file same way as provided 
																										// *and so that library items can be read in first* **SEE  ABOVE**

			for (int j = 0; j < accounts[i]->item->getUsers().size(); j++)								// loop through the users
			{
				User* tempUser = accounts[i]->item->getUsers()[j]->item;								// create a temporary user pointer to shorten code

				if(tempUser->isGuest())																	// if user is guest
				{
					Save << "ACCOUNT-GUEST" << "\n";													// write header
						
					Guest* g = dynamic_cast<Guest*>(tempUser);											// downcast

					for (int k = 0; k < g->getLibrary().size(); k++)									// loop through library items
					{
						Save << "LIBRARY-ITEM" << "\n";													// write header

						for (int l = 0; l < getStore().games.size(); l++)								// loop through games
						{
							if (g->getLibrary()[k]->getName() == getStore().games[l]->item->getName())	// find the game matching the library item
							{
								Save << l << "\n";														// save its index
							}
						}

						const Date purchaseDate = g->getLibrary()[k]->getPurchaseDate();				// save purchased date
						day = purchaseDate.getDay();													
						month = purchaseDate.getMonth();
						year = purchaseDate.getYear();

						Save << year << "-" << month << "-" << day << "\n";								// save formatted date

						Save << g->getLibrary()[k]->getPlayTime() << "\n";								// save playtime
						Save << "1" << "\n";															// is guest so "isRated" set true so they cannot rate anygames
					}
				}
				else
				{				
					if (tempUser->isAdmin())															// check if is admin or player
					{																					// write correct header
						Save << "ACCOUNT-ADMIN" << "\n";
					}
					else
					{
						Save << "ACCOUNT-PLAYER" << "\n";
					}

					day = tempUser->getCreated().getDay();
					month = tempUser->getCreated().getMonth();
					year = tempUser->getCreated().getYear();

					Save << year << "-" << month << "-" << day << "\n";													// save the formatted date
					Save << tempUser->getUsername() << "\n";
					Save << tempUser->getPassword() << "\n";
					Save << tempUser->getCredits() << "\n";

					Player* p = dynamic_cast<Player*>(tempUser);														// downcast user to player

					for (int k = 0; k < p->getLibrary().size(); k++)													// For each item in the library.
					{
						Save << "LIBRARY-ITEM" << "\n";																		// Adds line to savedata
						for (int l = 0; l < getStore().games.size(); l++)												
																																	// For each game in games. 
						{
							if (p->getLibrary()[k]->getName() == getStore().games[l]->item->getName())					// If the librarys game name matches up with the 
							{
								Save << l << "\n";
							}
						}

						const Date purchaseDate = p->getLibrary()[k]->getPurchaseDate();
						day = purchaseDate.getDay();																	// Returns the day from purchase date object.
						month = purchaseDate.getMonth();																// Returns the month from purchase date object.
						year = purchaseDate.getYear();																	// Returns the year from purchase date object.

						Save << year << "-" << month << "-" << day << "\n";												// Once each element is in local memory, add the purchase date in 'YYYY-MM-DD' format to save data

						Save << p->getLibrary()[k]->getPlayTime() << "\n";												// Adds the games playtime from a player to save data.
						Save << p->getLibrary()[k]->isRated() << "\n";													// Adds if the game is rated or not to the save data.
					}
				}
			}
		}
	}
}


