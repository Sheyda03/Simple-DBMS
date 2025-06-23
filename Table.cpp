#include "Table.h"
#include "ColumnFactory.h"

Table::Table(const std::string& name) : name(name) {}

Table::~Table() 
{
    freeDynamic();
}

Table::Table(const Table& other) 
{
    copyDynamic(other);
    name = other.name;
}

Table& Table::operator=(const Table& other) 
{
    if (this != &other) 
    {
        freeDynamic();
        copyDynamic(other);
        name = other.name;
    }
    return *this;
}

void Table::copyDynamic(const Table& other) 
{
    
    for (Column* col : other.columns) 
    {
        columns.push_back(col->clone());
    }
}

void Table::freeDynamic() 
{
    for (Column* col : columns)
    {
        delete col;
    }
    columns.clear();
}

const std::string& Table::getName() const 
{
    return name;
}

const std::vector<Column*>& Table::getColumns() const 
{
    return columns;
}


void Table::addColumn(const std::string& columnName, const std::string& columnType) 
{
    Column* column = ColumnFactory::createColumn(columnType, columnName);
    if (!column) 
    {
        std::cerr << "Invalid column type: " << columnType << std::endl;
        return;
    }

    for (size_t i = 0; i < getRowCount(); ++i) 
    {
        column->addEmpty();
    }

    columns.push_back(column);
}

void Table::printPaginated(size_t rowsPerPage) const 
{
    if (columns.empty()) 
    {
        std::cout << "Table is empty.\n";
        return;
    }

    size_t numRows = columns[0]->size(); 

    
    auto printHeader = [&]() 
        {
        for (const Column* col : columns)
        {
            std::cout << col->getName() << "\t";
        }
        std::cout << std::endl;
        };

    auto printRow = [&](size_t rowIndex) 
        {
        for (const Column* col : columns)
        {
            std::cout << col->getValueAt(rowIndex) << "\t";
        }
        std::cout << std::endl;
        };

    
    if (rowsPerPage == 0) 
    {
        printHeader();
        for (size_t i = 0; i < numRows; ++i)
        {
            printRow(i);
        }
        return;
    }

    
    size_t currentPage = 0;
    size_t totalPages = (numRows + rowsPerPage - 1) / rowsPerPage;

    while (true) 
    {
        system("cls"); 
        printHeader();

        size_t start = currentPage * rowsPerPage;
        size_t end = std::min(start + rowsPerPage, numRows);

        for (size_t i = start; i < end; ++i)
        {
            printRow(i);
        }

        std::cout << "\nPage " << (currentPage + 1) << " : " << totalPages << "\n";
        std::cout << "Commands: first page | next page | previous page | last page | exit\n> ";

        std::string cmd;
        std::getline(std::cin, cmd);

        if (cmd == "exit") break;
        else if (cmd == "first page") currentPage = 0;
        else if (cmd == "next page" && currentPage + 1 < totalPages) ++currentPage;
        else if (cmd == "previous page" && currentPage > 0) --currentPage;
        else if (cmd == "last page") currentPage = totalPages - 1;
    }
}


size_t Table::getRowCount() const 
{
    return columns.empty() ? 0 : columns[0]->size();
}

void Table::insertRow(const std::vector<std::string>& values) 
{
    if (values.size() > columns.size()) 
    {
        std::cout << "Too many values provided.\n";
        return;
    }

    for (size_t i = 0; i < columns.size(); ++i) 
    {
        if (i < values.size()) 
        {
            try
            {
                columns[i]->addValue(values[i]);
            }
            catch (...)
            {
                std::cout << "Invalid date! Try again...";
            }            
        }
        else 
        {
            columns[i]->addEmpty();  
        }
    }
}

void Table::deleteRows(size_t colIndex, const std::string& value) 
{
    if (colIndex >= columns.size()) 
    {
        return;
    }

    for (int i = static_cast<int>(getRowCount()) - 1; i >= 0; --i) 
    {
        if (columns[colIndex]->compare(i, value)) 
        {
            for (Column* col : columns)
            {
                col->removeRow(i);
            }
        }
    }
}

void Table::update(size_t colIndex, const std::string& value, size_t targetCol, const std::string& newVal) 
{
    if (colIndex >= columns.size() || targetCol >= columns.size()) 
    {
        return;
    }

    for (size_t i = 0; i < getRowCount(); ++i) 
    {
        if (columns[colIndex]->compare(i, value)) 
        {
            try {
                columns[targetCol]->updateValue(i, newVal);
            }
            catch (const std::exception& ex) {
                std::cout << "Failed to update row " << i << ": " << ex.what() << "\n";
            }
        }
    }
}

void Table::describe() const 
{
    for (const auto& col : columns)
    {
        std::cout << col->getName() << " : " << col->getTypeName() << "\n";
    }
}

void Table::exportTo(std::ostream& out) const
{
    out << name << "\n";
    out << columns.size() << " " << getRowCount() << "\n";        

    for (Column* col : columns)
    {
        col->serialize(out);
    }
}

void Table::deserialize(std::istream& in) 
{
    freeDynamic();

    std::getline(in, name);
    size_t colCount, rowCount;
    in >> colCount >> rowCount;
    in.ignore();

    for (size_t i = 0; i < colCount; ++i) 
    {
        
        std::string columnName;
        std::getline(in, columnName);

        std::string typeName;
        std::getline(in, typeName);
        Column* col = ColumnFactory::createColumn(typeName, columnName);
        col->deserialize(in, rowCount);
        columns.push_back(col);
    }
}
Table Table::select(size_t colIndex, const std::string& value) const 
{
    Table result(name + "_selection");

    for (Column* col : columns) 
    {
        result.addColumn(col->getName(), col->getTypeName());
    }

    for (size_t i = 0; i < getRowCount(); ++i) 
    {
        if (columns[colIndex]->compare(i, value)) 
        {
            for (size_t j = 0; j < columns.size(); ++j) 
            {
                result.columns[j]->addValue(columns[j]->getValueAt(i));
            }
        }
    }

    return result;
}

void Table::modifyColumnType(size_t columnIndex, const std::string& newType) 
{
    if (columnIndex >= columns.size()) 
    {
        std::cout << "Invalid column index.\n";
        return;
    }

    Column* oldCol = columns[columnIndex];
    Column* newCol = ColumnFactory::createColumn(newType, oldCol->getName());

    if (!newCol) 
    {
        std::cout << "Invalid type: " << newType << std::endl;
        return;
    }

    size_t success = 0, fail = 0;
    for (size_t i = 0; i < oldCol->size(); ++i) 
    {
        std::string value = oldCol->getValueAt(i);
        if (value == "NULL" || value.empty()) 
        {
            newCol->addValue("NULL"); 
            continue;
        }

        try {
            newCol->addValue(value);
            ++success;
        }
        catch (...) {
            newCol->addValue("NULL");
            ++fail;
        }
    }

    delete columns[columnIndex];
    columns[columnIndex] = newCol;

    std::cout << "Success: " << success << ", Unsuccess: " << fail << std::endl;
}

