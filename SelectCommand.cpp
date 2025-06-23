#include "SelectCommand.h"
#include "Table.h"
#include <iostream>

void SelectCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 4) 
    {
        std::cout << "Usage: select <column-n> <value> <table name>\n";
        return;
    }

    size_t columnIndex;
    try 
    {
        columnIndex = std::stoul(args[1]);
    }
    catch (...) 
    {
        std::cout << "Invalid column index.\n";
        return;
    }

    const std::string& value = args[2];
    const std::string& tableName = args[3];

    Table* table = db.getTable(tableName);
    if (!table) 
    {
        std::cout << "Table \"" << tableName << "\" not found.\n";
        return;
    }

    Table selected = table->select(columnIndex, value);
    size_t rowsPerPage;
    std::cout << "How many rows do you want in one page? (Input 0 for non-paginating...): ";
    std::cin >> rowsPerPage;

    
    selected.printPaginated(rowsPerPage);
}
