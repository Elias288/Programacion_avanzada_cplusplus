#ifndef COLUMN_H_
#define COLUMN_H_

#include "Data.hpp"

using namespace std;

class Column
{
private:
    char columnName[100];
    Column *nextColumn;
    Data *firstData;
    bool isPrimaryKey;

public:
    Column(const char *_columnName, const bool _isPrimaryKey);
    Column(Column *_column);

    char *getColumnName();
    bool getIsPrimaryKey();
    Column *getNextColumn();
    Data *getFirstData();

    void setColumnName(const char *_columnName);
    void setNextColumn(Column *_nextColumn);
    void pushData(Data *_data);

    virtual ~Column();
};

#endif // COLUMN_H_