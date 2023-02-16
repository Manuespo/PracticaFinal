#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    char nombre[20];
    char apellido[20];
    int edad;
    char deporte[20];
    int idDeporte;
}stRegistro;

typedef struct
{
    char nombre[20];
    char apellido[20];
    int edad;
}deportista;
typedef struct
{
    deportista dato;
    struct nodoDeportista* siguiente;
}nodoDeportista;

typedef struct
{
    char deporte[20];
    int idDeporte;
    nodoDeportista * listaDeportistas;
    struct nodoArbol* izq;
    struct nodoArbol* der;
}nodoArbol;

int main()
{

    return 0;
}
