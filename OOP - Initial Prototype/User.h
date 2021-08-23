#pragma once

#include <string>
#include "Date.h"

class User
{
	public:
		// constructor
		
		User(const std::string&, const std::string&, const Date&);
		virtual ~User();
		virtual bool isAdmin();
		virtual bool isGuest();

		// Accessors

		const std::string& getUsername() const;
		const std::string& getPassword() const;
		const Date& getCreated() const;
		const int& getCredits() const;

		// Mutators

		void setUsername(const std::string& username);
		void setPassword(const std::string& password);
		void setCreated(const Date& created);
		void setCredits(const int& credits);
		void removeCredits(const int& credits);

	private:
		std::string username;
		std::string password;
		Date created;  // TODO: replace with custom Date class, currently YYYY-MM-DD
		int credits;
		
};