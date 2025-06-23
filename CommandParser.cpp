#include "CommandParser.h"
#include <sstream>
#include <algorithm>
#include <iomanip>

CommandParser::CommandParser(Database& database) : db(database), running(true) {
    // Initialize command map
    commands["showtables"] = [this](const std::vector<std::string>&) { handleShowTables(); };
    commands["describe"] = [this](const std::vector<std::string>& args) { handleDescribe(args); };
    commands["print"] = [this](const std::vector<std::string>& args) { handlePrint(args); };
    commands["export"] = [this](const std::vector<std::string>& args) { handleExport(args); };
    commands["select"] = [this](const std::vector<std::string>& args) { handleSelect(args); };
    commands["modify"] = [this](const std::vector<std::string>& args) { handleModify(args); };
    commands["addcolumn"] = [this](const std::vector<std::string>& args) { handleAddColumn(args); };
    commands["update"] = [this](const std::vector<std::string>& args) { handleUpdate(args); };
    commands["delete"] = [this](const std::vector<std::string>& args) { handleDelete(args); };
    commands["insert"] = [this](const std::vector<std::string>& args) { handleInsert(args); };
    commands["open"] = [this](const std::vector<std::string>& args) { handleOpen(args); };
    commands["save"] = [this](const std::vector<std::string>&) { handleSave(); };
    commands["saveas"] = [this](const std::vector<std::string>& args) { handleSaveAs(args); };
    commands["close"] = [this](const std::vector<std::string>&) { handleClose(); };
    commands["help"] = [this](const std::vector<std::string>&) { handleHelp(); };
    commands["exit"] = [this](const std::vector<std::string>&) { handleExit(); };
}

void CommandParser::run() {
    std::string input;
    std::cout << "Database Management System\n";
    std::cout << "Type 'help' for available commands\n\n";

    while (running) {
        std::cout << "> ";
        std::getline(std::cin, input);

        if (input.empty()) continue;

        auto tokens = tokenize(input);
        if (tokens.empty()) continue;

        std::string command = tokens[0];
        std::transform(command.begin(), command.end(), command.begin(), ::tolower);

        auto it = commands.find(command);
        if (it != commands.end()) {
            try {
                it->second(tokens);
            }
            catch (const std::exception& e) {
                printError(e.what());
            }
        }
        else {
            printError("Unknown command: " + command);
        }
    }
}

std::vector<std::string> CommandParser::tokenize(const std::string& input) {
    std::vector<std::string> tokens;
    std::stringstream ss(input);
    std::string token;

    while (ss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

void CommandParser::printError(const std::string& message) {
    std::cerr << "Error: " << message << std::endl;
}

void CommandParser::printSuccess(const std::string& message) {
    std::cout << "Success: " << message << std::endl;
}

bool CommandParser::validateArguments(const std::vector<std::string>& args, size_t expectedCount) {
    if (args.size() != expectedCount) {
        printError("Invalid number of arguments. Expected " + std::to_string(expectedCount - 1) + 
                  ", got " + std::to_string(args.size() - 1));
        return false;
    }
    return true;
}

void CommandParser::handleShowTables() {
    db.showTables();
}

void CommandParser::handleDescribe(const std::vector<std::string>& args) {
    if (!validateArguments(args, 2)) return;
    db.describeTable(args[1]);
}

void CommandParser::handlePrint(const std::vector<std::string>& args) {
    if (args.size() < 2 || args.size() > 3) {
        printError("Invalid number of arguments. Expected 1 or 2 arguments");
        return;
    }
    
    size_t rowsPerPage = 0;
    if (args.size() == 3) {
        try {
            rowsPerPage = std::stoul(args[2]);
        }
        catch (...) {
            printError("Invalid rows per page value");
            return;
        }
    }
    
    db.printTable(args[1], rowsPerPage);
}

void CommandParser::handleExport(const std::vector<std::string>& args) {
    if (!validateArguments(args, 3)) return;
    db.exportTable(args[1], args[2]);
}

void CommandParser::handleSelect(const std::vector<std::string>& args) {
    if (!validateArguments(args, 4)) return;
    
    try {
        size_t columnIndex = std::stoul(args[1]);
        db.select(args[3], columnIndex, args[2]);
    }
    catch (...) {
        printError("Invalid column index");
    }
}

void CommandParser::handleModify(const std::vector<std::string>& args) {
    if (!validateArguments(args, 4)) return;
    
    try {
        size_t columnIndex = std::stoul(args[2]);
        db.modifyColumn(args[1], columnIndex, args[3]);
    }
    catch (...) {
        printError("Invalid column index");
    }
}

void CommandParser::handleAddColumn(const std::vector<std::string>& args) {
    if (!validateArguments(args, 4)) return;
    db.addColumn(args[1], args[2], args[3]);
}

void CommandParser::handleUpdate(const std::vector<std::string>& args) {
    if (!validateArguments(args, 6)) return;
    
    try {
        size_t searchColumnIndex = std::stoul(args[2]);
        size_t targetColumnIndex = std::stoul(args[4]);
        db.update(args[1], searchColumnIndex, args[3], targetColumnIndex, args[5]);
    }
    catch (...) {
        printError("Invalid column index");
    }
}

void CommandParser::handleDelete(const std::vector<std::string>& args) {
    if (!validateArguments(args, 4)) return;
    
    try {
        size_t columnIndex = std::stoul(args[2]);
        db.deleteRows(args[1], columnIndex, args[3]);
    }
    catch (...) {
        printError("Invalid column index");
    }
}

void CommandParser::handleInsert(const std::vector<std::string>& args) {
    if (args.size() < 3) {
        printError("Invalid number of arguments. Expected at least 2 arguments");
        return;
    }
    
    std::vector<std::string> values(args.begin() + 2, args.end());
    db.insert(args[1], values);
}

void CommandParser::handleOpen(const std::vector<std::string>& args) {
    if (!validateArguments(args, 2)) return;
    db.open(args[1]);
}

void CommandParser::handleSave() {
    db.save();
}

void CommandParser::handleSaveAs(const std::vector<std::string>& args) {
    if (!validateArguments(args, 2)) return;
    db.saveAs(args[1]);
}

void CommandParser::handleClose() {
    db.close();
}

void CommandParser::handleHelp() {
    std::cout << "Available commands:\n"
              << "  showtables - Show all tables in the database\n"
              << "  describe <table> - Show table structure\n"
              << "  print <table> [rows_per_page] - Print table contents\n"
              << "  export <table> <filename> - Export table to file\n"
              << "  select <column_n> <value> <table> - Select rows matching value\n"
              << "  modify <table> <column_n> <new_type> - Modify column type\n"
              << "  addcolumn <table> <column_name> <column_type> - Add new column\n"
              << "  update <table> <search_column_n> <search_value> <target_column_n> <target_value> - Update rows\n"
              << "  delete <table> <column_n> <value> - Delete matching rows\n"
              << "  insert <table> <value1> [value2 ...] - Insert new row\n"
              << "  open <filename> - Open database file\n"
              << "  save - Save database\n"
              << "  saveas <filename> - Save database as\n"
              << "  close - Close database\n"
              << "  help - Show this help\n"
              << "  exit - Exit program\n";
}

void CommandParser::handleExit() {
    if (db.isDirty()) {
        std::cout << "Database has unsaved changes. Save before exit? (y/n): ";
        std::string response;
        std::getline(std::cin, response);
        if (response == "y" || response == "Y") {
            db.save();
        }
    }
    running = false;
} 