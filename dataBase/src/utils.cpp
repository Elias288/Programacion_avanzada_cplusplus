#include <iostream>
#include <cstring>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>
#include <regex>

#include "..\include\dataBase\module.hpp"

using namespace std;

bool tieneComa(char *texto)
{
    int x = 0, cantComas = 0;

    while (texto[x] != '\0')
    {
        if (texto[x] == ',')
        {
            cantComas++;
        }
        x++;
    }
    if (cantComas == 0)
    {
        return false;
    }
    return true;
}

void strtok_test()
{
    char frase[] = "Est Lorem ea sit dolore.";
    char *ptr /* , ptr1[10], ptr2[10] */;

    cout << "frase: " << frase << endl;

    ptr = strtok(frase, " ");
    // strcpy(ptr1, ptr);
    // ptr = strtok(NULL, " ");
    // strcpy(ptr2, ptr);
    // cout << ptr1 << " " << ptr2 << endl;

    while (ptr != NULL)
    {
        printf("%s\n", ptr);
        ptr = strtok(NULL, " ");
    }
}

void ayudas()
{
    // HANDLE hConsole;                                                          // consola
    // SetConsoleTextAttribute(hConsole = GetStdHandle(STD_OUTPUT_HANDLE), 112); // cambia el color el texto y de la consola

    /*
     * setw establece el ancho del campo que se utilizará para la operacióm de salida
     * https://cplusplus.com/reference/iomanip/setw/
     */
    cout << setw(69) << " " << endl;
    cout << "-createtable (NombreTabla)" << setw(43) << " " << endl;
    cout << "-droptable (NombreTabla)" << setw(45) << " " << endl;
    cout << "-addcol (NombreTabla, NombreColumna)" << setw(33) << " " << endl;
    cout << "-dropcol (NombreTabla, Nombrecolumna)" << setw(32) << " " << endl;
    cout << "-insertinto (NombreTabla,\"valor1\":\"valor2\":\"valor...\")" << setw(15) << " " << endl;
    cout << "-deletefrom (NombreTabla,NombreColumna=/!/</>/*\"valorn\")" << setw(12) << " " << endl;
    cout << "-printdatatable (NombreTabla)" << setw(40) << " " << endl;
    // cout << setw(69) << " " << endl;
    // cout << "-selectWhere (NuevaTabla, \"Condicion=/!/</>/*\"valorn\", NombreTabla)" << setw(2) << " " << endl;
    // cout << "-select (NuevaTabla, nombreColumna1:nombreColumna2:..., NombreTabla)" << setw(0) << " " << endl;
    // cout << "-join (NombreTabla1, NombreTabla2, NuevaTabla)" << setw(23) << " " << endl;
    // cout << "-union (NombreTabla1, NombreTabla2, NuevaTabla)" << setw(22) << " " << endl;
    cout << "-printTables ()" << setw(54) << " " << endl;
    cout << setw(69) << " " << endl;
    cout << "-exit" << setw(60) << " " << "" << endl;
    cout << "-clean" << setw(59) << " " << "" << endl;
    cout << setw(69) << " " << endl
         << endl;
}

void vaciarColumnas(TtablaSQL &tabla)
{
    TnodoSQL columna, columnaAEliminar;
    columna = tabla->column;

    if (columna == NULL)
        return;

    while (columna->sigN != NULL)
    {
        columnaAEliminar = columna;
        columna = columna->sigN;
        delete (columnaAEliminar);
    }
}

TtablaSQL buscarTabla(TtablaSQL &tabla, char *nombre)
{
    TtablaSQL result = NULL;

    if (tabla == NULL)
        return NULL;

    // Encontró la tabla
    if (strcmp(nombre, tabla->nombreT) == 0)
        return tabla;

    // Busqueda a la izquierda
    if (strcmp(nombre, tabla->nombreT) < 0)
        result = buscarTabla(tabla->izq, nombre);

    // Busqueda a la derecha
    if (strcmp(nombre, tabla->nombreT) > 0)
        result = buscarTabla(tabla->der, nombre);

    return result;
}

TtablaSQL unirArbol(TtablaSQL izq, TtablaSQL der)
{
    if (izq == NULL)
        return der;

    if (der == NULL)
        return izq;

    TtablaSQL centro = unirArbol(izq->der, der->izq);
    izq->der = centro;
    der->izq = izq;

    return der;
}

/*
 * Valida si el argumento ingresado está contenido entre () y si lo está devuelve
 * el contenido
 */
TipoRet validarParentesis(char *argument)
{
    int cantParentesis = 0, x = 0;
    int openPosition, closePosition;
    msgResponse resp;
    resp.code = _OK;
    strcpy(resp.message, "");

    while (argument[x] != '\0')
    {
        if (argument[x] == '(')
        {
            cantParentesis++;
            openPosition = x;
        }

        if (argument[x] == ')')
        {
            cantParentesis++;
            closePosition = x;
        }

        x++;
    }

    if (cantParentesis < 2)
    {
        resp.code = _ERROR;
        strcpy(resp.message, "ERROR, los argumentos debe estar entre parentesis");
        return resp;
    }

    string tempArg = argument;
    string argumentosSinParentesis = tempArg.substr(openPosition + 1, closePosition - openPosition - 1);
    strcpy(resp.message, argumentosSinParentesis.data());

    return resp;
}

char *toLowerCase(char *string)
{
    if (string == nullptr)
        return nullptr;

    for (int i = 0; i < string[i] != '\0'; i++)
        string[i] = tolower(string[i]);

    return string;
}

void obtieneAntesComa(char texto[INPUT_SIZE])
{
    int a = 0;
    while (texto[a] != '\0')
    {
        while (texto[a] != ',')
            a++;

        while (texto[a] != '\0')
            texto[a] = '\0';
    }
    return;
}

void borrarAntesComa(char texto[INPUT_SIZE])
{
    int a = 0;
    int largoC = strlen(texto);
    while (texto[0] != ',')
    {
        for (int i = 0; i < largoC; i++)
            texto[i] = texto[i + 1];
        largoC--;
    }

    for (int i = a; i < largoC; i++)
        texto[i] = texto[i + 1];
}

int cantColumnas(TtablaSQL &tabla, char *Ntabla)
{
    TtablaSQL BuscaT = tabla;
    TnodoSQL BuscaC;
    int cantColumnas = 0;

    BuscaT = buscarTabla(tabla, Ntabla);
    if (!BuscaT)
    {
        cout << "ERROR, NO EXISTE TABLA...!!\n";
        return 0;
    }

    /*-----------------------cantidad de columna-----------------------*/
    BuscaC = BuscaT->column;
    while (BuscaC)
    {
        cantColumnas++;
        BuscaC = BuscaC->sigN;
    }
    return cantColumnas;
}

bool comillas(const char *texto)
{
    // int comilla = 0, x = 0, num = 0;
    // char Ndato[50];
    // strcpy(Ndato, texto);

    // while (Ndato[x] != '\0')
    // {
    //     if (Ndato[x] >= '0' && Ndato[x] <= '9')
    //         num++;
    //     if (Ndato[x] == '"')
    //         comilla++;
    //     else if (Ndato[x] == ':')
    //     {
    //         if (num == 0)
    //         {
    //             if (comilla < 2)
    //                 return false;
    //             else
    //                 comilla = 0;
    //         }
    //     }
    //     num = 0;
    //     x++;
    // }
    // return true;

    // Define el patrón regex
    const regex patron(R"(^\"[^\"]+\"(:\"[^\"]+\")*$)");

    // Convertir el puntero a char a una cadena std::string para utilizarlo con std::regex
    string str(texto);

    // Evaluar si la cadena coincide con el patrón
    return regex_match(str, patron);
}

void sacacomillas(char *texto)
{
    int x = 0;
    int largo = strlen(texto); // obtiene el largo de la cadena de ergumentos
    while (texto[x] != '\0')
    {
        if (texto[x] == '"')
        {
            for (int i = x; i < largo; i++)
            {
                texto[i] = texto[i + 1];
            }
            largo--;
        }
        if (largo != 1)
            x++;
    }
}

void borrarantesPuntos(char texto[INPUT_SIZE])
{
    int a = 0;

    int largoC = strlen(texto);
    while (texto[0] != ':')
    {
        for (int i = a; i <= largoC; i++)
        {
            texto[i] = texto[i + 1];
        }
        largoC--;
    }
    for (int i = a; i <= largoC; i++)
    {
        texto[i] = texto[i + 1];
    }
}

void obtieneantesPuntos(char texto[INPUT_SIZE])
{
    int a = 0;

    while (texto[a] != '\0')
    {
        while (texto[a] != ':')
            a++;
        while (texto[a] != '\0')
        {
            texto[a] = '\0';
        }
    }
    return;
}

void borrarfila(TtablaSQL &BuscaT, int dato)
{
    TnodoSQL BuscaC = BuscaT->column;
    TdatoSQL BuscaD = BuscaC->priD, BorrarD;

    while (BuscaC)
    {
        BorrarD = BuscaC->priD;
        if (dato == 1)
        {
            BuscaC->priD = BorrarD->sigL;
            delete (BorrarD);
        }
        else
        {
            for (int i = 1; i < dato; i++)
            {
                BuscaD = BorrarD;
                BorrarD = BorrarD->sigL;
            }
            BuscaD->sigL = BorrarD->sigL;
            delete (BorrarD);
        }
        BuscaC = BuscaC->sigN;
    }
    return;
}
