#pragma once
#include <string>
#include <vector>

/// \brief Abstract base class representing a column in a table.
///
/// This class serves as a common interface for all specific column types
/// such as integer, double, string, and date columns.
/// All data-related operations for a column are defined as pure virtual
/// methods and must be implemented by derived classes.
class Column
{
public:
    /// \brief Constructs a Column with the specified name.
    /// \param name The name of the column.
    Column(const std::string& name);

    /// \brief Gets the name of the column.
    /// \return The name of the column.
    const std::string& getName() const;

    /// \brief Sets a new name for the column.
    /// \param newName The new name to be assigned to the column.
    void setName(const std::string& newName);

    /// \brief Gets the type name of the column (e.g., "Integer", "String").
    /// \return The name of the column type as a string.
    virtual std::string getTypeName() const = 0;

    /// \brief Adds an empty (NULL) value to the column.
    virtual void addEmpty() = 0;

    /// \brief Adds a specific value to the column.
    /// \param value The string representation of the value to add.
    virtual void addValue(const std::string& value) = 0;

    /// \brief Sets the value at a specific row index.
    /// \param index The row index.
    /// \param value The new value to assign at the given index.
    virtual void setValueAt(size_t index, const std::string& value) = 0;

    /// \brief Gets the value at a specific row index.
    /// \param index The row index.
    /// \return The string representation of the value.
    virtual std::string getValueAt(size_t index) const = 0;

    /// \brief Compares the value at a given index with another value.
    /// \param index The row index.
    /// \param value The value to compare with.
    /// \return True if the values match according to column rules, false otherwise.
    virtual bool compare(size_t index, const std::string& value) const = 0;

    /// \brief Updates the value at a specific row.
    /// \param index The row index.
    /// \param value The new value to update.
    virtual void updateValue(size_t index, const std::string& value) = 0;

    /// \brief Removes the value at a specific row.
    /// \param index The row index to remove.
    virtual void removeRow(size_t index) = 0;

    /// \brief Serializes the column contents to an output stream.
    /// \param out The output stream to write to.
    virtual void serialize(std::ostream& out) const = 0;

    /// \brief Deserializes the column contents from an input stream.
    /// \param in The input stream to read from.
    /// \param rowsCount Number of rows expected to read.
    virtual void deserialize(std::istream& in, size_t rowsCount) = 0;

    /// \brief Gets the number of rows currently in the column.
    /// \return The number of rows (entries) in the column.
    virtual size_t size() const = 0;

    /// \brief Creates a deep copy of the column.
    /// \return A pointer to a new Column object that is a clone of the current one.
    virtual Column* clone() const = 0;

    /// \brief Virtual destructor to allow proper cleanup of derived classes.
    virtual ~Column() = default;

private:
    std::string name; ///< The name of the column.
};
