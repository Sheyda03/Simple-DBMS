#pragma once

#include <vector>
#include <string>
#include <fstream>
#include "Table.h"

/// \brief Class representing a simple database containing multiple tables.
class Database
{
public:
    /// \brief Default constructor.
    Database() = default;

    /// \brief Copy constructor.
    /// \param other Another Database object to copy from.
    Database(const Database& other);

    /// \brief Copy assignment operator.
    /// \param other Another Database object to assign from.
    /// \return Reference to the current object.
    Database& operator=(const Database& other);

    /// \brief Destructor. Cleans up all dynamically allocated tables.
    ~Database();

    /// \brief Opens and loads a database from a file.
    /// \param fileName The name of the file to open.
    /// \return True on success, false on failure.
    bool open(const std::string& fileName);

    /// \brief Saves the database to its currently opened file.
    /// \return True if saving was successful, false otherwise.
    bool save() const;

    /// \brief Saves the database to a new file.
    /// \param newFileName The name of the new file.
    /// \return True if successful, false otherwise.
    bool saveAs(const std::string& newFileName);

    /// \brief Closes the current database, freeing resources.
    void close();

    /// \brief Adds a new empty table to the database.
    /// \param name Name of the new table.
    void addTable(const std::string& name);

    /// \brief Checks if a table with the given name exists.
    /// \param name Name of the table to check.
    /// \return True if the table exists, false otherwise.
    bool hasTable(const std::string& name) const;

    /// \brief Gets a pointer to a table by name.
    /// \param name Name of the table to get.
    /// \return Pointer to the Table, or nullptr if not found.
    Table* getTable(const std::string& name);

    /// \brief Gets a const reference to all tables.
    /// \return Const reference to the internal vector of table pointers.
    const std::vector<Table*>& getTables() const;

    /// \brief Checks if a database file is currently opened.
    /// \return True if a file is opened, false otherwise.
    bool isOpened() const;

    /// \brief Gets the filename of the currently opened database.
    /// \return Const reference to the filename string.
    const std::string& getFilename() const;

private:
    std::vector<Table*> tables; ///< Vector of all tables in the database.
    std::string filename;       ///< Name of the currently opened file.
    bool isOpen = false;        ///< Flag indicating if a file is currently opened.

    /// \brief Frees all dynamically allocated memory for tables.
    void freeDynamic();

    /// \brief Copies dynamic content from another database object.
    /// \param other The database to copy from.
    void copyDynamic(const Database& other);
};

