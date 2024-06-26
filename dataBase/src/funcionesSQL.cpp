#include <iostream>
#include <iomanip>
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

TipoRet printDataTabla(char *nombre, TtablaSQL &tabla)
{
    TipoRet resp;
    TnodoSQL BuscaC;
    TdatoSQL BuscaD;
    int col = 0;
    char Ntabla[INPUT_SIZE], Ndato[INPUT_SIZE], NomT[INPUT_SIZE];

    strcpy(Ntabla, nombre);
    TtablaSQL BuscaT = buscarTabla(tabla, Ntabla);
    if (!BuscaT)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "ERROR, NO EXISTE LA TABLA...\n");
        return resp;
    }

    strcpy(NomT, BuscaT->nombreT);
    int largoT = strlen(NomT);
    for (int i = 0; i < largoT; i++)
        NomT[i] = toupper(NomT[i]);

    cout << "\n|" << NomT << "|" << endl;

    // Si no tiene columnas
    BuscaC = BuscaT->column;
    if (!BuscaC)
    {
        resp.code = _OK;
        return resp;
    }

    while (BuscaC)
    {
        cout << ": " << BuscaC->nombre << " ";
        BuscaC = BuscaC->sigN;
    }
    cout << ":" << endl;

    BuscaC = BuscaT->column;
    BuscaD = BuscaC->priD;
    while (BuscaD)
    {
        col++;
        BuscaD = BuscaD->sigL;
    }

    // Si no tiene datos
    BuscaD = BuscaC->priD;
    if (!BuscaD)
    {
        resp.code = _OK;
        return resp;
    }

    strcpy(Ndato, BuscaD->valor);
    for (int i = 0; i < col; i++)
    {
        printFila(BuscaT, i);
        cout << ":" << endl;
    }

    cout << endl;
    resp.code = _OK;
    return resp;
}

// addcol (NombreTabla, NombreColumna)
TipoRet addColumn(char *nombre, TtablaSQL &tabla)
{
    msgResponse resp;
    char Ntabla[INPUT_SIZE], NColumna[INPUT_SIZE];
    TnodoSQL BuscaC;

    strcpy(Ntabla, nombre);
    obtieneAntesComa(Ntabla);

    TtablaSQL BuscaT = buscarTabla(tabla, Ntabla);
    if (!BuscaT)
    {
        strcpy(resp.message, "ERROR, NO EXISTE LA TABLA...\n");
        resp.code = _ERROR;
        return resp;
    }

    strcpy(NColumna, nombre);
    borrarAntesComa(NColumna);

    TnodoSQL nuevo = new struct nodoSQL;
    strcpy(nuevo->nombre, NColumna);
    nuevo->sigN = NULL;
    nuevo->priD = NULL;
    TnodoSQL q;

    // Si la tabla no tiene columnas
    if (!BuscaT->column)
    {
        BuscaT->column = nuevo;
        strcpy(resp.message, "Columna agregada\n");
        resp.code = _OK;
        return resp;
    }

    BuscaC = BuscaT->column;
    if (BuscaC->priD)
    {
        strcpy(resp.message, "ERROR, LAS COLUMNAS DE ESTA TABLA YA TIENEN DATOS...\n");
        resp.code = _ERROR;
        return resp;
    }
    q = BuscaT->column;
    while (q->sigN != NULL)
        q = q->sigN;
    q->sigN = nuevo;
    strcpy(resp.message, "Columna agregada\n");
    resp.code = _OK;
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

void printFila(TtablaSQL &tabla, int dato)
{
    TnodoSQL BuscaC = tabla->column;
    TdatoSQL BuscaD = NULL;

    while (BuscaC)
    {
        BuscaD = BuscaC->priD;
        for (int i = 1; i <= dato; i++)
        {
            BuscaD = BuscaD->sigL;
        }
        cout << setw(2) << ": " << BuscaD->valor << " ";
        BuscaC = BuscaC->sigN;
    }
    return;
}

TipoRet dropColumn(char *nombre, TtablaSQL &tabla)
{
    TipoRet resp;
    int a = 0;
    char Ntabla[INPUT_SIZE], Ncolumna[INPUT_SIZE];
    TnodoSQL eliminar = NULL, BuscarC = NULL;

    strcpy(Ntabla, nombre);
    obtieneAntesComa(Ntabla);

    TtablaSQL BuscaT = buscarTabla(tabla, Ntabla);
    if (!BuscaT)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "ERROR, NO EXISTE LA TABLA...\n");
        return resp;
    }
    if (BuscaT->column == NULL)
    {
        strcpy(resp.message, "ERROR, TABLA VACIA...\n");
        resp.code = _ERROR;
        return resp;
    }

    strcpy(Ncolumna, nombre);
    borrarAntesComa(Ncolumna);

    eliminar = BuscaT->column; // inicaliza en el primer columna
    BuscarC = BuscaT->column;  // inicaliza en el primer columna

    // Busca la columna a eliminar
    while (strcmp(eliminar->nombre, Ncolumna) != 0)
    {
        // si el nombre de la tabla no es el de la tabla a eliminar
        BuscarC = eliminar;        // BuscaC toma el valor anterior de eliminar
        eliminar = eliminar->sigN; // eliminar pasa a la siguiente columna
    }

    if (!eliminar)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "Error, Columna no encontrada...\n");
        return resp;
    }

    if (eliminar == BuscaT->column)
        BuscaT->column = BuscaT->column->sigN; // une el puntero a las columnas a la siguiente columna
    else
        BuscarC->sigN = eliminar->sigN; // une la columna anterior con el siguiente de la columna a eliminar

    delete (eliminar);
    resp.code = _OK;
    strcpy(resp.message, "Columna eliminada correctamente...\n");
    return resp;
}

// insertinto (NombreTabla,"valor1":"valor2":"valor...")
TipoRet insertInto(char *nombre, TtablaSQL &tabla)
{
    TipoRet resp;
    TnodoSQL BuscaC;
    TdatoSQL anterior = NULL, BuscaD;
    char Ntabla[INPUT_SIZE], Ndato[INPUT_SIZE], Dato[INPUT_SIZE];
    int a = 0, coma = 1, columna = 0, fila = 1;

    strcpy(Ntabla, nombre);
    // Verifica que exista por lo menos una ,
    if (tieneComa(Ntabla) == 0)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "ERROR, FALTAN DATOS...\n");
        return resp;
    }
    obtieneAntesComa(Ntabla); // borra todo lo esté despúes de la ,

    TtablaSQL BuscaT = buscarTabla(tabla, Ntabla);
    if (!BuscaT)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "ERROR, NO EXISTE LA TABLA...\n");
        return resp;
    }
    if (BuscaT->column == NULL)
    {
        strcpy(resp.message, "ERROR, TABLA VACIA...\n");
        resp.code = _ERROR;
        return resp;
    }
    BuscaC = BuscaT->column;

    strcpy(Ndato, nombre);
    borrarAntesComa(Ndato);
    int nColumnas = cantColumnas(tabla, Ntabla);

    bool res = comillas(Ndato);
    if (!res)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "Error, los datos deben estar entre comillas");
        return resp;
    }
    sacacomillas(Ndato);

    // Cuenta la cantidad de datos ingresados
    while (Ndato[a] != '\0')
    {
        if (Ndato[a] == ':')
        {
            coma++;
        }
        a++;
    }

    if (nColumnas != coma)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "Error, cantidad de campos invalidos");
        return resp;
    }

    while (BuscaC)
    {
        if (BuscaT->column == BuscaC)
        { // si es la primera columna
            strcpy(Dato, Ndato);
            if (BuscaT->column->sigN)
            { // si la tabla tiene mas de una columna
                obtieneantesPuntos(Dato);
            }
            BuscaD = BuscaC->priD;
            while (BuscaD)
            {
                if (strcmp(BuscaD->valor, Dato) == 0)
                {
                    resp.code = _ERROR;
                    strcpy(resp.message, "Error, cantidad de campos invalidos");
                    return resp;
                }
                BuscaD = BuscaD->sigL;
            }
        }

        if (BuscaC->sigN == NULL)
        { // si es la ultima columna
            strcpy(Dato, Ndato);
            if (BuscaT->column->sigN)
            {
                for (int x = 0; x < columna; x++)
                {
                    borrarantesPuntos(Dato);
                }
            }
        }

        if (BuscaC->sigN != NULL && BuscaT->column != BuscaC)
        { // si es la columna del medio

            strcpy(Dato, Ndato);
            if (BuscaT->column->sigN)
            {
                for (int x = 0; x < columna; x++)
                {
                    borrarantesPuntos(Dato);
                }
                obtieneantesPuntos(Dato);
            }
        }

        columna++;
        /*---------------guarda el nodo dato en el nodo columna---------------*/
        TdatoSQL nuevo = new struct datoSQL;
        strcpy(nuevo->valor, Dato);
        nuevo->sigL = NULL;
        anterior = NULL;

        if (BuscaC->priD != NULL)
        { // si la columna tiene datos
            if (BuscaT->column == BuscaC)
            { // si la columna es la pk
                if (strcmp(nuevo->valor, BuscaC->priD->valor) < 0)
                { // si la nueva pk es menor a la pk
                    nuevo->sigL = BuscaC->priD;
                    BuscaC->priD = nuevo;
                    BuscaC = BuscaC->sigN;
                }
                else
                { // si la nueva pk en mayor a la pk
                    anterior = BuscaC->priD;
                    while (anterior->sigL && strcmp(anterior->sigL->valor, nuevo->valor) < 0)
                    {                              // si el valor del siguiente anterior es menor que el nuevo valor
                        anterior = anterior->sigL; // q avanza
                        fila++;
                    }
                    if (strcmp(nuevo->valor, anterior->valor) > 0)
                    { // si el nuevo valor es mayor que el valor anterior
                        nuevo->sigL = anterior->sigL;
                        fila++;
                        anterior->sigL = nuevo;
                    }
                    // si el nuevo valor es menor que el valor anterior
                    else
                        nuevo->sigL = anterior;

                    BuscaC = BuscaC->sigN;
                }
            }
            else
            { // si la columna tiene al menos un dato
                anterior = BuscaC->priD;
                if (fila == 1)
                {
                    nuevo->sigL = anterior;
                    BuscaC->priD = nuevo;
                    BuscaC = BuscaC->sigN;
                }
                else
                {
                    for (int i = 2; i < fila; i++)
                        anterior = anterior->sigL;

                    nuevo->sigL = anterior->sigL;
                    anterior->sigL = nuevo;
                    BuscaC = BuscaC->sigN;
                }
            }
        }
        else
        {
            BuscaC->priD = nuevo;
            BuscaC = BuscaC->sigN;
        }
    }
    return resp;
}

TipoRet deleteFrom(char *nombre, TtablaSQL &tabla)
{
    TipoRet resp;
    TnodoSQL BuscaC;
    TdatoSQL anterior = NULL, BuscaD;
    char Ntabla[INPUT_SIZE], Ndato[INPUT_SIZE], Dato[INPUT_SIZE], operador[1], valor[INPUT_SIZE], palabra[INPUT_SIZE], Ncol[INPUT_SIZE];
    int a = 0, coma = 0, dato = 1;

    strcpy(Ntabla, nombre);
    // Verifica que exista por lo menos una ,
    if (tieneComa(Ntabla) == 0)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "ERROR, FALTAN DATOS...\n");
        return resp;
    }
    obtieneAntesComa(Ntabla); // borra todo lo esté despúes de la ,

    TtablaSQL BuscaT = buscarTabla(tabla, Ntabla);
    if (!BuscaT)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "ERROR, NO EXISTE LA TABLA...\n");
        return resp;
    }
    if (BuscaT->column == NULL)
    {
        strcpy(resp.message, "ERROR, TABLA VACIA...\n");
        resp.code = _ERROR;
        return resp;
    }
    BuscaC = BuscaT->column;

    strcpy(Ndato, nombre);
    borrarAntesComa(Ndato);
    int nColumnas = cantColumnas(tabla, Ntabla);

    int largoD = strlen(Ndato);
    bool res = comillas(Ndato);
    if (!res)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "Error, los datos deben estar entre comillas");
        return resp;
    }
    sacacomillas(Ndato);

    BuscaT = tabla;
    BuscaC = NULL;
    TdatoSQL BorrarD = NULL;

    BuscaC = BuscaT->column;
    while (BuscaC)
    {
        if (strcmp(BuscaC->nombre, Ncol) == 0)
        { // si encuentro la columna
            BorrarD = BuscaC->priD;
            /*si el operador es =*/
            if (strncmp(operador, "=", 1) == 0)
            {
                while (BorrarD)
                {
                    if (strcmp(BorrarD->valor, Ndato) == 0)
                    { // si encontramos el dato
                        BorrarD = BorrarD->sigL;
                        borrarfila(BuscaT, dato);
                    }
                    else
                    {
                        BorrarD = BorrarD->sigL;
                        dato++;
                    }
                }
                resp.code = _OK;
                strcpy(resp.message, "listo");
                return resp;
            }
            /*si el operador es !*/
            else if (strncmp(operador, "!", 1) == 0)
            {
                while (BorrarD)
                {
                    if (strcmp(BorrarD->valor, Ndato) == 0)
                    { // si encontramos el dato
                        BorrarD = BorrarD->sigL;
                        dato++;
                    }
                    else
                    {
                        BorrarD = BorrarD->sigL;
                        borrarfila(BuscaT, dato);
                    }
                }
                resp.code = _OK;
                strcpy(resp.message, "listo");
                return resp;
            }
            /*si el operador es <*/
            else if (strncmp(operador, "<", 1) == 0)
            {
                while (BorrarD)
                {
                    largoD = strlen(Ndato);
                    for (int i = 0; i < largoD; i++)
                        valor[i] = BorrarD->valor[i];
                    if (strcmp(valor, Ndato) > 0)
                    {
                        BorrarD = BorrarD->sigL;
                        dato++;
                    }
                    else
                    {
                        BorrarD = BorrarD->sigL;
                        borrarfila(BuscaT, dato);
                    }
                }
                resp.code = _OK;
                strcpy(resp.message, "listo");
                return resp;
            }
            /*si el operador es >*/
            else if (strncmp(operador, ">", 1) == 0)
            {
                while (BorrarD)
                {
                    for (int i = 0; i < 2; i++)
                        valor[i] = BorrarD->valor[i];
                    if (strcmp(valor, Ndato) < 0)
                    {
                        BorrarD = BorrarD->sigL;
                        dato++;
                    }
                    else
                    {
                        BorrarD = BorrarD->sigL;
                        borrarfila(BuscaT, dato);
                    }
                }
                resp.code = _OK;
                strcpy(resp.message, "listo");
                return resp;
            }
            /*si el operador es **/
            else if (strncmp(operador, "*", 1) == 0)
            {
                largoD = strlen(Ndato);
                while (BorrarD)
                {
                    strcpy(palabra, BorrarD->valor);
                    palabra[largoD] = '\0';
                    if (strcmp(palabra, Ndato) == 0)
                    { // si encontramos el dato
                        BorrarD = BorrarD->sigL;
                        borrarfila(BuscaT, dato);
                    }
                    else
                    {
                        BorrarD = BorrarD->sigL;
                        dato++;
                    }
                }
                resp.code = _OK;
                strcpy(resp.message, "listo");
                return resp;
            }
            resp.code = _ERROR;
            strcpy(resp.message, "ERROR, EL DATO NO EXISTE O NO SE ECUENTRA EN ESTA TABLA\n");
            return resp;
        }
        else
            BuscaC = BuscaC->sigN;
    }

    return resp;
}
