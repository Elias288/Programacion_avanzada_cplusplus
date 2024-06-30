#include <iostream>
#include <cstring>

#include "..\include\dataBaseOOP\Table.hpp"

using namespace std;

Table::Table(const char *_tableName)
{
    setTableName(_tableName);
    this->firstColumn = NULL;
    this->right = NULL;
    this->left = NULL;
}

Table::Table(Table *_table)
{
    setTableName(_table->tableName);
    this->firstColumn = _table->firstColumn;
    this->right = _table->right;
    this->left = _table->left;
}

void Table::setTableName(const char *_tableName)
{
    int sizeOfName = sizeof(this->tableName);
    strncpy(this->tableName, _tableName, sizeOfName - 1);
    this->tableName[sizeOfName - 1] = '\0';
}

void Table::setLeft(Table *_table)
{
    this->left = _table;
}

void Table::setRight(Table *_table)
{
    this->right = _table;
}

void Table::addNewTable(Table *_table)
{
    this->recursivePushTable(this, _table);
}

void Table::recursivePushTable(Table *actualTable, Table *newTable)
{
    if (actualTable == NULL)
    {
        actualTable = newTable;
        return;
    }

    if (actualTable->getTableName() == newTable->getTableName())
    {
        cerr << "Error, table already added" << endl;
        return;
    }

    if (actualTable->getTableName() < newTable->getTableName())
        recursivePushTable(actualTable->getRight(), newTable);

    if (actualTable->getTableName() > newTable->getTableName())
        recursivePushTable(actualTable->getLeft(), newTable);
}

void Table::pushColumn(Column *_newColumn)
{
    if (this->getFirstColumn() == NULL)
    {
        this->firstColumn = _newColumn;
        return;
    }

    Column *actualColumn = new Column(this->getFirstColumn());
    while (actualColumn->getNextColumn() != NULL)
        actualColumn = actualColumn->getNextColumn();
    actualColumn->setNextColumn(_newColumn);
}

char *Table::getTableName()
{
    return this->tableName;
}

Column *Table::getFirstColumn()
{
    return this->firstColumn;
}

Table *Table::getLeft()
{
    return this->left;
}

Table *Table::getRight()
{
    return this->right;
}

Table::~Table() {}
