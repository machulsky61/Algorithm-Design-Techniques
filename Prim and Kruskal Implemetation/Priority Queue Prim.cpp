/**
 * CSES Problem 1675: Road Reparation
 * https://cses.fi/problemset/task/1675/
 * (Para Algoritmos 3 - Implementación de Prim con cola de prioridad)
 * Author: Pablo Terlisky
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <queue>

using namespace std;

using Costo = unsigned long int;
using Vertice = unsigned int;
using Distancia = unsigned long int;
using VerYCos = pair<Vertice,Costo>;
using DisYVer = pair<Distancia,Vertice>;

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

    //Voy a contar los vértices que fuí agregando al árbol (la raíz ya está)
    unsigned int vertices_agregados = 1;

    //Enraizamos Prim en algún vértice (había tomado el primero de la primera arista)
    distancia[raiz]=0;
    padre[raiz]=raiz; //Tomo la convención de que el padre de la raiz es la propia raiz

    priority_queue<DisYVer, vector<DisYVer> , greater<DisYVer> > cola_vertices;

    cola_vertices.push(DisYVer(0,raiz));

    //En tanto la cola de vértices tenga elementos, tomo el primero que no haya
    //visitado y lo agrego al árbol, actualizando a sus vecinos.
    while (!cola_vertices.empty()) {
        Vertice v = cola_vertices.top().second;
        cola_vertices.pop();
        
        if(visitado[v]) continue;
       
        visitado[v] = true;
        costo_total+=distancia[v];
        vertices_agregados++;

        for (auto& [w,c] : grafo[v]) {
            if (!visitado[w] and distancia[w]>c) {  //Si esta arista es la más barata para 
                distancia[w]=c;                     //llegar del árbol a w, se baja su distancia
                padre[w]=v;                         //y se marca que actualmente v es el padre de w 
                cola_vertices.push(DisYVer(c,w));   //Notar que cada vez que actualizo la distancia
                                                    //de un vértice lo vuelvo a agregar a la cola.
                                                    //De todos modos, la primera aparición que tome
                                                    //será la de distancia mínima.
            }
        }
    }

    //Salida en formato CSES
    //Si mi árbol no terminó con n vértices, el
    //grafo no era conexo
    if (vertices_agregados<n) {
        cout << "IMPOSSIBLE";
    } else {
        cout << costo_total;
    }

    return 0;
}
