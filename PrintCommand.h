#pragma once
#include "Command.h"

/// \brief Print command class
class PrintCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
