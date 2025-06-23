// Invoker.cpp
#include "Invoker.h"
#include "CommandFactory.h"

Invoker::Invoker() : currentCommand(nullptr) {}

Invoker::~Invoker() 
{
    delete currentCommand;
}

void Invoker::executeCommand(Database& db, const std::vector<std::string>& args) 
{
    if (args.empty()) 
    {
        std::cout << "No command entered.\n";
        return;
    }

    Command* command = CommandFactory::createCommand(args[0]);

    if (!command) 
    {
        std::cout << "Unknown command: '" << args[0] << "'. Please try again.\n";
        return;
    }

    delete currentCommand;
    currentCommand = command;

    if (currentCommand)
    {
        currentCommand->execute(db, args);
    }
}

