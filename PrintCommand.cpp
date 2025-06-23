#include "PrintCommand.h"
#include <iostream>
#include "Table.h"

void PrintCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() == 1 || args.size() > 3)
    {
        std::cout << "Usage: print <table> [rows_per_page]\n";
        return;
    }

    Table* table = db.getTable(args[1]);
    if (!table) 
    {
        std::cout << "Table \"" << args[1] << "\" not found.\n";
        return;
    }

    if (args.size() == 3) 
    {
        try {
            size_t rowsPerPage = std::stoul(args[2]);
            table->printPaginated(rowsPerPage);
        }
        catch (...) {
            std::cout << "Invalid number of rows per page.\n";
        }
    }
    else 
    {
       table->printPaginated();        
    }
}
