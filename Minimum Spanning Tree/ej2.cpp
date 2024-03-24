#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long int ll;

int parent[4321];

int find(int x){
	if(parent[x]!=x) {parent[x] = find(parent[x]);}
	return parent[x];
}

void join(int u, int v){
	parent[find(u)] = find(v);
}

int main(){
	int n;
	
	// Leo la entrada
	cin >> n;
	
	vector<ll> x(n),y(n),c(n),k(n);
	for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
	for (int i = 0; i < n; i++) cin >> c[i];
	for (int i = 0; i < n; i++) cin >> k[i];
	
	
	// Armo el grafo
	vector<pair<ll,pair<int,int>>> edges;
	
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			ll cost = abs(x[i]-x[j]) + abs(y[i]-y[j]);
			cost = cost * (k[i] + k[j]);
			edges.push_back(make_pair(cost,make_pair(i,j)));
		}
	}
	for (int i = 0; i < n; i++) edges.push_back(make_pair(c[i],make_pair(n,i)));
	n=n+1;
	
	
	// Uso kruskal guardando la solucion
	for (int i = 0; i < n; i++) parent[i] = i;
	
	sort(edges.begin(),edges.end());
	
	int i = 0;
	int comp = n;
	ll acum = 0;
	vector<int> stations;
	vector<int> connections;
	while(comp>1){
		int u = edges[i].second.first;
		int v = edges[i].second.second;
		if (find(u) != find(v)){
			join(u,v);
			acum += edges[i].first;
			if(u == n-1) {
				stations.push_back(v);
			}else{
				connections.push_back(i);
			}
			comp--;
		}
		i++;
	}
	
	// Imprimo la solucion
	cout << acum << endl;
	cout << stations.size() << endl;
	for (int i = 0; i < (int)stations.size(); i++) cout << stations[i]+1 << ' ';
	cout << endl;
	
	cout << connections.size() << endl;
	for (int i = 0; i < (int)connections.size(); i++) cout << edges[connections[i]].second.first+1 << ' ' << edges[connections[i]].second.second+1 << endl;
	
	
}

