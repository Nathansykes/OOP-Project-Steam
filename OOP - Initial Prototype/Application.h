#pragma once

#include "Account.h"
#include "User.h"
#include "Store.h"
#include "ListT.h"
#include "Admin.h"
#include "Player.h"

class Application
{
	public:
		// constructors

		Application();
		~Application();
		void Load();
		void Save();

		// accessors

		const bool IsAccountLoggedIn() const;
		const bool IsUserLoggedIn() const;
		Account* getCurrentAccount() const;
		User* getCurrentUser() const;
		Store& getStore();

		// mutators

		bool LoginAccount(const std::string& email, const std::string& password);
		bool LoginUser(const std::string& username, const std::string& password);
		bool LoginGuest();
		void LogoutUser();
		void LogoutAccount();
		
	private:
		List<Account*> accounts;
		Store store;
		Account* currentAccount;
		User* currentUser;
};