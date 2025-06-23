#pragma once
#include "Command.h"

/// \brief AddTable command class
class AddTableCommand : public Command
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};

