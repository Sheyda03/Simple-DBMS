#pragma once
#include "Command.h"
#include "Database.h"

/// \brief Open command class
class OpenCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};

