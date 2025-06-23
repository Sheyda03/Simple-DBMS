#pragma once
#include <string>
#include "Column.h"

/// \brief Factory class to create columns
class ColumnFactory 
{
public:
    /// \brief Static function which produces a column
        /// \param first 'const string' which is the column type
        /// \param second 'const string' which is the column name
        /// \return 'Column*' newly created column or nullptr
    static Column* createColumn(const std::string& type, const std::string& name);
};


