#include <iostream>
#include <list>
#include <cmath>
#include "tuple"
#include "vector"
#include "limits"
#include <functional>


using namespace std;

constexpr int MAXINF = 100000;// numeric_limits<int>::max();
constexpr int BOTTOM = -1;

///variables globales
vector<vector<int>> M;
vector<double> limite;

void ordenoPorPos(vector<vector<double>> &aspersores) { /// O(n^2)
    for(int i=0; i<aspersores.size(); i++) {
        for(int j=i; j>0 && aspersores[j][0] < aspersores[j-1][0]; j--) {
            swap(aspersores[j], aspersores[j-1]);
        }
    }
}
void ordenoPorPosInv(vector<vector<double>> &aspersores) { /// O(n^2)
    for(int i=0; i<aspersores.size(); i++) {
        for(int j=i; j>0 && (aspersores[j][0]+aspersores[j][1]) < (aspersores[j-1][0]+aspersores[j-1][1]); j--) {
            swap(aspersores[j], aspersores[j-1]);
        }
    }
}

int Min(int a, int b) {
    if (a<=b) {return a;} else {return b;}
}
int fuerzaBruta(list<tuple<int,double,int>> v, double l, int w,int i){
    if (l<=0) {
        return 0;
    }
    if (v.empty()) {
        return 10000;
    }
    tuple<int,double,int> t = v.back();
    v.pop_back();
    if ( get<0>(t) + get<1>(t) >= l ) {
        return Min(fuerzaBruta(v,get<0>(t) - get<1>(t) ,w,i-1) + get<2>(t), fuerzaBruta(v,l,w,i-1));
    } else {
        return fuerzaBruta(v,l,w,i-1);
    }
}

double calcularDistancia(double r, double a){
    return sqrt(r * r - a * a);

}
int watteringGrass(double l, vector<vector<double>> &aspersores, int i, int j){
    if (limite[j]<=0){
        return 0;
    }
    if (i<0){
        return MAXINF;
    }

    if (M[i][j]==BOTTOM) {
        if (aspersores[i][0] + aspersores[i][1] >= limite[j]) { ///el aspersor puede servir
            M[i][j] = Min(watteringGrass(l, aspersores, i - 1, i) + aspersores[i][2],
                          watteringGrass(l, aspersores, i - 1, j));
        } else { /// el aspersor i no sirve pues no cubre
            M[i][j] = watteringGrass(l, aspersores, i - 1, j);
        }
    }
    return M[i][j];
}

int preparaElTerreno(int l, vector<vector<double>> &aspersores){
    int n = aspersores.size();
    M = vector<vector<int>>(n,vector<int>(n+1,BOTTOM)); ///matriz N x N+1 donde guardo mis costos

    ordenoPorPos(aspersores);

    for (int i = 0; i < n ; ++i) {
        limite.push_back(aspersores[i][0]-aspersores[i][1]);
    }
    limite.push_back(l);


    return watteringGrass(l, aspersores, n-1, n);
}

int main() {
    int n, l, w;
    cin >> n >> l >> w;

    vector<vector<double>> aspersores;
    for(int i = 0; i < n; i++){
        vector<double> actual;
        actual.clear();
        for (int j = 0; j < 3; ++j){///guardo los datos para cada aspersor en un vec de 3 elem. Ubicacion, diametro y costo respectivamente
            int a;
            cin >> a;
            actual.push_back(a);
        }
        if(actual[1]>double(w)/double(2)){ /// descarto lo que no llegan al borde
            actual[1] = calcularDistancia(actual[1],double(w)/double(2));///guardo lo que cubre
            aspersores.push_back(actual);
        }
    }
    int res = preparaElTerreno(l,aspersores);
    cout << (res == MAXINF ? -1 : res) << endl;
    return 0;
}
