#pragma once

#include "Game.h"
#include "Date.h"
#include "Utils.h"
#include <string>

class LibraryItem
{
	public:

		// Constructors
		LibraryItem(const Date&, const Game*, const int playtime, const bool rated);
		~LibraryItem();

		// Accessors
		const std::string& getName() const;
		const Date& getPurchaseDate() const;
		const int getPlayTime() const;

		// Mutators
		void addPlayTime();
		void setPlayTime(int& playtime);
		void setRated(bool hasRated);
		const bool isRated() const;

	private:
		const Game* game;
		const Date  purchased;
		bool rated;
		int	playTime;
};