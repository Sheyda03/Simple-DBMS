#include "ExportCommand.h"
#include "Table.h"
#include <iostream>
#include <fstream>

void ExportCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 3) 
    {
        std::cout << "Usage: export <table> <filename>\n";
        return;
    }

    Table* table = db.getTable(args[1]);
    if (!table) 
    {
        std::cout << "Table \"" << args[1] << "\" not found.\n";
        return;
    }

    std::ofstream out(args[2]);
    if (!out.is_open()) 
    {
        std::cout << "Could not open file " << args[2] << " for writing.\n";
        return;
    }

    table->exportTo(out);
    std::cout << "Table \"" << args[1] << "\" exported to " << args[2] << ".\n";
}
