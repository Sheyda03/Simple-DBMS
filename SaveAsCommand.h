#pragma once
#include "Command.h"

/// \brief SaveAs command class
class SaveAsCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
