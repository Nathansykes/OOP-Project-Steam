#pragma once

#include <cstring>
#include <string>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <algorithm>


class Utils
{
  public:
    // Accessors
    static std::string      getLineFromUser();
    static char             getCharFromUser();
    static std::string      displayTime(const float time);
    static bool             StartsWith(const std::string& fullText, const std::string& searchText);

    // Mutators
    static std::string      toUpperLoop(const std::string& str);
    static void             recursiveUpper(char str[]);
    static float            randomTime();
};