#include "User.h"

User::User(const std::string& username, const std::string& password, const Date& created)
	: username(username), password(password), created(created)
{
}

User::~User()
{
}

// accessors

bool User::isAdmin()
{
	return false;
}

bool User::isGuest()
{
	return false;
}

const std::string& User::getUsername() const
{
	return this->username;
}

const std::string& User::getPassword() const
{
	return this->password;
}

const Date& User::getCreated() const 
{
	return this->created;
}

const int& User::getCredits() const
{
	return this->credits;
}


// mutators

void User::setUsername(const std::string& username)
{
	this->username = username;
}

void User::setPassword(const std::string& password)
{
	this->password = password;
}

void User::setCreated(const Date& created)
{
	this->created = created;
}

void User::setCredits(const int& credits)
{
	this->credits = this->credits + credits;
}

void User::removeCredits(const int& credits)
{
	this->credits = this->credits - credits;
}