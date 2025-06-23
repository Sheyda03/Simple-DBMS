#pragma once

#include <string>
#include <vector>
#include "Command.h"

/// \brief Factory class responsible for creating command objects.
class CommandFactory
{
public:
    /// \brief Creates a command object based on the command name.
    ///
    /// This static method returns a pointer to a new Command object
    /// that matches the given name. If the command is unknown, it
    /// returns a nullptr.
    /// 
    /// \param name The name of the command.
    /// \return A pointer to a dynamically allocated Command object, or nullptr if the name is unrecognized.
    static Command* createCommand(const std::string& name);
};

