#pragma once
#include "Database.h"
#include <string>
#include <vector>
#include <functional>
#include <unordered_map>

class CommandParser {
private:
    Database& db;
    bool running;
    
    // Command handlers
    void handleShowTables();
    void handleDescribe(const std::vector<std::string>& args);
    void handlePrint(const std::vector<std::string>& args);
    void handleExport(const std::vector<std::string>& args);
    void handleSelect(const std::vector<std::string>& args);
    void handleModify(const std::vector<std::string>& args);
    void handleAddColumn(const std::vector<std::string>& args);
    void handleUpdate(const std::vector<std::string>& args);
    void handleDelete(const std::vector<std::string>& args);
    void handleInsert(const std::vector<std::string>& args);
    void handleOpen(const std::vector<std::string>& args);
    void handleSave();
    void handleSaveAs(const std::vector<std::string>& args);
    void handleClose();
    void handleHelp();
    void handleExit();

    // Helper methods
    std::vector<std::string> tokenize(const std::string& input);
    void printError(const std::string& message);
    void printSuccess(const std::string& message);
    bool validateArguments(const std::vector<std::string>& args, size_t expectedCount);

    // Command map
    using CommandHandler = std::function<void(const std::vector<std::string>&)>;
    std::unordered_map<std::string, CommandHandler> commands;

public:
    explicit CommandParser(Database& database);
    void run();
    void stop() { running = false; }
}; 