#include <bits/stdc++.h>

using namespace std;

// Conjunto de aristas

vector<pair<int,int>> grafo;

// y si es pesado?

struct arista {
    int v;
    int w;
    int peso;
};

vector<arista> grafo;

/* a) $N$ se representa con una secuencia (vector o lista) que en cada posición $v$ tiene el conjunto $N(v)$ implementado sobre una secuencia (lista o vector).
 * Cada vértice es una estructura que tiene un índice para acceder en $O(1)$ a $N(v)$.
 * Esta representación se conoce comúnmente como \emph{lista de adyacencias}.*/

using grafo = vector<vector<int>>;

//y si es pesado?
struct eje{
    int destino;
    int peso;
};

using grafo = vector<vector<eje>>;

/* b) ídem anterior, pero cada $w \in N(v)$ se almacena junto con un índice a la posición que ocupa $v$ en $N(w)$. Esta representación también se conoce como \emph{lista de adyacencias}, pero tiene información para implementar operaciones dinámicas. */


struct eje{
    int destino;
    int indice;
};

struct grafo{

    /* INV: para todo u, para todo i
     * ady[u][i_u] = (v,i_v) <=> ady[v][i_v] = (u,i_u)*/

    grafo(vector<pair<int,int>> E, int n) {
        ady = vector<vector<eje>>(n);
        int u, v;
        for (auto e : E) {
            tie(u, v) = e;
            ady[u].push_back({v, ady[v].size()});
            ady[v].push_back({u, ady[u].size() - 1});
        }
    }

    void borrar_eje(int v, int i_v){
        ady[v][i_v] = ady[v].back();
        ady[v].pop_back();

        if(i_v < ady[v].size()){
            //rompi el invariante! :(

            int u = ady[v][i_v].destino;
            int i_u = ady[v][i_v].indice;
            ady[u][i_u].indice = i_v;
            //invariante reestablecido :)
        }
    }

    void borrar_vertice(int u){
        for(int i_u = 0; i_u < ady[u].size(); i_u++)
            borrar_eje(ady[u][i_u].destino,ady[u][i_u].indice);
        ady[u].clear();
    }

    vector<vector<eje>> ady;
};


/* c) $N(v)$ se representa con un vector que en cada posición $i$ tiene un vector booleano $A_i$ con $|V(G)|$ posiciones tal que $A_i[j]$ es verdadero si y solo si $i$ es adyacente a $j$.
        Esta representación se conoce comúnmente como \emph{matriz de adyacencias}. */

using grafo = vector<vector<bool>>;

//y si es pesado?

using grafo = vector<vector<int>>;

/* $N(v)$ se representa con un vector que en cada posición tiene el conjunto $N(v)$ implementado con una tabla de hash.
 * Esta representación es un mix entre las representaciones clásicas de matriz de adyacencias y lista de adyacencias. */

using grafo = vector<unordered_set<int>>;

//y si es pesado?

using grafo = vector<unordered_map<int,int>>;


