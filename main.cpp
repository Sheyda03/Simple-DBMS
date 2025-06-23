#include "CommandParser.h"
#include <iostream>
#include <memory>

int main() {
    try {
        Database db;
        CommandParser parser(db);
        parser.run();
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    catch (...) {
        std::cerr << "Unknown fatal error occurred" << std::endl;
        return 1;
    }
    return 0;
} 