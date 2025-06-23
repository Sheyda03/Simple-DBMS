#include "ModifyCommand.h"
#include <iostream>
#include "Table.h"

void ModifyCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 4) 
    {
        std::cout << "Usage: modify <table name> <column-n> <new type>\n";
        return;
    }

    Table* table = db.getTable(args[1]);
    if (!table) 
    {
        std::cout << "Table \"" << args[1] << "\" not found.\n";
        return;
    }

    size_t colIndex;
    try {
        colIndex = std::stoul(args[2]);
    }
    catch (...) {
        std::cout << "Invalid column index.\n";
        return;
    }

    table->modifyColumnType(colIndex, args[3]); 
}
