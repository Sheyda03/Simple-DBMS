#include "Database.h"
#include <iostream>

void Database::freeDynamic() 
{
    for (Table* table : tables)
    {
        delete table;
    }
    tables.clear();
}

void Database::copyDynamic(const Database& other) 
{   
    for (const Table* t : other.tables)
    {
        tables.push_back(new Table(*t));
    }
}

Database::Database(const Database& other) 
{
    copyDynamic(other);
    filename = other.filename;
    isOpen = other.isOpen;
}

Database& Database::operator=(const Database& other) 
{
    if (this != &other) 
    {
        freeDynamic();
        copyDynamic(other);
        filename = other.filename;
        isOpen = other.isOpen;
    }
    return *this;
}

Database::~Database() 
{
    freeDynamic();
}

bool Database::open(const std::string& fileName) 
{
    std::ifstream in(fileName);
        
    if (!in.is_open()) 
    {
        std::cout << "You have not such a file. Do you want to create a file with name (Y/N)" << fileName << std::endl;
        char answer;
        std::cin >> answer;
        if (answer == 'Y')
        {
            std::ofstream out(fileName);
            if (!out.is_open()) 
            {
                std::cout << "Failed to create file.\n";
                return false;
            }
            
            out << "0\n";
            out.close();
            
            in.open(fileName);
            if (!in.is_open()) 
            {
                std::cout << "Failed to reopen newly created file.\n";
                return false;
            }
        }
        else 
        {
            std::cout << "Failed to create file.\n";
            return false;
        }       
    }

    freeDynamic(); 

    size_t tableCount;
    in >> tableCount;
    in.ignore();

    for (size_t i = 0; i < tableCount; ++i) 
    {
        Table* t = new Table();
        t->deserialize(in);
        tables.push_back(t);
    }

    filename = fileName;
    isOpen = true;
    
    return true;
}

bool Database::save() const 
{
    if (!isOpen) 
    {
        return false;
    }

    std::ofstream out(filename);
    if (!out.is_open()) 
    {
        return false;
    }

    out << tables.size() << "\n";
    for (const Table* table : tables)
    {
        table->exportTo(out);
    }

    return true;
}

bool Database::saveAs(const std::string& newFileName) 
{
    filename = newFileName;
    return save();
}

void Database::close() 
{
    freeDynamic();
    filename.clear();
    isOpen = false;
}

void Database::addTable(const std::string& name) 
{
    Table* table = new Table(name);
    tables.push_back(table);
}

bool Database::hasTable(const std::string& name) const 
{
    for (const auto& table : tables) 
    {
        if (table->getName() == name) 
        {
            return true;
        }
    }
    return false;
}

Table* Database::getTable(const std::string& name) 
{
    for (Table* t : tables)
    {
        if (t->getName() == name)
        {
            return t;
        }
    }
    return nullptr;
}

const std::vector<Table*>& Database::getTables() const {

    return tables;
}

bool Database::isOpened() const 
{
    return isOpen;
}

const std::string& Database::getFilename() const 
{
    return filename;
}
