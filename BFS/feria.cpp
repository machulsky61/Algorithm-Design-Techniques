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
vector<vector<int> > dist;
int n, m, k, s;

void bfs(int source, vector<int>& d){
    deque<int> q;
    q.push_back(source);
    d[source] = 0;
    while(!q.empty()){
        int v = q.front();
        q.pop_front();
        for(int u : ady[v]){
            if(d[u] == INF){
                q.push_back(u);
                d[u] = d[v]+1;
            }
        }
    }
}

void add_product_nodes(){
    // agregamos k nodos nuevos vacíos
    for(int prod = 0; prod < k; prod++) ady.push_back(vector<int>()); 

    // agregamos las aristas hacia las ciudades del producto correspondiente
    for(int i = 0; i < n; i++){
        ady[n+a[i]].push_back(i);
    }
}

void fair(){
    add_product_nodes();

    // dist[prod][j] es la distancia (más 1) del producto prod a la ciudad j (si j < n)
    dist = vector<vector<int> >(k, vector<int>(n+k, INF));
    for(int prod = 0; prod < k; prod++){
        bfs(n+prod, dist[prod]);
    }

    // armamos un vector de costos para cada ciudad
    vector<vector<int> > costs = vector<vector<int > >(n, vector<int>(k));
    for(int prod = 0; prod < k; prod++){
        for(int i = 0; i < n; i++){
            costs[i][prod] = dist[prod][i]-1;
        }
    }

    // tomamos los primeros s elementos de ese vector para cada ciudad
    res = vector<int>(n, 0);
    for(int i = 0; i < n; i++){
        nth_element(costs[i].begin(), costs[i].begin()+s, costs[i].end()); // deja los s elementos más chicos al principio en O(k) en tiempo promedio
        for(int j = 0; j < s; j++){
            res[i] += costs[i][j];
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
