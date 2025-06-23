#include "Date.h"
#include "Parser.h"

Date::Date() : day(0), month(0), year(0) {}

Date::Date(int d, int m, int y) 
{
    if (!isValidDate(d, m, y)) 
    {
        throw std::invalid_argument("Invalid date: " + std::to_string(d) + "." + std::to_string(m) + "." + std::to_string(y));
    }
    day = d;
    month = m;
    year = y;
}

int Date::getDay() const 
{ 
    return day; 
}
int Date::getMonth() const 
{ 
    return month; 
}
int Date::getYear() const 
{ 
    return year; 
}

std::string Date::toString() const 
{
    return std::to_string(day) + "." + std::to_string(month) + "." + std::to_string(year);
}

bool Date::isLeapYear(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool Date::isValidDate(int d, int m, int y) 
{
    if (y < 1900 || m < 1 || m > 12 || d < 1) 
    {
        return false;
    }

    int daysInMonth[] = { 31, isLeapYear(y) ? 29 : 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    return d <= daysInMonth[m - 1];
}


bool Date::operator==(const Date& other) const 
{
    return day == other.day && month == other.month && year == other.year;
}
bool Date::operator!=(const Date& other) const 
{ 
    return !(*this == other); 
}
bool Date::operator<(const Date& other) const 
{
    if (year != other.year) 
    {
        return year < other.year;
    }
    if (month != other.month) 
    {
        return month < other.month;
    }
    return day < other.day;
}
bool Date::operator<=(const Date& other) const 
{
    return *this < other || *this == other; 
}
bool Date::operator>(const Date& other) const 
{ 
    return !(*this <= other); 
}
bool Date::operator>=(const Date& other) const 
{
    return !(*this < other); 
}

Date Date::parse(const std::string& str) 
{
    Date result;
    if (!Parser::tryParseDate(str, result)) 
    {
        throw std::invalid_argument("Invalid date string: " + str);
    }
    return result;
}
