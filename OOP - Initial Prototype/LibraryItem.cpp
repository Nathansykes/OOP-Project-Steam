#include "LibraryItem.h"


//Constructors.

LibraryItem::LibraryItem(const Date& date, const Game* game, const int playTime, const bool rated)
	: purchased(date), game(game), playTime(playTime), rated(rated)
{
}

LibraryItem::~LibraryItem()
{
}

//Accessors.

const std::string& LibraryItem::getName() const					//Get the games name.
{
	return game->getName();
	
}

const Date& LibraryItem::getPurchaseDate() const				//Return Purchase date
{
	return purchased;
}

const int LibraryItem::getPlayTime() const						//Return Playtime
{
	return this->playTime;
}

const bool LibraryItem::isRated() const							//Checks if the library item has been rated by the player.
{
	return rated;
}

//Mutators.

void LibraryItem::addPlayTime()			
{
	this->playTime += Utils::randomTime();						//Playtime is set to playtime + a random amount of time between one and 60.

}

void LibraryItem::setPlayTime(int& playTime)					//Sets play time.
{
	this->playTime = playTime;
}

void LibraryItem::setRated(bool hasRated)						//Sets rated, if the game has already been rated by the palyer upon startup of the system. 
{
	rated = hasRated;
}