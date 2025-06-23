#include "StringColumn.h"
#include <stdexcept>
#include <iostream>
#include "Parser.h"

StringColumn::StringColumn(const std::string& name) : Column(name) {}

std::string StringColumn::getTypeName() const 
{
    return "string";
}
size_t StringColumn::size() const 
{
    return data.size();
}
Column* StringColumn::clone() const 
{
    return new StringColumn(*this);
}

void StringColumn::addEmpty() 
{
    data.emplace_back("", false);
}

void StringColumn::addValue(const std::string& value) 
{
    if (value == "NULL") 
    {
        addEmpty();
    }
    else 
    {
        data.emplace_back(unescapeString(value), true);
    }
}

void StringColumn::setValueAt(size_t index, const std::string& value) 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Invalid index in setValueAt");
    }

    if (value == "NULL") 
    {
        data[index] = { "", false };
    }
    else 
    {
        data[index] = { unescapeString(value), true };
    }
}

std::string StringColumn::getValueAt(size_t index) const 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Invalid index in getValueAt");
    }

    if (!data[index].second) 
    {
        return "NULL";
    }

    return escapeString(data[index].first);
}

bool StringColumn::compare(size_t index, const std::string& value) const 
{
    if (!data[index].second) 
    {
        return false;
    }
    return compareSubstr(data[index].first, value);
}

void StringColumn::updateValue(size_t index, const std::string& value) 
{
    setValueAt(index, value);
}

void StringColumn::removeRow(size_t index) 
{
    if (index >= data.size()) 
    {
        throw std::out_of_range("Invalid index in removeRow");
    }

    data.erase(data.begin() + index);
}

void StringColumn::serialize(std::ostream& out) const 
{
    out << getName() << "\n" << getTypeName() << "\n";

    for (const auto& pair : data) 
    {
        out << (pair.second ? escapeString(pair.first) : "NULL") << "\n";
    }
}

void StringColumn::deserialize(std::istream& in, size_t rowsCount) 
{
    data.clear();
    std::string line;

    for (size_t i = 0; i < rowsCount; ++i) 
    {
        std::getline(in, line);
        if (line == "NULL") 
        {
            addEmpty();
        }
        else 
        {
            data.emplace_back(unescapeString(line), true);
        }
    }
}

std::string StringColumn::escapeString(const std::string& raw) 
{
    std::string escaped;
    for (char ch : raw) 
    {
        if (ch == '"') 
        {
            escaped += "\\\"";
        }
        else if (ch == '\\') 
        {
            escaped += "\\\\";
        }
        else
        {
            escaped += ch;
        }
    }
    return "\"" + escaped + "\"";
}

std::string StringColumn::unescapeString(const std::string& raw) 
{
    std::string cleaned = raw;
    if (!cleaned.empty() && cleaned.front() == '"' && cleaned.back() == '"') 
    {
        cleaned = cleaned.substr(1, cleaned.size() - 2);
    }

    std::string result;
    for (size_t i = 0; i < cleaned.size(); ++i) 
    {
        if (cleaned[i] == '\\' && i + 1 < cleaned.size()) 
        {
            if (cleaned[i + 1] == '"' || cleaned[i + 1] == '\\') 
            {
                result += cleaned[i + 1];
                ++i;
            }
            else 
            {
                result += cleaned[i];
            }
        }
        else 
        {
            result += cleaned[i];
        }
    }
    return result;
}
bool StringColumn::compareSubstr(const std::string& a, const std::string& b)
{
    std::string aLower = Parser::toLower(a);
    std::string bLower = Parser::toLower(b);

    for (size_t i = 0; i + bLower.size() <= aLower.size(); ++i) 
    {
        if (aLower.substr(i, bLower.size()) == bLower)
        {
            return true;
        }
    }

    return false;
}
