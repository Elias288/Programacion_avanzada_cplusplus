#ifndef TABLE_H_
#define TABLE_H_

#include "Column.hpp"

using namespace std;

class Table
{
private:
    char tableName[100];
    Column *firstColumn;
    Table *left;
    Table *right;

tublic:
    Table(const char *_tableName);
    Table(Table *_table);

    void setTableName(const char *_tableName);
    void setLeft(Table *_table);
    void setRight(Table *_table);
    void addNewTable(Table *_table);
    void recursivePushTable(Table *actualTable, Table *newTable);
    void pushColumn(Column *newColumn);

    char *getTableName();
    Column *getFirstColumn();
    Table *getLeft();
    Table *getRight();

    virtual ~Table();
};

#endif // TABLE_H_
