#include <iostream>
#include <cstring>
#include <iomanip>
#include <windows.h>
#include <stdlib.h>

#include "..\include\dataBase\module.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
    HANDLE hConsole;
    TtablaSQL tabla = NULL;
    char text[INPUT_SIZE], command[INPUT_SIZE], argument[INPUT_SIZE];
    char *ptr;
    int exit = 1;

    SetConsoleTextAttribute(hConsole = GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << AUTOR << "\n\n";
    SetConsoleTextAttribute(hConsole = GetStdHandle(STD_OUTPUT_HANDLE), 5);
    cout << "AYUDAS - 'ayudas'" << "\n\n";
    SetConsoleTextAttribute(hConsole = GetStdHandle(STD_OUTPUT_HANDLE), 3);
    cout << "PARA OPTIMO FUNCIONAMIENTO DEL GESTOR RESPETAR ESPACIOS, \nMINUSCULAS Y SEPARADORES DE ARGUMENTOS" << "\n\n";

    do
    {
        SetConsoleTextAttribute(hConsole = GetStdHandle(STD_OUTPUT_HANDLE), 14);
        cout << "MYSQL>";
        SetConsoleTextAttribute(hConsole = GetStdHandle(STD_OUTPUT_HANDLE), 15);

        cin.getline(text, 100);

        if (strlen(text) == 0)
            continue;

        ptr = strtok(text, " "); // separa el texto ingresado en un array por palabra

        strcpy(command, toLowerCase(ptr)); // copia la primer palabra en command
        ptr = strtok(NULL, " ");

        // Limpia el contenido del argument
        memset(argument, '\0', INPUT_SIZE);
        // Recorre el resto del texto ingresado y lo guarda en argument
        while (ptr != NULL)
        {
            strcat(argument, " ");
            strcat(argument, ptr);
            ptr = strtok(NULL, " ");
        }

        // comando exit
        if (strcmp(command, "exit") == 0)
        {
            exit = 0;
            break;
        }
        /* AYUDAS */
        if (strcmp(command, "ayudas") == 0)
        {
            ayudas();
            continue;
        }

        /* CLEAN */
        else if (strcmp(command, "clean") == 0)
        {
            system("cls");
            continue;
        }

        TipoRet res = comandos(command, argument, tabla);
        if (res.message[0] != '\0')
            cout << res.message << endl;

    } while (exit != 0);

    return 0;
}

TipoRet comandos(char *comando, char *argumento, TtablaSQL &tabla)
{
    HANDLE hConsole;
    msgResponse resp;
    resp.code = _OK;
    strcpy(resp.message, "");

    TipoRet validadorResp = validarParentesis(argumento);
    if (validadorResp.code == _ERROR)
        return validadorResp;
    char *argumentoSinParentesis = validadorResp.message;

    /* CREATE TABLE */
    if (strcmp(comando, "createtable") == 0)
        resp = createTable(argumentoSinParentesis, tabla);

    /* DROP TABLE */
    else if (strcmp(comando, "droptable") == 0)
        resp = dropTable(argumentoSinParentesis, tabla);

    /* ADD COLUMN */
    else if (strcmp(comando, "addcol") == 0)
        resp = addColumn(argumentoSinParentesis, tabla);

    /* DROP CLUMN */
    else if (strcmp(comando, "dropcol") == 0)
        resp = dropColumn(argumentoSinParentesis, tabla);

    /* INSERT INTO */
    else if (strcmp(comando, "insertinto") == 0)
        resp = insertInto(argumentoSinParentesis, tabla);

    /* DELETE FROM */
    else if (strcmp(comando, "deletefrom") == 0)
        resp = deleteFrom(argumentoSinParentesis, tabla);

    /* PRINT DATA TABLE */
    else if (strcmp(comando, "printdatatable") == 0)
        resp = printDataTabla(argumentoSinParentesis, tabla);

    /* SELECT WHERE */
    /* SELECT */
    /* JOIN */
    /* UNION */
    /* PRINT TABLES */
    else if (strcmp(comando, "printtables") == 0)
        printTables(tabla);
    else
    {
        resp.code = _ERROR;
        strcpy(resp.message, "Comando no encontrado");
    }

    return resp;
}
