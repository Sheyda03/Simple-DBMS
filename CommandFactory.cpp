#include "CommandFactory.h"
#include "SelectCommand.h"
#include "ModifyCommand.h"
#include "AddColumnCommand.h"
#include "UpdateCommand.h"
#include "DeleteCommand.h"
#include "InsertCommand.h"
#include "ExportCommand.h"
#include "PrintCommand.h"
#include "ShowTablesCommand.h"
#include "DescribeCommand.h"
#include "HelpCommand.h"
#include "ExitCommand.h"
#include "OpenCommand.h"
#include "CloseCommand.h"
#include "SaveCommand.h"
#include "SaveAsCommand.h"
#include "AddTableCommand.h"

Command* CommandFactory::createCommand(const std::string& name) 
{
    
    if (name == "select") return new SelectCommand();
    else if (name == "modify") return new ModifyCommand();
    else if (name == "addcolumn") return new AddColumnCommand();
    else if (name == "addtable") return new AddTableCommand();
    else if (name == "update") return new UpdateCommand();
    else if (name == "delete") return new DeleteCommand();
    else if (name == "insert") return new InsertCommand();
    else if (name == "export") return new ExportCommand();
    else if (name == "print") return new PrintCommand();
    else if (name == "showtables") return new ShowTablesCommand();
    else if (name == "describe") return new DescribeCommand();
    else if (name == "help") return new HelpCommand();
    else if (name == "exit") return new ExitCommand();
    else if (name == "open") return new OpenCommand();
    else if (name == "close") return new CloseCommand();
    else if (name == "save") return new SaveCommand();
    else if (name == "saveas") return new SaveAsCommand();

    return nullptr;
}
