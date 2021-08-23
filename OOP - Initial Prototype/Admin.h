#pragma once

#include <string>
#include "Player.h"
#include "Date.h"

class Admin : public Player
{
	public:
		Admin(const std::string&, const std::string&, const Date&, const int&);
		~Admin();

		// Accessors

		void setGuestGames();
		bool isAdmin() override;
};