#include "ExitCommand.h"
#include <iostream>

void ExitCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 1) 
    {
        std::cout << "Usage: exit\n";
        return;
    }

    if (db.isOpened()) 
    {
        std::cout << "There is an open database. Closing before exit...\n";
        db.close();
    }

    std::cout << "Exiting application.\n";
    std::exit(0); 
}
