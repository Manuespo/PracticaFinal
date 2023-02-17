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

nodoArbol* inicArbol();
nodoArbol * crearNodoArbol(stRegistro dato);
nodoArbol* insertar(nodoArbol* arbol,stRegistro dato);
nodoArbol* alta(nodoArbol* arbol,stRegistro dato);
nodoArbol * buscar(nodoArbol* arbol,int dato);
nodoDeportista* inicLista();
nodoDeportista* crearNodoLista(deportista dato);
nodoDeportista* agregarPpio(nodoDeportista* lista,deportista dato);
deportista transforma(stRegistro dato);
stRegistro crearRegistro();
void crearArchivo(char archivo[]);
void leerArchivo(char archivo[]);
void mostrarRegistro(stRegistro dato);
nodoArbol * pasarArchivoToArbol(nodoArbol* arbol,char archivo[]);
void inOrder(nodoArbol* arbol);
void mostrarLista(nodoDeportista* lista);
void crearArchivoLista(nodoDeportista* lista,char archivo[]);
void pasarArboltoArchivo(nodoArbol* arbol);
void leerArchivoLista(char archivo[]);

int main()
{
    //nodoArbol* arbol=inicArbol();
    //crearArchivo("hola.bin");
    //leerArchivo("hola.bin");
    //arbol=pasarArchivoToArbol(arbol,"hola.bin");
    //inOrder(arbol);
    //pasarArboltoArchivo(arbol);
    leerArchivoLista("Handball.bin");

    return 0;
}

nodoArbol* inicArbol()
{
    return NULL;
}
nodoArbol * crearNodoArbol(stRegistro dato)
{
    nodoArbol* aux=(nodoArbol*)malloc(sizeof(nodoArbol));
    strcpy(aux->deporte,dato.deporte);
    aux->idDeporte=dato.idDeporte;
    aux->listaDeportistas=inicLista();
    aux->izq=NULL;
    aux->der=NULL;
    return aux;
}
nodoArbol* insertar(nodoArbol* arbol,stRegistro dato)
{
    if (arbol==NULL)
        arbol=crearNodoArbol(dato);
    else
    {
        if (dato.idDeporte>arbol->idDeporte)
            arbol->der=insertar(arbol->der,dato);
        else
            arbol->izq=insertar(arbol->izq,dato);
    }
    return arbol;
}
nodoArbol* alta(nodoArbol* arbol,stRegistro dato)
{
    nodoArbol* aux=buscar(arbol,dato.idDeporte);
    if (aux==NULL)
    {
        arbol=insertar(arbol,dato);
    }
    aux=buscar(arbol,dato.idDeporte);
    aux->listaDeportistas=agregarPpio(aux->listaDeportistas,transforma(dato));
    return arbol;
}
nodoArbol * buscar(nodoArbol* arbol,int dato)
{
    nodoArbol* rta=NULL;
    if (arbol!=NULL)
    {
        if (dato==arbol->idDeporte)
            rta=arbol;
        else
            if (dato>arbol->idDeporte)
                rta=buscar(arbol->der,dato);
            else
                rta=buscar(arbol->izq,dato);
    }
    return rta;
}

nodoDeportista* inicLista()
{
    return NULL;
}

nodoDeportista* crearNodoLista(deportista dato)
{
    nodoDeportista * aux=(nodoDeportista*)malloc(sizeof(nodoDeportista));
    aux->dato=dato;
    aux->siguiente=NULL;
    return aux;
}
nodoDeportista* agregarPpio(nodoDeportista* lista,deportista dato)
{
    nodoDeportista * nuevoNodo=crearNodoLista(dato);
    if (lista!=NULL)
    {
        nuevoNodo->siguiente=lista;
    }
    lista=nuevoNodo;
    return lista;
}
deportista transforma(stRegistro dato)
{
    deportista aux;
    strcpy(aux.nombre,dato.nombre);
    strcpy(aux.apellido,dato.apellido);
    aux.edad=dato.edad;
    return aux;
}
stRegistro crearRegistro()
{
    stRegistro aux;
    printf("Ingrese Nombre\n");
    fflush(stdin);
    gets(aux.nombre);
    printf("Ingrese Apellido\n");
    fflush(stdin);
    gets(aux.apellido);
    printf("Ingrese Edad\n");
    fflush(stdin);
    scanf("%i",&aux.edad);
    printf("Ingrese Deporte\n");
    fflush(stdin);
    gets(aux.deporte);
    printf("Ingrese Id del Deporte\n");
    fflush(stdin);
    scanf("%i",&aux.idDeporte);
    return aux;
}
void crearArchivo(char archivo[])
{
    FILE * archi=fopen(archivo,"ab");
    int parar=0;
    stRegistro aux;
    while (parar==0)
    {
        aux=crearRegistro();
        fwrite(&aux,sizeof(stRegistro),1,archi);
        printf("Desea ingresar mas datos, ingrese 0 para continuar\n");
        fflush(stdin);
        scanf("%i",&parar);
    }
    fclose(archi);
}
void leerArchivo(char archivo[])
{
    FILE * archi=fopen(archivo,"rb");
    stRegistro aux;
    while (!feof(archi))
    {
        fread(&aux,sizeof(stRegistro),1,archi);
        if (!feof(archi))
            mostrarRegistro(aux);
    }
    fclose(archi);
}
void mostrarRegistro(stRegistro dato)
{
    printf("--------------------------\n");
    printf("Nombre: %s\n",dato.nombre);
    printf("Apellido: %s\n",dato.apellido);
    printf("Edad: %i\n",dato.edad);
    printf("Deporte: %s\n",dato.deporte);
    printf("Id del Deporte: %i\n",dato.idDeporte);
}
nodoArbol * pasarArchivoToArbol(nodoArbol* arbol,char archivo[])
{
    FILE * archi=fopen(archivo,"rb");
    stRegistro aux;
    while (!feof(archi))
    {
        fread(&aux,sizeof(stRegistro),1,archi);
        if (!feof(archi))
            arbol=alta(arbol,aux);
    }
    return arbol;
}
void inOrder(nodoArbol* arbol)
{
    if (arbol!=NULL)
    {
        inOrder(arbol->izq);
        printf("-----------------------------\n");
        printf("Deporte: %s\n",arbol->deporte);
        printf("Id Deportista: %i\n",arbol->idDeporte);
        mostrarLista(arbol->listaDeportistas);
        inOrder(arbol->der);
    }
}
void mostrarLista(nodoDeportista* lista)
{
    nodoDeportista* seg=lista;
    while(seg!=NULL)
    {
        printf("---------------------------------\n");
        printf("Nombre: %s\n",seg->dato.nombre);
        printf("Apellido: %s\n",seg->dato.apellido);
        printf("Edad: %i\n",seg->dato.edad);
        seg=seg->siguiente;
    }
}
void crearArchivoLista(nodoDeportista* lista,char archivo[])
{
    strcat(archivo,".bin");
    FILE * archi=fopen(archivo,"ab");
    deportista aux;
    nodoDeportista* seg=lista;
    while (seg!=NULL)
    {
        aux=seg->dato;
        fwrite(&aux,sizeof(deportista),1,archi);
        seg=seg->siguiente;
    }
    fclose(archi);
}
void pasarArboltoArchivo(nodoArbol* arbol)
{
    if (arbol!=NULL)
    {
        pasarArboltoArchivo(arbol->izq);
        crearArchivoLista(arbol->listaDeportistas,arbol->deporte);
        pasarArboltoArchivo(arbol->der);
    }
}
void leerArchivoLista(char archivo[])
{
    FILE * archi=fopen(archivo,"rb");
    deportista aux;
    while (!feof(archi))
    {
        fread(&aux,sizeof(deportista),1,archi);
        if (!feof(archi))
        {
            printf("---------------------------------\n");
            printf("Nombre: %s\n",aux.nombre);
            printf("Apellido: %s\n",aux.apellido);
            printf("Edad: %i\n",aux.edad);
        }
    }
    fclose(archi);
}













