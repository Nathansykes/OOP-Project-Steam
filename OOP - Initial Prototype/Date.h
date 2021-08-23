#pragma once
#include <iostream>
#include <string>
#include <ctime>
#include <sstream>


class Date
{
private:

	// data members.
	int day, month, year;

public:

	// constructors.
	Date(const int& day, const int& month, const int& year);	// if we call this constructor we must specify the data.
	Date();														// if we call this constructor the current date is provided for the data members.

	// accessors.
	const int getDay() const;
	const int getMonth() const;
	const int getYear() const;

	// useful stuff.
	std::string displayDateNumFormat() const;
	std::string displayDateWrittenFormat() const;

	bool IsDateBefore(const Date& secondDate) const;

	// Operator Overloads.
	bool operator< (const Date& rhs) const;




};

