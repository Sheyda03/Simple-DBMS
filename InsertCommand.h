#pragma once
#include "Command.h"

/// \brief Insert command class
class InsertCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
