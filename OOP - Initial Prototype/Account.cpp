#include "Account.h"

// constructors

Account::Account(const std::string& email, const std::string& password, const Date& created)
	: email(email), password(password), created(created)
{
	
}

Account::~Account()
{
	for (int i = 0; i < users.size(); ++i)
	{
		delete users[i]->item;
	}
}

// accessors

const std::string& Account::getEmail() const
{
	return this->email;
}

const std::string& Account::getPassword() const
{
	return this->password;
}

const Date& Account::getCreated() const // Needs to be changed to custom date class 
{
	return this->created;
}

List<User*> &Account::getUsers()
{

	return this->users;
}

// mutators

void Account::setPassword(const std::string& password)
{
	this->password = password;
}

void Account::setEmail(const std::string& email) 
{
	this->email = email;
}

void Account::setCreated(const Date& created) 
{
	this->created = created;
}