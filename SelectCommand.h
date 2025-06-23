#pragma once
#include "Command.h"

/// \brief Select command class
class SelectCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
