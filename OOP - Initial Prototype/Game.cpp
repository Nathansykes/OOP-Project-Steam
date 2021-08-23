#include "Game.h"

//Constructors

Game::Game(const std::string& name, const std::string& desc, const int& cost, const int& rating, const int& likes, const int& dislikes)
	: name(name), description(desc), cost(cost), ageRating(rating), likes(likes), dislikes(dislikes)
{
}

Game::~Game()
{
}

//Accessors

const std::string& Game::getName() const				//Returns the games name.
{
	return name;
}

const std::string& Game::getDescription() const			//Returns games description.
{
	return description;									
}

const int& Game::getCost() const						//Returns the games cost.
{
	return cost;
}

const int& Game::getAgeRating() const					//Returns age rating.
{
	return ageRating;
}

const int& Game::getLikes() const						//Returns likes.
{
	return likes;
}

const int& Game::getDislikes() const
{
	return dislikes;
}

//Mutators

const float Game::getRating() const							//This function takes likes and dislikes on a game and, returns the percentage for the game.
{
	if (likes == 0)											//This stops the program from outputting weird things
	{
		return 0;
	}
	if (dislikes == 0)										//This stops the program from outputting weird things									
	{
		return 100;
	}
	else
	{
		float total = likes + dislikes;						// (Likes / (Likes + Dislikes)) * 100 will return the percentage.
		float rating = likes / total;
		rating = rating * 100;
		return rating;
	}
}

void Game::addLike()
{
	likes++;
}

void Game::addDislike() 
{
	dislikes++;
}