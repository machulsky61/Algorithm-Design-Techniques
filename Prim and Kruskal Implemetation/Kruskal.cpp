/**
 * CSES Problem 1675: Road Reparation
 * https://cses.fi/problemset/task/1675/
 * (Para Algoritmos 3 - Implementación de Kruskal)
 * Authors: Pablo Terlisky, Francisco Soulignac
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using Costo = unsigned long int;
using Arista = pair<size_t,size_t>;


//Estructura Union-Find.
//Proporciona dos funciones: Unite y Find
struct UF {
    //vectores internos
    //  p: Vector con los parents
    //  s: Vector con tamaños
    vector<int> p, s;
    
    //Constructor
    UF(int n): p(n, -1), s(n, 1) {}
    
    //unite: Hace la unión y devuelve el tamaño del resultante
    int unite(int v, int w) {
        v = find(v); w = find(w);
        if(v == w) return s[v];
        if(s[v] < s[w]) swap(v, w);
        p[w] = v; //El árbol de mayor tamaño queda como padre
        return s[v] += s[w];
    }
    
    //find: Devuelve el parent
    int find(int v) {
        return p[v] == -1 ? v : p[v] = find(p[v]); //Recursión para path compression
    }
    
};


int main() {
    size_t n,m;
    cin >> n >> m;

    UF componentes(n+1);                //Para indexar desde 1
    vector<pair<Costo, Arista>> valores(m);

    //Lectura del vector de aristas
    for (auto& [c, e] : valores) cin >> e.first >> e.second >> c;

    //Ordenamiento de las aristas por peso
    sort(valores.begin(), valores.end());

    vector<Arista> mst;
    unsigned long int costo_total = 0;

    //Recorre las aristas ordenadas y se queda con aquellas que unan
    //dos vértices de componentes conexas distintas, uniéndolas
    for (auto [c, e] : valores) {
        auto [i,j] = e;
        if (componentes.find(i) != componentes.find(j)) {
            mst.push_back(Arista(i,j));
            costo_total += c;
            componentes.unite(i,j);
        }
    }

    //Salida en formato CSES
    if (mst.size()<n-1) {
        cout << "IMPOSSIBLE";
    } else {
        cout << costo_total;
    }

    return 0;
}
