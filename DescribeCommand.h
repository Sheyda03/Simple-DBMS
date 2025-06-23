#pragma once
#include "Command.h"

/// \brief Describe command class
class DescribeCommand : public Command 
{
public:
    void execute(Database& db, const std::vector<std::string>& args) override;
};
