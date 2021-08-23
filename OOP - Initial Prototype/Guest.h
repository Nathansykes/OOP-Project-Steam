#pragma once

#include <string>
#include <vector>
#include "LibraryItem.h"
#include "User.h"

class Guest : public User
{
public:
	Guest(const std::string& username, const std::string& password, const Date&);
	~Guest();

	// Accessors

	std::vector<LibraryItem*> &getLibrary();
	bool isGuest() override;

private:
	std::vector<LibraryItem*> library;
};
