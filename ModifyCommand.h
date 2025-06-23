#pragma once
#include "Command.h"

/// \brief Modify command class
class ModifyCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
