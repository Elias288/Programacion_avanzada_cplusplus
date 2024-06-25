#include <cstddef>
#include <string>

#ifndef MODULE_H
#define MODULE_H
#define AUTOR ("LIAM TEXEIRA - ELIAS BIANCHI")

/*
 * SQL
 * Estructura basada en grafos en la que los nodos son las
 * columnas y las lineas son los datos de la tabla.
 * -----------------------------------------------------------------
 */

enum retorno
{
    _OK,
    _ERROR,
    _NO_IMPLEMENTADA
};

struct msgResponse
{
    retorno code;
    char message[100];
};

// Estructura Columnas
struct nodoSQL
{
    char nombre[30];      // nombre de la columna
    struct nodoSQL *sigN; // puntero al siguiente nodo
    struct datoSQL *priD; // puntero hacia el primer dato del nodo
};

// Estructura Tablas
struct Tabla
{
    char nombreT[30];       // nombre de la tabla
    struct nodoSQL *column; // columnas de la tabla
    struct Tabla *izq;      // puntero a siguiente tabla
    struct Tabla *der;
};

// Estructura Filas
struct datoSQL
{
    char valor[100];             // valor del dato
    struct datoSQL *sigL = NULL; // puntero a la siguente dato
};

typedef struct msgResponse TipoRet;

typedef struct nodoSQL *TnodoSQL; // Tipo Columna

typedef struct Tabla *TtablaSQL; // Tipo Tabla
typedef struct Tabla *pNodo;     // union tabla con columna

typedef struct datoSQL *TdatoSQL; // Tipo Dato

/* FUNCIONES */

const int INPUT_SIZE = 100;

bool tieneComa(char *texto);
void strtok_test();
void ayudas();
void insertarTabla(TtablaSQL &tabla, pNodo nuevo);
void borrarTabla(TtablaSQL &tabla, char *nombre);
void vaciarColumnas(TtablaSQL &tabla);
char *toLowerCase(char *string);
void obtieneAntesComa(char texto[]);
void borrarAntesComa(char texto[]);
void printTables(TtablaSQL &tabla);
void printFila(TtablaSQL &tabla, int dato);
int cantColumnas(TtablaSQL &tabla, char *Ntabla);
bool comillas(const char *texto);
void sacacomillas(char *texto);
void borrarantesPuntos(char texto[]);
void obtieneantesPuntos(char texto[]);
void borrarfila(TtablaSQL &BuscaT, int dato);

void chargeData(TtablaSQL &tabla);

TipoRet validarParentesis(char *argumento);
TipoRet comandos(char comando[], char argumento[], TtablaSQL &tabla);
TtablaSQL buscarTabla(TtablaSQL &tabla, char *nombre);
TtablaSQL unirArbol(TtablaSQL izq, TtablaSQL der);

/* FUNCIONES SQL */
TipoRet createTable(char *nombre, TtablaSQL &tabla);
TipoRet dropTable(char *nombre, TtablaSQL &tabla);
TipoRet addColumn(char *nombre, TtablaSQL &tabla);
TipoRet dropColumn(char *nombre, TtablaSQL &tabla);
TipoRet printDataTabla(char *nombre, TtablaSQL &tabla);
TipoRet insertInto(char *nombre, TtablaSQL &tabla);
TipoRet deleteFrom(char *nombre, TtablaSQL &tabla);

#endif