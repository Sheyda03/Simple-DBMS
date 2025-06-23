#pragma once
#include "Command.h"

/// \brief Help command class
class HelpCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};


