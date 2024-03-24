#include <iostream>
#include "vector"
#include <bits/stdc++.h>

using namespace std;

struct eje{
    long long int destino;
    long long int indice;
};



struct grafo{

    /* INV: para todo u, para todo i
     * ady[u][i_u] = (v,i_v) <=> ady[v][i_v] = (u,i_u)*/

    grafo(vector<pair<long long int,long long int>> E, int n) {
        ady = vector<vector<eje>>(n);
        long long int u, v;
        for (auto e : E) {
            tie(u, v) = e;
            ady[u].push_back({v,ady[v].size() });
            ady[v].push_back({u,ady[u].size() - 1});
        }
    }
    vector<vector<eje>> ady;
};

long long int n,m;


long long int dp(const vector<vector<long long int>>& ady, long long int source, const vector<long long int>& time_in, const vector<long long int>& parents, vector<bool>& puente_con_parent) {
    long long int cantidad = 0;
    for (long long int u : ady[source]) {
        if (parents[u]==source) {
            cantidad +=dp(ady, u, time_in, parents, puente_con_parent);
        } else {
            if (time_in[source]>time_in[u] and parents[source]!=u) { //(source,u) es backedge que sube
                cantidad++;
            }
            if (time_in[source]<time_in[u]) { //(source,u) es backedge que viene de abajo
                cantidad--;
            }
        }
    }
    if (cantidad==0 and parents[source]!=source) {
        puente_con_parent[source] = true;
    }
    return cantidad;
}


//RECURSIVO CON PARENT
void dfs_parent(vector<vector<long long int>>& ady, long long int source, vector<long long int>& parents) {
    for (long long int u : ady[source]) {
        if (parents[u]==-1) {
            parents[u]=source;
            dfs_parent(ady, u, parents);
        }
    }
}

//RECURSIVO CON TIMER Y COLORES
void dfs_timer(const vector<vector<long long int>>& ady,const long long int source, long long int & current_time, vector<long long int>& time_in, vector<long long int>& color) {
    color[source] = 1;
    time_in[source] = current_time++;
    for (long long int u : ady[source]) {
        if (color[u]==0) {
            dfs_timer(ady, u, current_time, time_in, color);
        }
    }
    color[source]=2;
}


void pintar2(vector<vector<long long int>>& ady, long long int source, vector<long long int>& parents, vector<long long int> & compConexa, long long int actual) {
    for (long long int u : ady[source]) {
        if (parents[u]==-1) {
            compConexa[u] = actual;
            parents[u]=source;
            pintar2(ady,u,parents,compConexa,actual);
        }
    }
}

long long int choose(long long int h, long long int k){
    if(h==0){
        return 0;
    }
    if(k == 0){
        return 1;
    }else{
        return (h * choose(h - 1, k - 1)) / k;
    }
}

int main() {
    cin >> n >> m;
    vector<vector<long long int>> grafo(n+1, vector<long long int>());
    for(long long int i=0; i<m; i++){
        long long int v,w;
        cin >> v >> w;
        grafo[v].push_back(w);
        grafo[w].push_back(v);
    }
    vector<bool> arista_puente(n+1, false);
    long long int tiempo=0;
    vector<long long int> tiempos(n + 1, 0);
    vector<long long int> colores(n + 1, 0);
    vector<long long int> padres(n + 1, -1);
     for (int i = 0; i < n + 1; i++) {
         if (padres[i] == -1) {
             padres[i] = i;
             dfs_parent(grafo, i, padres);
             dfs_timer(grafo, i, tiempo, tiempos, colores);
             dp(grafo, i, tiempos, padres, arista_puente);
         }
     }


     vector<vector<long long int>> sinPuentes(n + 1, vector<long long int>());
     for (int i = 0; i < n + 1; ++i) {
         long long int v, w;
         if (!arista_puente[i]) {
             v = i;
             w = padres[i];
             sinPuentes[v].push_back(w);
             sinPuentes[w].push_back(v);
         }
     }


     for(long long int i = 0; i < padres.size(); ++i) {
         padres[i] = -1;
     }
     vector<long long int> compConexa(n + 1, 0);
     long long int actual = 0;
     for (long long int i = 0; i < n + 1; ++i) {
         if (padres[i] == -1) {
             actual++;
             compConexa[i] = actual;
             padres[i] = i;
             pintar2(sinPuentes, i, padres, compConexa, actual);
         }
     }
     vector<long long int> cantNodosPorCC(n+1,0);
     for(int i=0; i<compConexa.size(); i++){
                 cantNodosPorCC[compConexa[i]]++;
     }

     long long int nCdos = choose(n,2);
     long double acum = 0;
     for(int i=0; i<cantNodosPorCC.size() ;i++){
         acum += choose(cantNodosPorCC[i],2);
     }
     cout << setprecision(5) << 1-(acum/nCdos);

}

