#pragma once
#include "Command.h"

/// \brief Exit command class
class ExitCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
