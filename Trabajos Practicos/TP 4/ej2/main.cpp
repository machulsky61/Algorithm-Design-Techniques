#include <iostream>
#include <vector>
#include <queue>
#include <stdio.h>

using namespace std;
int INF = 100000;




int bfs(int s, int t, vector<int>& parent, vector<vector<int>> &adj, vector<vector<int>> &capacity) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next]) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}

int maxflow(int s, int t, int n, vector<vector<int>> &adj, vector<vector<int>> &capacity) {
    int flow = 0;
    vector<int> parent(n);
    int new_flow;

    while (new_flow = bfs(s, t, parent, adj, capacity)) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}





int main() {
    while(true){
        int n,m;
        scanf("%i",&n);
        scanf("%i",&m);
        if(n == 0 && m == 0){
            return 0;
        }else{
            vector<vector<int>> capacity(n+2,vector<int>(n+2,0));
            vector<vector<int>> adj(n+2, vector<int>());

            int s = 0; //fuente
            int t = n+1;//sumidero

            for(int i=1;i<n+1;i++){ // me dicen quien vota a que algoritmo
                int h;
                scanf("%i",&h);
                if(h == 1){ //vota a prim -> lo uno con s y capacidad 1
                    adj[s].push_back(i);
                    capacity[s][i] = 1;

                    adj[i].push_back(s);
                    //capacity[i][s] = 1;

                }else{ //vota kruskal -> lo uno con t y capacidad 1
                    adj[i].push_back(t);
                    capacity[i][t] = 1;

                    adj[t].push_back(i);
                    //capacity[t][i] = 1;
                }
            }

            for(int l = 0; l<m;l++){ // si i y j son amigos les pongo una arista con capacidad 1 a ambos
                int i, j;
                scanf("%i",&i);
                scanf("%i",&j);

                adj[i].push_back(j);
                adj[j].push_back(i);

                capacity[i][j] = 1;
                capacity[j][i] = 1;
            }

            printf("%i", maxflow(s,t,n+2,adj,capacity));
            printf ("%s", "\n");
        }
    }
}
