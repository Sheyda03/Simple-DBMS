#include "InsertCommand.h"
#include <iostream>
#include "Table.h"

void InsertCommand::execute(Database& db, const std::vector<std::string>& args) 
{
    if (args.size() < 3) 
    {
        std::cout << "Usage: insert <table name> <value1> ... <valueN>\n";
        return;
    }

    Table* table = db.getTable(args[1]);
    if (!table) 
    {
        std::cout << "Table \"" << args[1] << "\" not found.\n";
        return;
    }

    std::vector<std::string> values(args.begin() + 2, args.end());
    table->insertRow(values); 
}
