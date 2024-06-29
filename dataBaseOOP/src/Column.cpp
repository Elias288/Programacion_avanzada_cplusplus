#include <iostream>
#include <cstring>

#include "..\include\dataBaseOOP\Column.hpp"

using namespace std;

Column::Column(const char *_columnName, const bool _isPrimaryKey)
{
    setColumnName(_columnName);
    this->isPrimaryKey = _isPrimaryKey;
    this->firstData = NULL;
    this->nextColumn = NULL;
}

Column::Column(Column *_column)
{
    setColumnName(_column->getColumnName());
    this->isPrimaryKey = _column->getIsPrimaryKey();
    this->firstData = _column->getFirstData();
    this->nextColumn = _column->getNextColumn();
}

void Column::setColumnName(const char *_columnName)
{
    int sizeOfName = sizeof(this->columnName);
    strncpy(this->columnName, _columnName, sizeOfName - 1);
    this->columnName[sizeOfName - 1] = '\0';
}

void Column::setNextColumn(Column *_nextColumn)
{
    this->nextColumn = _nextColumn;
}

void Column::pushData(Data *_data)
{
    if (this->firstData->getNextData() == NULL)
    {
        this->firstData = _data;
        return;
    }

    Data *actualData = new Data(this->firstData);
    // Go to end
    while (actualData->getNextData() != NULL)
        actualData = actualData->getNextData();
    actualData->setNextData(_data);
}

char *Column::getColumnName()
{
    return this->columnName;
}

bool Column::getIsPrimaryKey()
{
    return this->isPrimaryKey;
}

Column *Column::getNextColumn()
{
    return this->nextColumn;
}

Data *Column::getFirstData()
{
    return this->firstData;
}

Column::~Column() {}
