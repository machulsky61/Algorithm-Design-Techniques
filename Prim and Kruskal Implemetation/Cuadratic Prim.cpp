/**
 * CSES Problem 1675: Road Reparation
 * https://cses.fi/problemset/task/1675/
 * (Para Algoritmos 3 - Implementación Cuadrática de Prim)
 * (Nota: Si se la trata de enviar al juez falla por timeout)
 * Author: Pablo Terlisky
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

using Costo = unsigned long int;
using Vertice = unsigned int;
using Distancia = unsigned long int;
using VerYCos = pair<Vertice,Costo>;


//Fución para buscar el elemento de Distancia más chica que no haya sido visitado aún
int dist_minima_no_visitado(const vector<Distancia>& las_distancias,const vector<bool>& los_visitados) {
    //Puedo usar directamente los valores del 0, siempre existen pues el vector tiene una posición extra
    Distancia distancia_minima=numeric_limits<Distancia>::max();
    int indice_minimo=0;
    for (auto i=1u;i<las_distancias.size();i++) {
        if (las_distancias[i]<distancia_minima and !los_visitados[i]) {
            distancia_minima = las_distancias[i];
            indice_minimo=i;
        }
    }
    return indice_minimo;
}

int main() {
    size_t n,m;
    cin >> n >> m;

    //Generación del grafo
    //Tamaño n+1 para indexar desde 1
    vector<vector<VerYCos>> grafo(n+1);

    //Inicializo a 0, el valor que no voy a usar
    Vertice raiz=0;

    //Construcción del grafo (incluyendo el costo de cada arista)
    for (auto i=0u;i<m;i++) {
        Vertice v,w; Costo c; cin >> v >> w >> c;
        if (i==0) {                    //Me guardo el primer vértice de la primera
            raiz=v;                    //arista para que sea la raíz del árbol.
        }
        grafo[v].push_back(VerYCos(w,c));
        grafo[w].push_back(VerYCos(v,c));
    }

    //Utilizamos los siguientes vectores:
    //  visitado[i] : verdadero cuando i ya fue visitado
    //  distancia[i]: la 'distancia' es el costo de la arista más
    //                barata que conecta a i con el árbol actual
    //                (Y es infinita si aún no está a distancia de 
    //                 una arista). En CLRS este valor es llamado "key"
    //  padre[i]    : indice del padre de i en el AGM generado
    //(En todos los vectores la posición 0 tiene valores inválidos)
    vector<bool> visitado(n+1,false);
    vector<Distancia> distancia(n+1,numeric_limits<Distancia>::max()); //Inicializa en Infinito
    vector<Vertice> padre(n+1,0);   //Dado que 0 no es un vértice, se usa como valor de padre inválido

    //Llevo la cuenta del costo total (es lo que pide este problema)
    unsigned long int costo_total = 0;

    //Enraizamos Prim en algún vértice (había tomado el primero de la primera arista)
    distancia[raiz]=0;
    padre[raiz]=raiz; //Tomo la convención de que el padre de la raiz es la propia raiz

    //Por n iteraciones, agrego al árbol actual el vértice de mínima 'distancia'.
    for (auto i=0u;i<n;i++) {
        int v = dist_minima_no_visitado(distancia,visitado);
        visitado[v] = true;
        costo_total+=distancia[v];
        for (auto& [w,c] : grafo[v]) {
            if (distancia[w]>c) {          //Si esta arista es la más barata para 
                distancia[w]=c;            //llegar del árbol a w, se baja su distancia
                padre[w]=v;                //y se marca que actualmente v es el padre de w 
            }
        }
    }

    //Salida en formato CSES
    //Si en algún momento me dio que el vértice de mínima
    //distancia era el 0 (que tiene infinito) es porque el
    //grafo no era conexo
    if (visitado[0]) {
        cout << "IMPOSSIBLE";
    } else {
        cout << costo_total;
    }

    return 0;
}
