#pragma once
#include "Command.h"

/// \brief Close database command class
class CloseCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
