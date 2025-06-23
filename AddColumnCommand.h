#pragma once
#include "Command.h"

/// \brief AddColumn command class
class AddColumnCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
