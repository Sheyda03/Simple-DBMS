#include "HelpCommand.h"
#include <iostream>

void HelpCommand::execute(Database&, const std::vector<std::string>&) 
{
    std::cout << "Available commands:\n"
        << "  open <file>\n"
        << "  close\n"
        << "  save\n"
        << "  saveas <file>\n"
        << "  help\n"
        << "  exit\n"
        << "  showtables\n"
        << "  describe <table>\n"
        << "  print <table> [rowsPerPage]\n"
        << "  export <table> <file>\n"
        << "  select <column> <value> <table>\n"
        << "  modify <table> <column> <new type>\n"
        << "  addcolumn <table> <name> <type>\n"
        << "  addtable <table name>\n"
        << "  update <table> <searchCol> <searchVal> <targetCol> <targetVal>\n"
        << "  delete <table> <searchCol> <value>\n"
        << "  insert <table> <val1> ... <valN>\n";
}
