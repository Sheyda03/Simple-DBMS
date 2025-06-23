#pragma once
#include "Command.h"

/// \brief ShowTables command class
class ShowTablesCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
