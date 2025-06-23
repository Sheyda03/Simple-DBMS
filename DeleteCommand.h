#pragma once
#include "Command.h"

/// \brief Delete command class
class DeleteCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
