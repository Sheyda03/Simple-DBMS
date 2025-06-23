#include "App.h"
#include <iostream>
#include "Parser.h"

App::App() 
{
    db = new Database();
    invoker = new Invoker();
}

App::~App() 
{
    delete db;
    delete invoker;
}

void App::run()
{
    std::string line;
    std::cout << "Welcome to Simple DBMS. Type 'help' for available commands.\n";

    while (true) 
    {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) continue;

        std::vector<std::string> args;
        size_t start = 0;

        while (start < line.size()) 
        {
            while (start < line.size() && (line[start] == ' ' || line[start] == '\t' || line[start] == '\n' || line[start] == '\r')) 
            {
                ++start;
            }

            if (start >= line.size()) 
            {
                break;
            }

            size_t end = start;
            while (end < line.size() && !(line[end] == ' ' || line[end] == '\t' || line[end] == '\n' || line[end] == '\r')) 
            {
                ++end;
            }

            args.push_back(line.substr(start, end - start));
            start = end;
        }

        if (args.empty()) 
        {
            continue;
        }

        if (args[0] == "exit") 
        {
            std::cout << "Exiting...\n";
            break;
        }

        invoker->executeCommand(*db, args);
    }
}


