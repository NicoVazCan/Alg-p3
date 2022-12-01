Práctica 3 Algoritmos Ingeniería Informática 2020/2021

Autor:
(QUITAR LOS DEMAS NOMBRES)
-Diego Saavedra
-Nicolás Vázquez
-Pedro Peón


En este informe queda reflejado la complejidad computacional de los algoritmos
inserción de n números enteros aleatorios en el rango [−n ... + n] en un árbol
vacío y búsqueda de n elementos en un árbol binario de búsqueda de n nodos.
En las tablas quedan represantados el número de elementos de los árboles y los
tiempos de ejecución, asi como las cotas ajustada, subestimada y sobreestimada.
(CAMBIAR POR VUESTROS PCs)
Estos cálculos se han realizado en un hp pavilion notebook con un procesador 
Intel corei7-6700HQ, CPU con 2.6 GHz y con una Memoria Ram de 15.6Gb DDR4.

Todos los tiempos indicados en las tablas estan en microsengundos.

Todas las tablas han sido ejecutadas 3 veces y con un número de filas variable,
empezando cuando el tiempo de ejecución supera los 500us (salvo en la búsqueda)
y finalizando cuando supera 1000000us para mayor precisión y con el objetivo de
evitar el mayor número de valores anómalos.

* Estes tiempos de busqueda son inferiores a 500 microsegundos por lo que
entraron en un bucle de 1000 interacciones y se calculó su tiempo medio.
** Valores anómalos.

--------------------------------------------------------------------------------

Tiempos de insertar n elementos y buscar n elementos
    t_ins(n): tiempo de insercion de n elementos.
    t_bus(n): tiempo de busqueda de n elementos en un arbol de n nodo.

           n       t_ins (n)       t_bus (n)
        4000       1078.0000       1563.0000
        8000       2388.0000       3484.0000
       16000       5783.0000       8293.0000
       32000      13705.0000      15309.0000
       64000      29745.0000      34403.0000
      128000      76581.0000      94709.0000
      256000     192797.0000     244573.0000
      512000     445810.0000     574246.0000
     1024000    1114360.0000    1335517.0000


Cotas en el algoritmo de inserción de n elementos:
    f(n)=n*log(n)       (cota subestimada)
    g(n)=n^1.24         (cota ajustada)
    h(n)=n^1.3	        (cota sobreestimada)

Insercion de n elementos
           n           T(n)      T(n)/f(n)      T(n)/g(n)      T(n)/h(n)
        4000       1140.000      0.0343620      0.0389359      0.0236716
        8000       2543.000      0.0353698      0.0367718      0.0214452
       16000       5836.000      0.0376794      0.0357278      0.0199875
       32000      13966.000      0.0420724      0.0361981      0.0194257
       64000      32090.000      0.0453079      0.0352133      0.0181274
      128000      74260.000      0.0493339      0.0344996      0.0170366**
      256000     190105.000      0.0596324      0.0373918      0.0177126
      512000     448344.000      0.0666109      0.0373350      0.0169653
     1024000    1064284.000      0.0751010      0.0375220      0.0163556

La constante a la que tiende T(n)/g(n) es: 0.037



Cotas en el algoritmo de búsqueda de n elementos:
    f(n)=n*log(n)       (cota subestimada)
    g(n)=n^1.22         (cota ajustada)
    h(n)=n^1.31         (cota sobreestimada)

Busqueda de n elementos
           n           T(n)      T(n)/f(n)      T(n)/g(n)      T(n)/h(n)
        2000        652.000      0.0428896      0.0612338      0.0308957
        4000       1545.000      0.0465695      0.0622896      0.0295277
        8000       3442.000      0.0478737      0.0595718      0.0265316
       16000       8002.000      0.0516640      0.0594528      0.0248772
       32000      16592.000      0.0499832**    0.0529195**    0.0208043
       64000      40664.000      0.0574136      0.0556763      0.0205643
      128000      93983.000      0.0624367      0.0552399      0.0191692
      256000     248717.000      0.0780178      0.0627556      0.0204603**
      512000     574292.000      0.0853231      0.0622047      0.0190541
     1024000    1307213.000      0.0922432      0.0607828      0.0174926

La constante a la que tiende T(n)/g(n) es: 0.061


--------------------------------------------------------------------------------

Nos encontramos con que, aunque la complejidad teorica de ambos algoritmos es de 
n*log(n), al ejecutar los tiempos nos encontramos una complejidad empirica mayor
en ambos casos, siendo n^1.24 para la inserción y n^1.22 en la búsqueda.

Al realizar las mediciones de los tiempos de la funcion insertar, nos dimos
cuenta (tambien gracias al profesor) que era imposible medir con precision
tiempos inferiores a 500us al no poderse medir por separado la insercion y el
vaciado del arbol dentro del bucle, por lo que decidimos comenzar con un
numero de inserciones lo suficientemente grande para que el tiempo transcurrido
supere a 500us, al igual que luego hicimos con el numero de busquedas.

Si comparamos la forma de las dos funciones, a pesar de llevar acabo dos 
tareas totalmente diferentes, ambas comparten el mismo proceso para recorrer el
arbol por la rama mas ajustada al elemento introducido, diferenciadose 
solo en los siguientes casos: cuando encuentra un nodo con el mismo elemento 
(insertar aumenta la repeticion de ese elemento y buscar devuelve el nodo)
y cuando no lo encuentra (insertar crea un nodo y buscar falla). A parte de esto,
actualmente no podemos compararlos con otros algoritmos ya que no disponemos
de la información de algoritmos similares, así que no podemos estimar su 
eficiencia.

Tambien podemos notar la diferencia de tiempos entre las dos funciones, siendo
insertar algo mas rapida que buscar, con lo que podemos suponer que buscar no
ecuentra una gran parte de elementos demandados.
