#pragma once

#include <string>
#include "Player.h"
#include "ListT.h"
#include "Date.h"
#include "Guest.h"

class Account
{
	public:
		Account(const std::string&, const std::string&, const Date&);
		~Account();

		// Accessors

		const std::string& getEmail() const;
		const std::string& getPassword() const;
		const Date& getCreated() const;
		List<User*> &getUsers();

		// Mutators

		void setEmail(const std::string& email);
		void setPassword(const std::string& password);
		void setCreated(const Date& created);

	private:
		List<User*> users;
		std::string email;
		std::string password;
		Date created; 
};