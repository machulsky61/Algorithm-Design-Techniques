#include <iostream>
#include <vector>
#include <bits/stdc++.h>
#include<stack>

using namespace std;

vector<long long int> orden;
vector<long long int> componentes;


//RECURSIVO
void dfs1(vector<vector<long long int>>& ady, long long int source, vector<bool>& visitado) {
    visitado[source] = true;
    for (long long int u : ady[source]) {
        if (!visitado[u]) {
            dfs1(ady, u, visitado);
        }
    }
    orden.push_back(source);
}

//RECURSIVO
void dfs2(vector<vector<long long int>>& ady, long long int source, vector<bool>& visitado) {
    visitado[source] = true;
    componentes.push_back(source);

    for (long long int u : ady[source]) {
        if (!visitado[u]) {
            dfs2(ady, u, visitado);
        }
    }
}

int main() {
    long long int n,m;
    cin >> n >> m;

    vector<vector<long long int>> g(n+1, vector<long long int>());
    vector<vector<long long int>> g_t (n+1, vector<long long int>());

    for(long long int i=0;i<m;i++){//leo la entrada y creo G y G Transpuesto
        long long int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g_t[b].push_back(a);
    }

    //Versión con vector de visitados
    vector<bool> visitados(n+1,false);
    for(long long int i = 1; i<n+1;i++){//hago 1er dfs y guardo el orden de exploracion
        if(!visitados[i]){
            dfs1(g, i, visitados);
        }
    }
    visitados.assign(n+1, false); //vacio mi vector de visitados
    reverse(orden.begin(), orden.end());//invierto el orden de exploracion hallado x el 1er dfs

    for(long long int i=1; i<n+1; i++){//hago mi 2do dfs y armo el grafo condensado
        if(!visitados[i]){
            dfs2(g_t,i,visitados);

            componentes.clear();
        }
    }

    //armo grafo condensado

    vector<long long int> roots(n+1,0);
    vector<long long int> root_nodes;
    vector<vector<long long int>> g_scc(n+1);

    visitados.assign(n, false); //vacio mi vector de visitados
    for(auto v : orden){
        if(!visitados[v]){
            dfs2(g_t,v,visitados);

            long long int raiz = componentes.front();
            for(auto u : componentes){
                roots[u] = raiz;
            }
            root_nodes.push_back(raiz);

            componentes.clear();
        }
    }

    for(long long int v=1; v<n+1; v++){
        for(auto u : g[v]){
            long long int root_v = roots[v];
            long long int root_u = roots[u];

            if(root_u != root_v){
                g_scc[root_v].push_back(root_u);
            }
        }
    }


    //ahora quiero devolver las raices del bosque dfs

    vector<bool> sol(n+1, true);

    for(int i = 1; i<n+1;i++){
        for(auto v : g_scc[i]){
            sol[v] = false;
        }
    }
    for(int i = 1; i<roots.size(); i++){
        if(roots[i] == i){
            continue;
        }else{
            sol[i] = false;
        }
    }
    int solve = 0;
    for(int i = 1; i<sol.size(); i++){
        if(sol[i]){
            solve++;
        }
    }
    cout << solve;
    cout << endl;
    for(int i = 1; i<sol.size(); i++){
        if(sol[i]){
            cout << i << " ";
        }
    }
    cout << endl;
}
