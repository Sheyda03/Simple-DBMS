#pragma once
#include "Command.h"
#include <vector>
#include <string>

/// \brief Class responsible for executing commands in the database system.

class Invoker
{
public:
    /// \brief Default constructor.
    Invoker();

    /// \brief Deleted copy constructor to prevent copying.
    Invoker(const Invoker&) = delete;

    /// \brief Deleted assignment operator to prevent copying.
    Invoker& operator = (const Invoker&) = delete;

    /// \brief Destructor that cleans up current command.
    ~Invoker();

    /// \brief Executes a command based on parsed arguments.
    ///
    /// The first element in the `args` vector is expected to be the command name.
    /// Remaining elements are passed as parameters to the corresponding command.
    /// \param db Reference to the `Database` object on which the command operates.
    /// \param args A vector of strings containing the command name and its arguments.
    void executeCommand(Database& db, const std::vector<std::string>& args);

private:
    Command* currentCommand; ///< Pointer to the currently executing command.
};