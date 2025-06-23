#include "CloseCommand.h"
#include <iostream>

void CloseCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 1) 
    {
        std::cout << "Usage: close\n";
        return;
    }

    if (!db.isOpened()) 
    {
        std::cout << "No database is currently open.\n";
        return;
    }

    db.close();
    std::cout << "Database closed successfully.\n";
}
