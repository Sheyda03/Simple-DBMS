#pragma once
#include <string>
#include "Date.h"

/// \brief Utility class for parsing strings into typed values and basic string utilities.
class Parser
{
public:
    /// \brief Tries to parse a string into an integer.
    /// \param str The input string to parse.
    /// \param out Reference to an integer where the result will be stored if parsing succeeds.
    /// \return True if the string was successfully parsed into an integer, false otherwise.
    static bool tryParseInt(const std::string& str, int& out);

    /// \brief Tries to parse a string into a double.
    /// \param str The input string to parse.
    /// \param out Reference to a double where the result will be stored if parsing succeeds.
    /// \return True if the string was successfully parsed into a double, false otherwise.
    static bool tryParseDouble(const std::string& str, double& out);

    /// \brief Tries to parse a string into a Date object.
    /// \param str The input string to parse (expected in DD.MM.YYYY format).
    /// \param out Reference to a Date object to hold the parsed result.
    /// \return True if parsing was successful and the date is valid, false otherwise.
    static bool tryParseDate(const std::string& str, Date& out);

    /// \brief Converts a string to lowercase.
    /// \param str The string to convert.
    /// \return A lowercase version of the input string.
    static std::string toLower(const std::string& str);

    /// \brief Checks if a character is a digit (0-9).
    /// \param ch The character to check.
    /// \return True if the character is a digit, false otherwise.
    static bool isDigit(char ch);

    /// \brief Checks if a character is a whitespace (space, tab, etc.).
    /// \param ch The character to check.
    /// \return True if the character is a whitespace character, false otherwise.
    static bool isWhitespace(char ch);
};

