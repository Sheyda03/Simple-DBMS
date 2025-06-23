#include "DescribeCommand.h"
#include "Table.h"
#include <iostream>

void DescribeCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() != 2) 
    {
        std::cout << "Usage: describe <table>\n";
        return;
    }

    Table* table = db.getTable(args[1]);
    if (!table) 
    {
        std::cout << "Table \"" << args[1] << "\" not found.\n";
        return;
    }

    table->describe();
}
