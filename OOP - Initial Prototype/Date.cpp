#pragma warning(disable : 4996)													// local time function is seen as unsafe
#include <iostream>
#include <string>
#include <ctime>
#include "Date.h"

Date::Date(const int& day, const int& month, const int& year)					// If we want to create a date with specified data.
	:day(day), month(month), year(year)
{
}

Date::Date()																	// If we want to create a date object with the current date.
{
	time_t t = time(0);
	struct tm* now = localtime(&t);
	year = now->tm_year + 1900;
	month = now->tm_mon + 1;
	day = now->tm_mday;
}


// Accessors
const int Date::getDay() const													// Returns Day
{
	return this->day;
}

const int Date::getMonth() const												// Returns Month 
{
	return this->month;		
}

const int Date::getYear() const													// Returns Year
{
	return this->year;
}

std::string Date::displayDateNumFormat() const									// Display the Data in different formats 
{
	std::stringstream ss;
	ss << this->day << "-" << this->month << "-" << this->year;					// Displays the date as so 17-03-2021.
	return ss.str();
}

std::string Date::displayDateWrittenFormat() const								// Displays the date as so 17-March-2021. 
{
	std::string writtenMonth;

	switch (month)																// Switch statement to convert the month(number) to month(written format).
	{
	case 1:
		writtenMonth = "January";
		break;
	case 2:
		writtenMonth = "Febuary";
		break;
	case 3:
		writtenMonth = "March";
		break;
	case 4:
		writtenMonth = "April";
		break;
	case 5:
		writtenMonth = "May";
		break;
	case 6:
		writtenMonth = "June";
		break;
	case 7:
		writtenMonth = "July";
		break;
	case 8:
		writtenMonth = "August";
		break;
	case 9:
		writtenMonth = "September";
		break;
	case 10:
		writtenMonth = "October";
		break;
	case 11:
		writtenMonth = "November";
		break;
	case 12:
		writtenMonth = "December";
		break;
	}

	std::stringstream ss;
	ss << this->day << "-" << writtenMonth << "-" << this->year;
	return ss.str();
}


bool Date::operator< (const Date& rhs) const												// Sorting/Overload of the '<' operator to sort the games by date purchased.
{

	if (this->year < rhs.year) return true;
	if (this->year > rhs.year) return false;

	if (this->month < rhs.month) return true;
	if (this->month > rhs.month) return false;

	return this->day < rhs.day;
}

bool Date::IsDateBefore(const Date& secondDate) const										// Checks whice date is first.
{
	if (this->year < secondDate.year)
	{
		return true;
	}
	else if (this->month < secondDate.month)
	{
		return true;
	}
	else if (this->month < secondDate.day)
	{
		return true;
	}
	else
	{
		return false;
	}
}
