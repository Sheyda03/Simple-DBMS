#include "SaveCommand.h"
#include <iostream>

void SaveCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 1) 
    {
        std::cout << "Usage: save\n";
        return;
    }

    if (!db.isOpened()) 
    {
        std::cout << "No database is currently open.\n";
        return;
    }

    if (db.save()) 
    {
        std::cout << "Database saved.\n";
    }
    else 
    {
        std::cout << "Failed to save database.\n";
    }
}