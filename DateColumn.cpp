#include "DateColumn.h"
#include "Parser.h"
#include <stdexcept>
#include <iostream>

DateColumn::DateColumn(const std::string& name) : Column(name) {}

std::string DateColumn::getTypeName() const 
{
    return "DATE";
}

Column* DateColumn::clone() const 
{
    return new DateColumn(*this);
}

void DateColumn::addEmpty() 
{
    data.emplace_back(Date(), false);
}
size_t DateColumn::size() const 
{
    return data.size();
}
void DateColumn::addValue(const std::string& value) 
{
    if (value == "NULL") 
    {
        addEmpty();
        return;
    }

    Date parsed;
    if (!Parser::tryParseDate(value, parsed)) 
    {
        throw std::invalid_argument("Invalid date: " + value);
    }

    data.emplace_back(parsed, true);
}

void DateColumn::setValueAt(size_t index, const std::string& value) 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Index out of range");
    }

    if (value == "NULL") 
    {
        data[index].second = false;
        return;
    }

    Date parsed;
    if (!Parser::tryParseDate(value, parsed)) 
    {
        throw std::invalid_argument("Invalid date: " + value);
    }

    data[index] = { parsed, true };
}

std::string DateColumn::getValueAt(size_t index) const 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Index out of range");
    }

    return data[index].second ? data[index].first.toString() : "NULL";
}

bool DateColumn::compare(size_t index, const std::string& value) const 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Index out of range");
    }

    if (!data[index].second || value == "NULL") 
    {
        return false;
    }

    Date search;
    if (!Parser::tryParseDate(value, search)) 
    {
        throw std::invalid_argument("Invalid date: " + value);
    }

    return data[index].first == search;
}

void DateColumn::updateValue(size_t index, const std::string& value) 
{
    setValueAt(index, value);
}

void DateColumn::removeRow(size_t index) 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Index out of range");
    }

    data.erase(data.begin() + index);
}

void DateColumn::serialize(std::ostream& out) const 
{
    out << getName() << "\n" << getTypeName() << "\n";
    for (const auto& entry : data) 
    {
        if (entry.second)
        {
            out << entry.first.toString() << "\n";
        }
        else
        {
            out << "NULL\n";
        }
    }
}

void DateColumn::deserialize(std::istream& in, size_t rowsCount) 
{
    data.clear();
    std::string line;
    for (size_t i = 0; i < rowsCount; ++i) 
    {
        std::getline(in, line);
        addValue(line);
    }
}
