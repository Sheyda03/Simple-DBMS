#include "IntColumn.h"
#include "Parser.h"
#include <stdexcept>
#include <iostream>

IntColumn::IntColumn(const std::string& name)
    : Column(name) {}

std::string IntColumn::getTypeName() const 
{
    return "INT";
}

Column* IntColumn::clone() const 
{
    IntColumn* newCol = new IntColumn(getName());
    newCol->data = data;
    return newCol;
}

void IntColumn::addEmpty() 
{
    data.push_back({ 0, false });
}

void IntColumn::addValue(const std::string& value) 
{
    if (value == "NULL") 
    {
        addEmpty();
        return;
    }

    int parsed;
    if (!Parser::tryParseInt(value, parsed)) 
    {
        throw std::invalid_argument("Invalid integer format: " + value);
    }

    data.push_back({ parsed, true });
}

void IntColumn::setValueAt(size_t index, const std::string& value) 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Index out of range in setValueAt");
    }

    if (value == "NULL") 
    {
        data[index] = { 0, false };
        return;
    }

    int parsed;
    if (!Parser::tryParseInt(value, parsed)) 
    {
        throw std::invalid_argument("Invalid integer format: " + value);
    }

    data[index] = { parsed, true };
}

std::string IntColumn::getValueAt(size_t index) const 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Index out of range in getValueAt");
    }

    if (!data[index].second) 
    {
        return "NULL";
    }

    return std::to_string(data[index].first);
}

bool IntColumn::compare(size_t index, const std::string& value) const 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Index out of range in compare");
    }

    if (!data[index].second) 
    {
        return false;
    }

    int parsed;
    if (!Parser::tryParseInt(value, parsed)) 
    {
        return false;
    }

    return data[index].first == parsed;
}

void IntColumn::updateValue(size_t index, const std::string& value) 
{
    setValueAt(index, value);
}

void IntColumn::removeRow(size_t index) 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Index out of range in removeRow");
    }
    data.erase(data.begin() + index);
}
size_t IntColumn::size() const 
{
    return data.size();
}
void IntColumn::serialize(std::ostream& out) const 
{
    out << getName() << "\n" << getTypeName() << "\n";
    for (const auto& entry : data) 
    {
        if (entry.second) 
        {
            out << entry.first << "\n";
        }
        else 
        {
            out << "NULL\n";
        }
    }
}

void IntColumn::deserialize(std::istream& in, size_t rowsCount) 
{
    data.clear();
    std::string line;

    for (size_t i = 0; i < rowsCount; ++i) 
    {
        if (!std::getline(in, line)) 
        {
            throw std::runtime_error("Failed to read line during deserialize");
        }

        if (line == "NULL") 
        {
            data.push_back({ 0, false });
        }
        else 
        {
            int parsed;
            if (!Parser::tryParseInt(line, parsed)) 
            {
                throw std::invalid_argument("Invalid integer format in file: " + line);
            }
            data.push_back({ parsed, true });
        }
    }
}
