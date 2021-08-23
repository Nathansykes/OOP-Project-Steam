#include "Utils.h"
#include <sstream>

std::string Utils::getLineFromUser()
{
    std::string input;
    std::getline(std::cin, input);
    return input;
}

char Utils::getCharFromUser()
{
    return toupper(getLineFromUser()[0]);
}
                                                                            //***Looped toUpper function.
std::string Utils::toUpperLoop(const std::string& str)                      // A way of making a toUpper function for a string using a loop.
{
    char* letters = new char[str.length() + 1];
    strcpy_s(letters, strlen(letters), str.c_str());

    for (int x = 0; x < strlen(letters); x++)
    {
        if (letters[x] >= 97 && letters[x] <= 122)                           // if beetween 92 and 122 = is lower case
        {
            letters[x] = letters[x] - 32;                                    // minus 32 to change to upper case
        }
    }

    std::string upperCase(letters);

    return upperCase;
   
}
                                                                            //***Recursive ToUpper Function***
void Utils::recursiveUpper(char str[])                                      // A way of making a toUpper function for a string using recursion.
{
    if(str[0] == '\0') return; //Base Case
    str[0] = tolower( str[0] ); 
    recursiveUpper( str+1 ); 
}
                                                                            //***Random Time***
float Utils::randomTime()                                                   // A way of making a toUpper function for a string using recursion.
{
    float i = 0.0f;                                                         // Set float i to 0.0f. 
                
    i = (rand() % 60);                                                      // i is set to a random number between 1 and 60.    

    return i;                                                               // the function returns i, the random time.
}
                                                                            //***Display Time Function
std::string Utils::displayTime(float time)                                  // A function to dynamically display time, depending on the amount of time on the clock.
{
    std::string display = "";                                               // Setting up empty string.

    if (time >= 60)                                                         // If the time is over an hour.                
    {
        time = time / 60;                                                   // then time is set to itself divided by 60.    
        std::ostringstream ss;
        ss << std::setprecision(3) << time << " hours";
        display = ss.str();                                                                   
    }
    else 
    {
        std::ostringstream ss;
        ss << time << " minutes";
        display = ss.str();
    }
    return display;
}

bool Utils::StartsWith(const std::string& fullText, const std::string& searchText) 
{
    int searchLength = searchText.length();

    std::string sub = fullText.substr(0, searchLength);

    if((toUpperLoop(sub) == toUpperLoop(searchText)))
    {
        return true;
    }

    return false;
}