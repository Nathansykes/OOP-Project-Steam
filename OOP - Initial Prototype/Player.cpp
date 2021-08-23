#include "Player.h"

Player::Player(const std::string& username, const std::string& password, const Date& created, const int& credits)
	: User(username, password, created)
{
	this->setCredits(credits);
}
Player::~Player()
{
	for (int i = 0; i < library.size(); ++i)
	{
		delete library[i];
	}
}

std::vector<LibraryItem*>& Player::getLibrary()
{

	return this->library;
}
