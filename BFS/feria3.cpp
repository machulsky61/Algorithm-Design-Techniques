#include <iostream>
#include <vector>
#include <deque>
#include <climits>
#include <algorithm>

using namespace std;

const int INF = INT_MAX;

vector<int> a;
vector<vector<int> > ady;
vector<int> res;
int n, m, k, s;


void fair(){

    // dist[i][j] es la distancia del producto i a la ciudad j (si j < n)
    vector<vector<int> > dist(k, vector<int>(n, INF));

    // agregamos las aristas hacia las ciudades del producto correspondiente
    vector<deque<int> > q(k);
    for(int i = 0; i < n; i++){
        q[a[i]].push_back(i);
        dist[a[i]][i] = 0;
    }

    res = vector<int>(n, 0); // costo total de la ciudad i
    vector<int> arrived(n, 1); // cantidad de productos que llegaron a la ciudad i

    bool fairs_done = false;
    while(!fairs_done){
        fairs_done = true;

        for(int prod = 0; prod < k; prod++){
            // avanzamos el producto desde una frontera a la siguiente
            deque<int> new_q;
            for(int v : q[prod]){ // por cada elemento en la frontera
                for(int u : ady[v]){ // expandimos sus vecinos
                    if(dist[prod][u] == INF){
                        dist[prod][u] = dist[prod][v] + 1;
                        new_q.push_back(u);
                        if(arrived[u] < s){
                            arrived[u] ++;
                            res[u] += dist[prod][u]; // no hizo falta el -1
                        }
                    }
                }
            }
            q[prod] = new_q;
            fairs_done &= new_q.empty();
        }
    }
}

int main(){
    cin >> n >> m >> k >> s;

    a = vector<int>(n);
    ady = vector<vector<int> >(n);

    for(int i = 0; i < n; i++){
        cin >> a[i];
        a[i]--;
    }

    for(int j = 0; j < m; j++){
        int u, v;
        cin >> u >> v;
        u--; v--;
        ady[u].push_back(v);
        ady[v].push_back(u);
    }

    fair();

    for(int i = 0; i < n; i++) cout << res[i] << " ";
    cout << endl;
}