#include <iostream>
#include <algorithm>
#include <vector> 
#include <map>
#include <set>

int parent[154321];

int find(int x){
	if(parent[x]!=x) {parent[x] = find(parent[x]);}
	return parent[x];
}

void join(int u, int v){
	parent[find(u)] = find(v);
}

using namespace std;

char ANS[][110] = { "at least one", "any", "none" };

// Codigo prestado de Pablo T.

void dfs_parent_timer(const vector<vector<int>>& ady,const int source, int & current_time, vector<int>& parents, vector<int>& time_in, vector<int>& color) {
    color[source] = 1;
    time_in[source] = current_time++;
    for (int u : ady[source]) {
        if (color[u]==0) {
            parents[u]=source;
            dfs_parent_timer(ady, u, current_time, parents, time_in, color);
        }
    }
    color[source]=2;
}

int dp(const vector<vector<int>>& ady, int source, const vector<int>& time_in, const vector<int>& parents, vector<bool>& puente_con_parent) {
    int cantidad = 0;
    for (int u : ady[source]) {
        if (parents[u]==source) {
            cantidad +=dp(ady, u, time_in, parents, puente_con_parent);
        } else {
            if (time_in[source]>time_in[u] and parents[source]!=u) { 
                cantidad++;
            }
            if (time_in[source]<time_in[u]) { 
                cantidad--;
            }
        }
    }
    if (cantidad==0 && parents[source]!=source) {
        puente_con_parent[source] = true;
    }
    return cantidad;
}


int main(){
	int n,m;
	
	cin >> n >> m;
	
	vector<pair<pair<int,int>,pair<int,int>>> edges;
	
	vector<int> ret(m);
	for (int i = 0; i < n+1; i++) parent[i] = i;
	
	
	for (int i = 0; i < m; i++){
		int a,b,w;
		cin >> a >> b >> w;
		edges.push_back(make_pair(make_pair(w,i),make_pair(a-1,b-1)));
	}
	
	sort(edges.begin(),edges.end());
	
	vector<vector<int>> ady;
	int i,j;
	
	for (i = 0; i < (int)edges.size(); i=j){
		ady.clear();
		map<int,int> nodes;
		map<pair<int,int>,int> cnt_edg;
		
		for (j=i ; j < (int)edges.size() && edges[i].first.first == edges[j].first.first; j++){
			int u = find(edges[j].second.first);
			int v = find(edges[j].second.second);
			
			if (nodes.count(u)==0) {
				nodes[u] = nodes.size();
				ady.push_back(vector<int>());
			}
			if (nodes.count(v)==0){
				nodes[v] = nodes.size();
				ady.push_back(vector<int>());
			}
			u = nodes[u];
			v = nodes[v];
			if(u!=v){
				if (cnt_edg.count(make_pair(min(u,v),max(u,v))) == 0) cnt_edg[make_pair(min(u,v),max(u,v))] = 0;
				cnt_edg[make_pair(min(u,v),max(u,v))] = cnt_edg[make_pair(min(u,v),max(u,v))] + 1;
				
				if (cnt_edg.count(make_pair(min(u,v),max(u,v))) == 1){
					ady[u].push_back(v);
					ady[v].push_back(u);
				}	
			}
		}
		
		int n = nodes.size();
		
		vector<int> time_in(n,0), parents(n,-1), color(n,0);
		vector<bool> puente_con_parent(n,0);
		int timer = 0;
		for (int k = 0; k < (int)nodes.size();k++){
			if (color[k] == 0){
				timer++;
				dfs_parent_timer(ady, k, timer, parents, time_in, color);
				dp(ady, k, time_in, parents, puente_con_parent);
				
			}
		}
		
		for (j=i ; j<(int)edges.size() && edges[i].first.first == edges[j].first.first; j++){
			int u = find(edges[j].second.first);
			int v = find(edges[j].second.second);
			u = nodes[u];
			v = nodes[v];
			
			ret[edges[j].first.second] = 0;
			
			if(parents[u]==v && puente_con_parent[u]) ret[edges[j].first.second] = 1;
			if(parents[v]==u && puente_con_parent[v]) ret[edges[j].first.second] = 1;
			if(u==v) ret[edges[j].first.second] = 2;
			
			if(cnt_edg[make_pair(min(u,v),max(u,v))] > 1) ret[edges[j].first.second] = 0;
			
		}
			
		for (j=i ; j<(int)edges.size() && edges[i].first.first == edges[j].first.first; j++){
			int u = find(edges[j].second.first);
			int v = find(edges[j].second.second);
			if (u!=v) join(u,v);
		}
		
	}
	
	for (int i = 0; i < m; i++){
		cout << ANS[ret[i]] << endl;
	}
	
}
