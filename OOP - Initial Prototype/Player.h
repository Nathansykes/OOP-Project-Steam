#pragma once

#include <string>
#include <vector>
#include "LibraryItem.h"
#include "User.h"
#include "ListT.h"
#include "Date.h"

class Player : public User
{
	public:
		Player(const std::string&, const std::string&, const Date&, const int&);
		~Player();

		// Accessors

		std::vector<LibraryItem*> &getLibrary();
	private:
		std::vector<LibraryItem*> library;
};