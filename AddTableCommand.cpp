// AddTableCommand.h
#pragma once
#include <iostream>
#include "AddTableCommand.h"

void AddTableCommand::execute(Database& db, const std::vector<std::string>& args)
{
    if (args.size() < 2) 
    {
        std::cout << "Usage: addtable <table name>\n";
        return;
    }

    const std::string& tableName = args[1];
    if (db.hasTable(tableName)) 
    {
        std::cout << "Table '" << tableName << "' already exists.\n";
        return;
    }

    db.addTable(tableName);
    std::cout << "Table '" << tableName << "' created successfully.\n";
}

