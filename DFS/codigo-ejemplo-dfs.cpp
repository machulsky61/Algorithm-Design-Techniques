
#include<iostream>
#include<vector>
#include<stack>

using namespace std;

//RECURSIVO
void dfs(vector<vector<int>>& ady, int source, vector<bool>& visitado) {
    visitado[source] = true;
    for (int u : ady[source]) {
        if (!visitado[u]) {
            dfs(ady, u, visitado);
        }
    }
}

//ITERATIVO
void dfs_iter(const vector<vector<int>>& ady, const int source, vector<bool>& visitado){
    stack<int> pila; pila.push(source);
    while (!pila.empty()) {
        int u = pila.top();
        pila.pop();
        if (!visitado[u]) {
            visitado[u] = true;
        }
        for (int w : ady[u]) {
            if (!visitado[w]) {
                pila.push(w);
            }
        }
    }
}

//RECURSIVO CON TIMER Y COLORES
void dfs_timer(const vector<vector<int>>& ady,const int source, int & current_time, vector<int>& time_in, vector<int>& color) {
    color[source] = 1;
    time_in[source] = current_time++;
    for (int u : ady[source]) {
        if (color[u]==0) {
            dfs_timer(ady, u, current_time, time_in, color);
        }
    }
    color[source]=2;
}

//RECURSIVO CON PARENT
void dfs_parent(vector<vector<int>>& ady, int source, vector<int>& parents) {
    for (int u : ady[source]) {
        if (parents[u]==-1) {
            parents[u]=source;
            dfs_parent(ady, u, parents);
        }
    }
}

//DETECCIÓN DE PUENTES
int dp(const vector<vector<int>>& ady, int source, const vector<int>& time_in, const vector<int>& parents, vector<bool>& puente_con_parent) {
    int cantidad = 0;
    for (int u : ady[source]) {
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


int main() {
    //En este ejemplo, tomo por entrada n, m, y una raíz
    int n,m,s; cin >> n >> m >> s;
    //Creo un vector de dimensión n+1 sólo para poder usar el índice 1 en el primer vértice, se ignora 
    //                                                                  la posición 0 en los resultados
    vector<vector<int>> grafo(n+1,vector<int>());
    for (int i=0;i<m;i++) {
        int v,w;cin>>v>>w;
        grafo[v].push_back(w);
        grafo[w].push_back(v);
    }

    //Versión con vector de visitados
    vector<bool> visitados(n,false);
    dfs(grafo, s, visitados);
    //dfs_iter(grafo, s, visitados);

    //Versión con vector de padres
    vector<int> padres(n+1,-1);
    //Establezco que el padre del vértice que va a ser la raíz es él mismo
    padres[s]=s;
    dfs_parent(grafo, s, padres);

    //Genero vector de tiempos
    int tiempo = 0;
    vector<int> tiempos(n+1,0);
    vector<int> colores(n+1,0);
    dfs_timer(grafo, s, tiempo, tiempos, colores);

    //Para detectar puentes
    vector<bool> arista_puente(n+1,false);
    dp(grafo, s, tiempos, padres, arista_puente);

    //Si busco encontrar los puentes en todas las componentes conexas
    for (int i = 0;i<n+1;i++) {
        if(padres[i]==-1) {
            padres[i]=i;
            dfs_parent(grafo, i, padres);
            dfs_timer(grafo, i, tiempo, tiempos, colores);
            dp(grafo, i, tiempos, padres, arista_puente);
        }
    }

    cout << "grafo: " << endl;
    for (int i=0;i<n+1;i++) {
        cout << i << ":";
        for (auto u : grafo[i]) {
            cout << u << " ";
        }
        cout << endl;
    }
    cout << endl;

    cout << "visitados: ";
    for (int i=0;i<n+1;i++) {
        cout << i << ":" << visitados[i] << " ";
    }
    cout << endl;

    cout << "padres: ";
    for (int i=0;i<n+1;i++) {
        cout << i << ":" << padres[i] << " ";
    }
    cout << endl;

    cout << "timer: ";
    for (int i=0;i<n+1;i++) {
        cout << i << ":" << tiempos[i] << " ";
    }
    cout << endl;

    cout << "colores: ";
    for (int i=0;i<n+1;i++) {
        cout << i << ":" << colores[i] << " ";
    }
    cout << endl;

    cout << "arista puente? (con su parent): ";
    for (int i=0;i<n+1;i++) {
        cout << i << ":" << arista_puente[i] << " ";
    }
    cout << endl;

    return 0;
}