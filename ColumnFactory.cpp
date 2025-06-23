#include "ColumnFactory.h"
#include "IntColumn.h"
#include "DoubleColumn.h"
#include "StringColumn.h"
#include "DateColumn.h"
#include "Parser.h"


Column* ColumnFactory::createColumn(const std::string& type, const std::string& name) 
{
    if (Parser::toLower(type) == "int") 
    {
        return new IntColumn(name);
    }
    else if (Parser::toLower(type) == "double") 
    {
        return new DoubleColumn(name);
    }
    else if (Parser::toLower(type) == "string") 
    {
        return new StringColumn(name);
    }
    else if (Parser::toLower(type) == "date") 
    {
        return new DateColumn(name);
    }
    else 
    {
        return nullptr; 
    }
}
