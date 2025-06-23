#include "ShowTablesCommand.h"
#include <iostream>

void ShowTablesCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 1)
    {
        std::cout << "Usage: showtables\n";
        return;
    }

    const auto& tables = db.getTables();
    if (tables.empty()) 
    {
        std::cout << "No tables available.\n";
        return;
    }

    std::cout << "Tables:\n";
    for (const auto& table : tables)
    {
        std::cout << " - " << table->getName() << '\n';
    }
}
