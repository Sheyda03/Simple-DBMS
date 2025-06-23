#include "UpdateCommand.h"
#include <iostream>
#include "Table.h"

void UpdateCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 6) 
    {
        std::cout << "Usage: update <table name> <search column n> <search value> <target column n> <target value>\n";
        return;
    }

    Table* table = db.getTable(args[1]);
    if (!table) 
    {
        std::cout << "Table \"" << args[1] << "\" not found.\n";
        return;
    }

    size_t searchCol, targetCol;
    try {
        searchCol = std::stoul(args[2]);
        targetCol = std::stoul(args[4]);
    }
    catch (...) {
        std::cout << "Invalid column index.\n";
        return;
    }

    table->update(searchCol, args[3], targetCol, args[5]);
}
