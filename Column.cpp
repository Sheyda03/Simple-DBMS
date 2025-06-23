#include "Column.h"
#include <stdexcept>

Column::Column(const std::string& name) : name(name) {}

const std::string& Column::getName() const 
{
    return this->name;
}

void Column::setName(const std::string& newName) 
{
    if (newName.empty())
    {
        throw std::invalid_argument("Column name cannot be empty.");
    }

    this->name = newName;
}
