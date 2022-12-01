/*
-Diego Saavedra
-Nicolás Vázquez
-Pedro Peón
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/time.h>
#include <time.h>
#include <stdbool.h>

struct nodo {
    int elem;
    int num_repeticiones;
    struct nodo *izq, *der;
};
typedef struct nodo *posicion;
typedef struct nodo *arbol;

struct mediciones{
    double tiempo;
    double subestimada;
    double ajustada;
    double sobrestimada;
};

double microsegundos(){
/* obtiene la hora del sistema en microsegundos */
    struct timeval t;
    if (gettimeofday(&t, NULL) < 0 )
        return 0.0;
    return (t.tv_usec + t.tv_sec * 1000000.0);
}

void inicializar_semilla(){
    srand(time(NULL));
}

void aleatorio(int v [], int n){
/* se generan números pseudoaleatorio entre -n y +n */
    int i, m=2*n+1;
    for (i=0; i < n; i++)
        v[i] = (rand() % m) - n;
}

static struct nodo *crearnodo(int e) {
    struct nodo *p = malloc(sizeof(struct nodo));
    if (p == NULL) {
        printf("memoria agotada\n"); exit(EXIT_FAILURE);
    }
    p->elem = e;
    p->num_repeticiones = 1;
    p->izq = NULL;
    p->der = NULL;
    return p;
}

arbol insertar(int e, arbol a){
    if (a == NULL)
        return crearnodo(e);
    else if (e < a->elem)
        a->izq = insertar(e, a->izq);
    else if (e > a->elem)
        a->der = insertar(e, a->der);
    else
        a->num_repeticiones++;
    return a;
}

arbol creararbol(){
    arbol tree = NULL;
    return tree;
}


int esarbolvacio(arbol tree){
    if (tree == NULL)
        return 1;
    else
        return 0;
}

posicion hijoizquierdo(arbol tree){
    if(tree != NULL){
        return tree -> izq;
    }
    else return NULL;
}

posicion hijoderecho(arbol tree){
    if(tree != NULL){
        return tree -> der;
    }
    else return NULL;
}

int elemento(posicion pos){ //Precondicion: no admite nodos nulos.
    return pos -> elem;
}   //No se puede devolver -1 porque seria un elemento valido.

posicion buscar(int elem, arbol tree){
    if(tree == NULL)
        return NULL;
    if(elem == tree->elem)
        return tree;
    else if ((elem < tree->elem) && (tree->izq != NULL))
        return buscar(elem, tree->izq);
    else if ((elem > tree->elem) && (tree->der != NULL))
        return buscar(elem, tree->der);
    else
        return NULL;
}

arbol eliminararbol(arbol tree){
    if (tree != NULL){
        eliminararbol(tree->izq);
        eliminararbol(tree->der);
        free(tree);
    }
    return NULL;
}

int numerorepeticiones(posicion pos){
    if(pos != NULL){
        return pos -> num_repeticiones;
    }
    else return -1;
}

int altura(arbol tree){
    int heigh;

    if (tree == NULL)
        heigh = -1;
    else
        heigh = 1+fmax(altura(tree->izq), altura(tree->der));
    return heigh;
}

void visualizar(arbol tree){
    printf("(");
    if(tree != NULL){
        if(tree->izq != NULL)
            visualizar(tree->izq);
        printf("%d", tree->elem);
        if(tree->der != NULL)
            visualizar(tree->der);
    }
    printf(")");
}

void mostrar(arbol tree){
    if (tree == NULL)
        printf("arbol vacio: ");
    else
        printf("arbol: ");
    visualizar(tree);
}

arbol testInsertar(arbol tree){
    tree = insertar(3, tree); //insertamos elementos
    printf("Inserto un 3\n");
    tree = insertar(1, tree);
    printf("Inserto un 1\n");
    tree = insertar(2, tree);
    printf("Inserto un 2\n");
    tree = insertar(5, tree);
    printf("Inserto un 5\n");
    tree = insertar(4, tree);
    printf("Inserto un 4\n");
    tree = insertar(5, tree);
    printf("Inserto un 5\n");
    return tree;
}

void testBusqueda(arbol tree){  
    posicion posBusqueda;
    
    posBusqueda = buscar(1, tree);
    printf("busco 1 y encuentro %d repetido %d veces\n", elemento(posBusqueda),
            numerorepeticiones(posBusqueda));
    posBusqueda = buscar(2, tree);
    printf("busco 2 y encuentro %d repetido %d veces\n", elemento(posBusqueda),
            numerorepeticiones(posBusqueda));
    posBusqueda = buscar(3, tree);
    printf("busco 3 y encuentro %d repetido %d veces\n", elemento(posBusqueda),
            numerorepeticiones(posBusqueda));
    posBusqueda = buscar(4, tree);
    printf("busco 4 y encuentro %d repetido %d veces\n", elemento(posBusqueda),
            numerorepeticiones(posBusqueda));
    posBusqueda = buscar(5, tree);
    printf("busco 5 y encuentro %d repetido %d veces\n", elemento(posBusqueda),
            numerorepeticiones(posBusqueda));
}

void test(){
    arbol tree;
    int heigh;

    tree = creararbol(); //crear arbol
    mostrar(tree);
    printf("\n");

    heigh = altura(tree); //altura vacio
    printf("Altura del arbol: %d\n", heigh);
    
    tree = testInsertar(tree);
    mostrar(tree); //visualizamos arbol
    printf("\n");

    heigh = altura(tree);//altura nuevo arbol
    printf("Altura del arbol: %d\n", heigh);

    testBusqueda(tree);

    tree = eliminararbol(tree);
    printf("Borro todos los nodos liberando la memoria\n");
    mostrar(tree);
    printf("\n");
}

double medir_tiempo_insercion(int n){
    double tiempo,instante_inicial,instante_final;
    int v[n], i;
    arbol tree;

    tree = creararbol();
    aleatorio(v, n);
    instante_inicial = microsegundos();
    for (i=0; i<n; i++)
        tree = insertar(v[i], tree);
    instante_final = microsegundos();
    tiempo = instante_final - instante_inicial;
    tree = eliminararbol(tree);

    return tiempo;
}

double medir_tiempo_busqueda(int n){
    double tiempo,instante_inicial,instante_final,tiempo_busqueda,
        tiempo_sin_busq;
    int v[n],i, j, k, busqueda[n];
    int repeticiones = 1000;
    int umbral = 500;
    arbol tree;

    tree = creararbol();
    aleatorio(v, n);
    aleatorio(busqueda, n);
    for (i=0; i<n; i++)
        tree = insertar(v[i], tree);
    instante_inicial = microsegundos();
    for (i=0; i<n; i++)
        buscar(busqueda[i], tree);
    instante_final = microsegundos();
    tiempo = instante_final - instante_inicial;
    tree = eliminararbol(tree);

    if (tiempo < umbral){
        instante_inicial = microsegundos();
        for(i=0; i < repeticiones; i++){
            aleatorio(v, n);
            aleatorio(busqueda, n);
            for (j=0; j<n; j++)
                tree = insertar(v[i], tree);
            for (k=0; k<n; k++)
                buscar(busqueda[i], tree);
            tree = eliminararbol(tree);
        }
        instante_final = microsegundos();
        tiempo_busqueda = (instante_final - instante_inicial) / repeticiones;
        instante_inicial = microsegundos();
        for(i=0; i < repeticiones; i++){
            aleatorio(v, n);
            aleatorio(busqueda, n);
            for (j=0; j<n; j++)
                tree = insertar(v[i], tree);
            tree = eliminararbol(tree);
        }
        instante_final = microsegundos();
        tiempo_sin_busq =(instante_final - instante_inicial)/repeticiones;
        tiempo = tiempo_busqueda - tiempo_sin_busq;
    }

    return tiempo;
}

void cabecera_fun(double (*medir)(int n)){
    if (medir == medir_tiempo_busqueda)
        printf("%s\n", "Busqueda de n elementos");
    else
        printf("%s\n", "Insercion de n elementos");
}

struct mediciones calcular_cota(int n, double (*medir)(int n)){
    struct mediciones cotas;
    cotas.tiempo = medir(n);
    if (medir == medir_tiempo_busqueda){
        cotas.subestimada = cotas.tiempo/(n*log(n));
        cotas.ajustada = cotas.tiempo/pow(n, 1.22);
        cotas.sobrestimada = cotas.tiempo/pow(n, 1.31);
    }
    else{
        cotas.subestimada = cotas.tiempo/(n*log(n));
        cotas.ajustada = cotas.tiempo/pow(n, 1.24);
        cotas.sobrestimada = cotas.tiempo/pow(n, 1.3);
    }
    return cotas;
}

void crear_tabla_simple(){
    int i, n = 500, umbral = 500, tiempoMin = 0, tiempoMax = 0;
    struct mediciones cotas_ins, cotas_bus;

    printf("%12s%16.9s%16.9s\n","n","t_ins (n)","t_bus (n)");
    for(i = 0 ; (i < 15) && tiempoMax < 1000000 ; i++){
        cotas_ins = calcular_cota(n, medir_tiempo_insercion);
        cotas_bus = calcular_cota(n, medir_tiempo_busqueda);
        tiempoMax = fmax(cotas_ins.tiempo, cotas_bus.tiempo);
        tiempoMin = fmin(cotas_ins.tiempo, cotas_bus.tiempo);
        if(tiempoMin > umbral){
            printf("%12d%16.4f%16.4f\n", n, cotas_ins.tiempo,
                   cotas_bus.tiempo);
        }
        n *= 2;
    }
    printf("\n");
}

void crear_tabla_cotas(double (*medir)(int n)){
    int i, n = 500, umbral = 500, tiempo = 0;
    struct mediciones cotas;

    cabecera_fun(medir);
    printf("%12s%15.4s%15.9s%15.9s%15.9s\n","n","T(n)","T(n)/f(n)",
           "T(n)/g(n)","T(n)/h(n)");
    for(i = 0 ; (i < 15) && tiempo < 1000000 ; i++){
        cotas = calcular_cota(n, medir);
        tiempo = cotas.tiempo;
        if(tiempo < umbral){
            if(medir == medir_tiempo_busqueda){
                printf("*%12d%15.3f%15.7f%15.7f%15.7f\n", n, cotas.tiempo,
                       cotas.subestimada, cotas.ajustada, cotas.sobrestimada);
            }
        }
        else{
           printf(" %12d%15.3f%15.7f%15.7f%15.7f\n", n, cotas.tiempo,
                  cotas.subestimada, cotas.ajustada, cotas.sobrestimada);
        }
        n *= 2;
    }
    printf("\n");
}

void repetir_tablas(){
    int i;
    
    printf("\n");
    for(i = 0; i < 3; i++)
        crear_tabla_simple();
    for(i = 0; i < 3; i++)
        crear_tabla_cotas(medir_tiempo_insercion);
    for(i = 0; i < 3; i++)
        crear_tabla_cotas(medir_tiempo_busqueda);
}

int main (){
    inicializar_semilla();
    test();
    repetir_tablas();

    return 0;
}
