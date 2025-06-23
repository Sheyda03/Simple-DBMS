#include "SaveAsCommand.h"
#include <iostream>

void SaveAsCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 2) 
    {
        std::cout << "Usage: saveas <file>\n";
        return;
    }

    if (!db.isOpened()) 
    {
        std::cout << "No database is currently open.\n";
        return;
    }

    if (db.saveAs(args[1])) 
    {
        std::cout << "Database saved to: " << args[1] << '\n';
    }
    else 
    {
        std::cout << "Failed to save database to file.\n";
    }
}
