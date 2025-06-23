#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Column.h"

/// \brief Represents a database table with named columns and rows.
class Table
{
    std::string name;                 ///< Name of the table.
    std::vector<Column*> columns;     ///< Vector of pointers to columns in the table.

    /// \brief method for deep copying dynamically allocated memory.
    void copyDynamic(const Table& other);

    /// \brief method for deallocating dynamic memory.
    void freeDynamic();

public:
    /// \brief Default constructor.
    Table() = default;

    /// \brief Constructs a table with a given name.
    /// \param name Name of the table.
    Table(const std::string& name);

    /// \brief Destructor to clean up dynamic memory.
    ~Table();

    /// \brief Copy constructor.
    Table(const Table& other);

    /// \brief Copy assignment operator.
    Table& operator=(const Table& other);

    /// \brief Returns the name of the table.
    /// \return A constant reference to the table's name.
    const std::string& getName() const;

    /// \brief Returns all columns of the table.
    /// \return A constant reference to the vector of column pointers.
    const std::vector<Column*>& getColumns() const;

    /// \brief Adds a new column to the table.
    /// \param columnName The name of the new column.
    /// \param columnType The type of the column ("int", "double", "string", "date").
    void addColumn(const std::string& columnName, const std::string& columnType);

    /// \brief Inserts a new row with values into the table.
    /// \param values A vector of string values to insert, matching the column types.
    void insertRow(const std::vector<std::string>& values);

    /// \brief Deletes rows where the value in a specific column matches.
    /// \param colIndex Index of the column to match.
    /// \param value Value to match exactly.
    void deleteRows(size_t colIndex, const std::string& value);

    /// \brief Updates a target column value in rows where another column matches a value.
    /// \param colIndex Column index to search.
    /// \param value Value to search for.
    /// \param targetCol Column index to update.
    /// \param newVal New value to set.
    void update(size_t colIndex, const std::string& value, size_t targetCol, const std::string& newVal);

    /// \brief Selects all rows where a column matches a specific value.
    /// \param colIndex Column index to filter by.
    /// \param value Value to match.
    /// \return A new Table containing the filtered rows.
    Table select(size_t colIndex, const std::string& value) const;

    /// \brief Changes the type of a column.
    /// \param colIndex Index of the column to modify.
    /// \param value New type to convert the column to.
    void modifyColumnType(size_t colIndex, const std::string& value);

    /// \brief Prints the table with optional pagination.
    /// \param rowsPerPage Number of rows per page. If 0, prints all rows at once.
    void printPaginated(size_t rowsPerPage = 0) const;

    /// \brief Prints column names and types of the table.
    void describe() const;

    /// \brief Serializes the table into an output stream.
    /// \param out The output stream to write to.
    void exportTo(std::ostream& out) const;

    /// \brief Reads a table from an input stream.
    /// \param in Input stream containing serialized table data.
    void deserialize(std::istream& in);

    /// \brief Returns the number of rows in the table.
    /// \return Number of rows (based on size of first column).
    size_t getRowCount() const;
};

