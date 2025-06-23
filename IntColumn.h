#pragma once
#include "Column.h"
#include <vector>

/// \brief Class for integer column type
class IntColumn : public Column 
{
public:
    /// \brief Constructor accepting column name as parameter
    IntColumn(const std::string& name);

    std::string getTypeName() const override;

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

    Column* clone() const override;
private:
    std::vector<std::pair<int, bool>> data; ///< field for storing row values\n
                                                  /// which are pairs having a boolean\n
                                                  /// as second value which is 'false' if\n
                                                  /// the cell is 'NULL'
};
