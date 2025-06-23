#pragma once
#include "Command.h"

/// \brief Update command class
class UpdateCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
