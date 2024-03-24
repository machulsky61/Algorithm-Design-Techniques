#include <iostream>
#include <iostream>
#include "vector"
#include <bits/stdc++.h>
#include "tuple"
#include <queue>
#include <tuple>

using namespace std;


int INF = 100000;

struct eje{
    int inicio;
    int destino;
    int peso;
};


struct grafo{

    /* INV: para todo u, para todo i
     * ady[u][i_u] = (v,i_v) <=> ady[v][i_v] = (u,i_u)*/

    grafo(vector<tuple<int,int,int>> E, int n) {
        ady = vector<vector<eje>>(n);
        int u, v, w;
        for (auto e : E) {
            tie(u, v, w) = e;
            ady[u].push_back({u, v, w});
        }
    }

    vector<vector<eje>> ady;
};

vector<int> dijsktra(grafo & G, int s, int n){
    vector<bool> visitados (n,false);
    vector<int> d (n,INF); ///vector de distancias
    d[s] = 0; ///mi distancia a mi mismo es 0 en primera instancia
    priority_queue <pair<int, int> , vector<pair<int, int>>, greater<pair<int, int>> > Q; ///minHeap Q de tuplas <distancia, indiceVertice> ordenada por distancias
    Q.push(make_pair(0,s));

    while(!Q.empty()){
        pair<int, int> temp;
        temp =  Q.top(); ///asigno el primer elemento de mi heap
        int indiceActual = temp.second;
        Q.pop();
        visitados[indiceActual] = true;

        for(auto e : G.ady[indiceActual]){
            if(!visitados[e.destino]){ ///no quiero visitar los ya visitados
                ///relax
                int relax = d[indiceActual] + e.peso;
                if(relax < d[e.destino]){
                    d[e.destino] = relax;
                    Q.push(make_pair(relax,e.destino));
                }
            }
        }
    }
    return d;
}

int main() {
    int casos = 0;
    cin >> casos;
    for(int h = 0; h<casos; h++){
        int n, m, k, s, t;
        cin >> n >> m >> k >> s >> t;

        vector<tuple<int,int,int>> E;
        vector<tuple<int,int,int>> E_t;

        for(int i = 0; i<m; i++){ //armo el cjto de aristas E y E transpuesto
            int di,ci,li;
            cin >> di >> ci >> li;

            E.push_back({di,ci,li});
            E_t.push_back({ci,di,li});
        }

        vector<tuple<int,int,int>> K; // conjunto de las calles bidireccionales

        for(int j = 0; j<k; j++){
            int uj, vj, qj;
            cin >> uj >> vj >> qj;

            K.push_back({uj,vj,qj});
            K.push_back({vj,uj,qj});
        }

        grafo G = grafo(E,n+1);
        grafo G_t = grafo(E_t,n+1);

        vector<int> dS = dijsktra(G,s,n+1);
        vector<int> dT = dijsktra(G_t,t,n+1);

        int min = dS[t];

        for(auto & e : K){
            if(dS[get<0>(e)] == INF || dT[get<1>(e)] == INF){
                continue;
            }else{
                int dK = dS[get<0>(e)] + get<2>(e) + dT[get<1>(e)];
                if(dK < min){
                    min = dK;
                }
            }
        }
        if(min == dS[t+1]){
            cout << -1 << endl;
        }else{
            cout << min << endl;
        }
//        cout << "distS = ";
//        for(int i = 1; i<n+1; i++){
//            cout << dS[i] << " ";
//        }
//        cout << endl;
//
//        cout << "distT = ";
//        for(int i = 1; i<n+1; i++){
//            cout << dT[i] << " ";
//        }
//        cout << endl;
    }
}
