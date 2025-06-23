#include "OpenCommand.h"
#include <iostream>

void OpenCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 2) 
    {
        std::cout << "Usage: open <file>\n";
        return;
    }

    if (db.isOpened()) 
    {
        std::cout << "A database is already open. Close it before opening another.\n";
        return;
    }

    if (db.open(args[1])) 
    {
        std::cout << "Database opened successfully.\n";
    }
    else 
    {
        std::cout << "Failed to open database.\n";
    }
}
