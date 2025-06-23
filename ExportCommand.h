#pragma once
#include "Command.h"

/// \brief Export command class
class ExportCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
