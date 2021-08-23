#include "Guest.h"

Guest::Guest(const std::string& username, const std::string& password, const Date& created) : User(username, password, created)
{
	this->setUsername("Guest");
	this->setPassword("password");
	this->setCreated(Date());
}

std::vector<LibraryItem*> &Guest::getLibrary()
{

	return this->library;
}

bool Guest::isGuest()
{
	return true;
}

Guest::~Guest()
{
	for (int i = 0; i < library.size(); ++i)
	{
		delete library[i];
	}
}