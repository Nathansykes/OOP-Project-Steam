#pragma once

#include <string>

class Game
{
	public:
		Game(const std::string&, const std::string&, const int&, const int&, const int&, const int&);
		~Game();

		// Accessors
		const std::string& getName() const;
		const std::string& getDescription() const;
		const int& getCost() const;
		const int& getAgeRating() const;
		const float getRating() const;
		const int& getLikes() const;
		const int& getDislikes() const;

		// Mutators
		void addLike();
		void addDislike();

	private:
		int likes;
		int dislikes;
		std::string name;
		std::string description;
		int cost;
		int ageRating;
};