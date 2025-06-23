#pragma once
#include <vector>
#include <string>
#include "Database.h"

/// \brief Abstract base class representing a database command.
///
/// This class defines the interface that all concrete command classes must implement. 
/// Each command performs an operation on the given Database instance.
class Command
{
public:
    /// \brief Executes the command using the provided database and arguments.
    ///
    /// This is a pure virtual method that must be implemented by all subclasses.
    /// \param db Reference to the database on which the command will operate.
    /// \param args List of arguments passed to the command, parsed from user input.
    virtual void execute(Database& db, const std::vector<std::string>& args) = 0;

    /// \brief Virtual destructor to ensure proper cleanup of derived classes.
    virtual ~Command() = default;
};
