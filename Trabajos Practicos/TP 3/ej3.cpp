/**
 * CSES Problem 1675: Road Reparation
 * https://cses.fi/problemset/task/1675/
 * (Para Algoritmos 3 - Implementación de Kruskal)
 * Authors: Pablo Terlisky, Francisco Soulignac
 */
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <iomanip>
#include <limits>

using namespace std;

using Costo = long double;
// {c,{from,to}}
using Arista = pair<long long int,long long int>;


//Estructura Union-Find.
//Proporciona dos funciones: Unite y Find
struct UF {
    //vectores internos
    //  p: Vector con los parents
    //  s: Vector con tamaños
    vector<long long int> p, s;

    //Constructor
    UF(long long int n): p(n, -1), s(n, 1) {}

    //unite: Hace la unión y devuelve el tamaño del resultante
    long long int unite(long long int v, long long int w) {
        v = find(v); w = find(w);
        if(v == w) return s[v];
        if(s[v] < s[w]) swap(v, w);
        p[w] = v; //El árbol de mayor tamaño queda como padre
        return s[v] += s[w];
    }

    //find: Devuelve el parent
    long long int find(long long int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]); //Recursión para path compression
    }

};


long double distCost(vector<long long int> a, vector<long long int> b, long long int i, long long int j){///calcula la distancia cartesiana entre dos puntos del plano
    if(i == j){
        return numeric_limits<long double>::infinity();
    }else{
        return sqrt(((a[0]-b[0]) * (a[0]-b[0])) + ((a[1]-b[1]) * (a[1]-b[1])));
    }
}



int main() {
    long long int l;
    cin >> l;
    for(long long int j=1; j<l+1; j++){
        long long int n,r,w,u,v;
        cin >> n >> r >> w >> u >> v;
        UF componentes(n+1);                //Para indexar desde 1
        vector<vector<long long int>> cartesianas(n); //leo la entrada
        for(int i=0;i<n;i++){
            int x,y;
            cin >> x >> y;
            cartesianas[i] = {x,y};
        }
        vector<pair<Costo,Arista>> valores;
        for(int i = 0; i<n; i++){
            for(int j = i; j<n; j++){
                if(i ==j) continue;
                valores.push_back({distCost(cartesianas[i],cartesianas[j],i,j),{i,j}}) ;
            }
        }
        sort(valores.begin(), valores.end());

        vector<pair<Costo,Arista>> mst;
        long double UTP = 0;
        long double fibra = 0;

        //Recorre las aristas ordenadas y se queda con aquellas que unan
        //dos vértices de componentes conexas distintas, uniéndolas
        for (auto [c, e] : valores) {
            auto [i,j] = e;
            if(n-mst.size()==w){
                break;
            }
            if (componentes.find(i) != componentes.find(j)) {
               mst.push_back({c,Arista(i,j)});
               componentes.unite(i,j);
               if(c <= r){
                   UTP += c;
               }else{
                   fibra += c;
               }
            }
        }

        cout << "Caso #" + to_string(j) + ": ";
        cout << fixed;
        cout << setprecision(3) <<  u*UTP;
        cout << " ";
        cout << v*fibra;
        cout <<"\n" << endl;
    }
}
