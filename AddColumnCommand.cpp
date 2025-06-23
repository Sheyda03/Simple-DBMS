#include "AddColumnCommand.h"
#include <iostream>
#include "Table.h"

void AddColumnCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 4) 
    {
        std::cout << "Usage: addcolumn <table name> <column name> <column type>\n";
        return;
    }

    Table* table = db.getTable(args[1]);
    if (!table) 
    {
        std::cout << "Table \"" << args[1] << "\" not found.\n";
        return;
    }

    table->addColumn(args[2], args[3]); 
}
