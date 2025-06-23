#pragma once
#include <string>
#include <stdexcept>

/// \brief Class representing a calendar date.

class Date
{
public:
    /// \brief Default constructor. Initializes an invalid or empty date.
    Date();

    /// \brief Constructs a Date with day, month, and year.
    /// \param d Day (1-31 depending on month)
    /// \param m Month (1-12)
    /// \param y Year (e.g., 2024)
    Date(int d, int m, int y);

    /// \brief Gets the day of the date.
    /// \return The day (1-31)
    int getDay() const;

    /// \brief Gets the month of the date.
    /// \return The month (1-12)
    int getMonth() const;

    /// \brief Gets the year of the date.
    /// \return The year
    int getYear() const;

    /// \brief Converts the date to string in format DD.MM.YYYY.
    /// \return String representation of the date.
    std::string toString() const;

    /// \brief Equality operator.
    /// \param other The date to compare with.
    /// \return True if both dates are equal.
    bool operator==(const Date& other) const;

    /// \brief Inequality operator.
    /// \param other The date to compare with.
    /// \return True if dates are not equal.
    bool operator!=(const Date& other) const;

    /// \brief Less than operator.
    /// \param other The date to compare with.
    /// \return True if this date is earlier than the other.
    bool operator<(const Date& other) const;

    /// \brief Less than or equal to operator.
    /// \param other The date to compare with.
    /// \return True if this date is earlier than or equal to the other.
    bool operator<=(const Date& other) const;

    /// \brief Greater than operator.
    /// \param other The date to compare with.
    /// \return True if this date is later than the other.
    bool operator>(const Date& other) const;

    /// \brief Greater than or equal to operator.
    /// \param other The date to compare with.
    /// \return True if this date is later than or equal to the other.
    bool operator>=(const Date& other) const;

    /// \brief Parses a date from string in format DD.MM.YYYY.
    /// \param str String representation of the date.
    /// \return Parsed Date object.
    static Date parse(const std::string& str);

private:
    int day;   ///< Day of the month (1-31)
    int month; ///< Month of the year (1-12)
    int year;  ///< Year

    /// \brief Checks if a given year is a leap year.
    /// \param year Year to check.
    /// \return True if leap year.
    static bool isLeapYear(int year);

    /// \brief Validates a date.
    /// \param day Day of the month.
    /// \param month Month of the year.
    /// \param year Year.
    /// \return True if the date is valid.
    static bool isValidDate(int day, int month, int year);
};

