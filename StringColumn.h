#pragma once
#include "Column.h"
#include <vector>
#include <string>

/// \brief Class for string column type
class StringColumn : public Column 
{
public:
    /// \brief Constructor accepting column name as parameter
    StringColumn(const std::string& name);

    std::string getTypeName() const override;
    Column* clone() const override;

    void addEmpty() override;
    void addValue(const std::string& value) override;

    void setValueAt(size_t index, const std::string& value) override;
    std::string getValueAt(size_t index) const override;

    bool compare(size_t index, const std::string& value) const override;
    void updateValue(size_t index, const std::string& value) override;

    void removeRow(size_t index) override;
    size_t size() const override;

    void serialize(std::ostream& out) const override;
    void deserialize(std::istream& in, size_t rowsCount) override;
private:
    std::vector<std::pair<std::string, bool>> data; ///< field for storing row values\n
                                                    /// which are pairs having a boolean\n
                                                    /// as second value which is 'false' if\n
                                                    /// the cell is 'NULL'

    /// \brief Escapes special characters in a string for safe serialization.
    /// \param raw The input raw string.
    /// \return The escaped version of the string.
    static std::string escapeString(const std::string& raw);

    /// \brief Reverses the effect of escapeString by converting escape sequences back to characters.
    /// \param raw The escaped string.
    /// \return The unescaped, original version of the string.
    static std::string unescapeString(const std::string& raw);

    /// \brief Compares if string `b` is a case-insensitive substring of string `a`.
    /// \param a The main string.
    /// \param b The substring to look for.
    /// \return True if `b` is a substring of `a` (case-insensitive), false otherwise.
    static bool compareSubstr(const std::string& a, const std::string& b);

};
