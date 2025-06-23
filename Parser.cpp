#include "Parser.h"
#include <stdexcept>

bool Parser::isDigit(char ch) 
{
    return ch >= '0' && ch <= '9';
}

bool Parser::isWhitespace(char ch) 
{
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

bool Parser::tryParseInt(const std::string& str, int& out) 
{
    if (str.empty())
    {
        return false;
    }

    int result = 0;
    bool negative = false;
    size_t i = 0;

    if (str[0] == '-') 
    {
        negative = true;
        i = 1;
    }

    if (i >= str.length())
    {
        return false;
    }

    for (size_t i = 0; i < str.length(); ++i) 
    {
        if (!isDigit(str[i]))
        {
            return false;
        }
        result = result * 10 + (str[i] - '0');
    }

    out = negative ? -result : result;
    return true;
}

bool Parser::tryParseDouble(const std::string& str, double& out) 
{
    if (str.empty())
    {
        return false;
    }

    size_t i = 0;
    bool negative = false;
    if (str[0] == '-') 
    {
        negative = true;
        i++;
    }

    double integerPart = 0.0;
    while (i < str.size() && isDigit(str[i])) 
    {
        integerPart = integerPart * 10 + (str[i] - '0');
        i++;
    }

    double fractionalPart = 0.0;
    double divisor = 10.0;

    if (i < str.size() && str[i] == '.') 
    {
        i++;
        while (i < str.size() && isDigit(str[i])) 
        {
            fractionalPart += (str[i] - '0') / divisor;
            divisor *= 10;
            i++;
        }
    }

    if (i != str.size())
    {
        return false;
    }

    out = integerPart + fractionalPart;
    if (negative)
    {
        out = -out;
    }
    return true;
}

bool Parser::tryParseDate(const std::string& str, Date& out) 
{
    size_t firstDot = str.find('.');
    size_t secondDot = str.find('.', firstDot + 1);
    if (firstDot == std::string::npos || secondDot == std::string::npos)
    {
        return false;
    }

    std::string dayStr = str.substr(0, firstDot);
    std::string monthStr = str.substr(firstDot + 1, secondDot - firstDot - 1);
    std::string yearStr = str.substr(secondDot + 1);

    int day, month, year;
    if (!tryParseInt(dayStr, day) || !tryParseInt(monthStr, month) || !tryParseInt(yearStr, year))
    {
        return false;
    }

    try 
    {
        out = Date(day, month, year);
        return true;
    }
    catch (...) 
    {
        return false;
    }
}

std::string Parser::toLower(const std::string& str) 
{
    std::string result = str;
    for (size_t i = 0; i < result.size(); ++i) 
    {
        if (result[i] >= 'A' && result[i] <= 'Z') 
        {
            result[i] = result[i] - 'A' + 'a';
        }
    }
    return result;
}
