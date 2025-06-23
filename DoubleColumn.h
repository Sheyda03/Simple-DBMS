#pragma once
#include "Column.h"
#include <vector>
#include <string>

/// \brief Represents a column containing double values.
class DoubleColumn : public Column 
{
public:
    /// \brief Constructor for DoubleColumn.
    /// \param name Name of the column.
    DoubleColumn(const std::string& name);

    std::string getTypeName() const override;
    Column* clone() const override;

    void addEmpty() override;
    void addValue(const std::string& value) override;

    void setValueAt(size_t index, const std::string& value) override;
    std::string getValueAt(size_t index) const override;

    bool compare(size_t index, const std::string& value) const override;
    void updateValue(size_t index, const std::string& value) override;

    void removeRow(size_t index) override;
    size_t size() const override;

    void serialize(std::ostream& out) const override;
    void deserialize(std::istream& in, size_t rowsCount) override;
private:
    std::vector<std::pair<double, bool>> data; ///< Stores date values and validity flags.
};
