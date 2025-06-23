#include "DoubleColumn.h"
#include "Parser.h"
#include <stdexcept>
#include <iostream>

DoubleColumn::DoubleColumn(const std::string& name) : Column(name) {}

std::string DoubleColumn::getTypeName() const 
{
    return "double";
}

Column* DoubleColumn::clone() const 
{
    return new DoubleColumn(*this);
}

void DoubleColumn::addEmpty() 
{
    data.emplace_back(0.0, false);
}

void DoubleColumn::addValue(const std::string& value) 
{
    double parsed;
    if (value == "NULL") 
    {
        addEmpty();
    }
    else if (Parser::tryParseDouble(value, parsed)) 
    {
        data.emplace_back(parsed, true);
    }
    else 
    {
        throw std::invalid_argument("Invalid double value: " + value);
    }
}

void DoubleColumn::setValueAt(size_t index, const std::string& value) 
{
    if (index >= data.size())
    {
        throw std::out_of_range("Index out of range in setValueAt");
    }

    if (value == "NULL") 
    {
        data[index] = { 0.0, false };
    }
    else 
    {
        double parsed;
        if (Parser::tryParseDouble(value, parsed)) 
        {
            data[index] = { parsed, true };
        }
        else 
        {
            throw std::invalid_argument("Invalid double value: " + value);
        }
    }
}

std::string DoubleColumn::getValueAt(size_t index) const 
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

bool DoubleColumn::compare(size_t index, const std::string& value) const 
{
    if (index >= data.size())
    {
        return false;
    }

    if (!data[index].second)
    {
        return false;
    }

    double parsed;
    if (!Parser::tryParseDouble(value, parsed))
    {
        return false;
    }

    return data[index].first == parsed;
}

void DoubleColumn::updateValue(size_t index, const std::string& value) 
{
    setValueAt(index, value);
}

void DoubleColumn::removeRow(size_t index) 
{
    if (index < data.size()) 
    {
        data.erase(data.begin() + index);
    }
}
size_t DoubleColumn::size() const 
{
    return data.size();
}
void DoubleColumn::serialize(std::ostream& out) const 
{
    out << getName() << "\n" << getTypeName() << "\n";
    for (const auto& pair : data) 
    {
        if (pair.second)
        {
            out << pair.first << "\n";
        }
        else
        {
            out << "NULL\n";
        }
    }
}

void DoubleColumn::deserialize(std::istream& in, size_t rowsCount) 
{
    data.clear();
    for (size_t i = 0; i < rowsCount; ++i) 
    {
        std::string value;
        std::getline(in, value);
        addValue(value);
    }
}
