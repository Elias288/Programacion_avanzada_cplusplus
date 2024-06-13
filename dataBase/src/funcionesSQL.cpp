#include <iostream>
#include <cstring>

#include "..\include\dataBase\module.hpp"

using namespace std;

void insertarTabla(TtablaSQL &tabla, pNodo nuevaTabla)
{
    // Raiz
    if (tabla == NULL)
        tabla = nuevaTabla;

    // Error, nombre de tabla ya registrada
    if (strcmp(nuevaTabla->nombreT, tabla->nombreT) == 0)
        return;

    // Inserta a la izquierda
    if (strcmp(nuevaTabla->nombreT, tabla->nombreT) < 0)
        insertarTabla(tabla->izq, nuevaTabla);

    // Inserta a la derecha
    if (strcmp(nuevaTabla->nombreT, tabla->nombreT) > 0)
        insertarTabla(tabla->der, nuevaTabla);
}

TipoRet createTable(char *nombre, TtablaSQL &tabla)
{
    msgResponse resp;
    resp.code = _OK;
    string message = "";

    if (strcmp(nombre, "") == 0)
    {
        message = "ERROR, FALTA NOMBRE TABLA";
        strcpy(resp.message, message.data());
        resp.code = _ERROR;
        return resp;
    }

    // si la tabla existe
    if (buscarTabla(tabla, nombre))
    {
        message = "ERROR, TABLA REPETIDA";
        strcpy(resp.message, message.data()); // Muestro el valor del principio
        resp.code = _ERROR;
        return resp;
    }

    // Se crea una tabla nueva
    TtablaSQL nuevaTabla = new Tabla;
    nuevaTabla->izq = NULL;
    nuevaTabla->der = NULL;
    nuevaTabla->column = NULL;
    strcpy(nuevaTabla->nombreT, nombre);

    insertarTabla(tabla, nuevaTabla);
    strcpy(resp.message, "Tabla agregada");

    return resp;
}

void borrarTabla(TtablaSQL &tabla, char *nombre)
{
    if (tabla == NULL)
        return;

    if (strcmp(nombre, tabla->nombreT) == 0)
    {
        TtablaSQL tablaToDelete = tabla;

        if (tablaToDelete->column != NULL)
            vaciarColumnas(tablaToDelete); // vacía los datos de la tabla

        if (tablaToDelete->izq != NULL || tablaToDelete->der != NULL)
            tabla = unirArbol(tablaToDelete->izq, tablaToDelete->der); // vuelve a unir el arbol

        delete tablaToDelete;
        return;
    }

    // Busca a la izquierda
    if (strcmp(nombre, tabla->nombreT) < 0)
        borrarTabla(tabla->izq, nombre);

    // Busca a la derecha
    if (strcmp(nombre, tabla->nombreT) > 0)
        borrarTabla(tabla->der, nombre);
}

TipoRet dropTable(char *nombre, TtablaSQL &tabla)
{
    msgResponse resp;
    resp.code = _OK;

    if (strcmp(nombre, "") == 0)
    {
        strcpy(resp.message, "ERROR, FALTA NOMBRE TABLA");
        resp.code = _ERROR;
        return resp;
    }

    // si la tabla no existe
    if (!buscarTabla(tabla, nombre))
    {
        strcpy(resp.message, "ERROR, TABLA NO EXISTE"); // Muestro el valor del principio
        resp.code = _ERROR;
        return resp;
    }

    borrarTabla(tabla, nombre);
    strcpy(resp.message, "Tabla eliminada");
    return resp;
}

void printTables(TtablaSQL &tabla)
{
    if (tabla != NULL)
        cout << tabla->nombreT << endl;

    if (tabla->izq != NULL)
        printTables(tabla->izq);

    if (tabla->der != NULL)
        printTables(tabla->der);

    return;
}
