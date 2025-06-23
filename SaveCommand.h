#pragma once
#include "Command.h"

/// \brief Save command class
class SaveCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
