#include <iostream>
#include "vector"
#include <functional>
#include <ctime>

using namespace std;
using matriz = vector<vector<int>>;
matriz M;
matriz B;

int distancia(int a1 , int a2, int p1, int p2) {
    return abs(a1-p1) + abs(a2-p2);
}

bool esValida (vector<int> &pos) {
    int m = M.size();
    int n = M[0].size();
    bool c1 = M[pos[0]][pos[1]] == m*n/4;
    bool c2 = M[pos[2]][pos[3]] == m*n/2;
    bool c3 = M[pos[4]][pos[5]] == m*n*3/4;
    bool c4 = M[0][1] == m*n;
    return (c1 && c2 && c3 && c4);
}

bool enRango(int &m,int &n,int &i,int &j) {
    return (i>=0 && i<m && j>=0 && j<n);
}

bool distanciasPosibles (int i, int j, vector<int> &pos, int c, int t) {
    //t es m*n
    if (c <= int(t / 4)) {
        return distancia(i, j, pos[0], pos[1]) <= (int(t / 4) - c);
    } else {
        if (c <= int(t / 2)) {
            return distancia(i, j, pos[2], pos[3]) <= int(t / 2) - c;
        } else {
            if (c <= int(t * 3 / 4)) {
                return distancia(i, j, pos[4], pos[5]) <= int(t * 3 / 4) - c;
            } else {
                return   distancia(i, j, 0, 1) <= t - c;
            }
        }
    }
}

bool checkCorrectos(int &i, int &j, int &c, vector<int> &pos) {
    int t = M.size() * M[0].size();
    if (i == pos[0] && j == pos[1]) return c == t/4;
    if (i == pos[2] && j == pos[3]) return c == t/2;
    if (i == pos[4] && j == pos[5]) return c == t*3/4;
    if (i == 0 && j == 1) return c == t;
    return true;
}

vector<vector<int>> crearMatrizBordes(int &m, int &n) {
    // inicializa una matriz de bordes libres
    vector<vector<int>> res = vector<vector<int>> (m,vector<int>( n,4));
    for (int i = 0; i < m; i++) {
        res[i][0]--;
        res[i][n-1]--;
    }
    for (int j = 0; j < n; j++) {
        res[0][j]--;
        res[m-1][j]--;
    }
    return res;
}


void disminuirUnoAlrededor(int &i, int &j, int &m, int &n) {
    if (i > 0) B[i-1][j]--;
    if (i < m - 1) B[i+1][j]--;
    if (j > 0) B[i][j-1]--;
    if (j < n - 1) B[i][j+1]--;
}

void aumentarUnoAlrededor(int &i, int &j, int &m, int &n) {
    if (i > 0) B[i-1][j]++;
    if (i < m - 1) B[i+1][j]++;
    if (j > 0) B[i][j-1]++;
    if (j < n - 1) B[i][j+1]++;
}

bool esLaUltima(int i, int j) {
    return (i==0 && j==1);
}

bool ultimaEncerrada(int &i, int &j) {
    // se fija si última quedó encerrada y la vibora NO está por llegar
    return B[0][1] == 0 && (not (distancia(i,j,0,1)<=1));
}

bool celdaEncerrada (int i, int j, int m, int n) {
    //una celda quedó encerrada si está vacía y tiene 1 solo borde libre, pero no es la última
    bool res = enRango(m,n,i,j) && B[i][j] == 1 && M[i][j] == 0 && !esLaUltima(i,j);
    return res;
}

bool diagonalEncerrada(int i, int j, int m, int n) {
    //se fija si dejó alguna celda en diagonal encerrada
    return celdaEncerrada(i-1, j-1, m, n) || celdaEncerrada(i+1, j+1, m, n) || celdaEncerrada(i-1, j+1, m, n) || celdaEncerrada(i+1, j-1, m, n);
}


bool otraEncerrada(int i, int j, int m, int n) {
    //se fija si dejó encerrada alguna celda a 2 celdas de distancia recta
    return celdaEncerrada(i-2, j, m, n) || celdaEncerrada(i, j-2, m, n) || celdaEncerrada(i+2, j, m, n) || celdaEncerrada(i, j+2, m, n);
}

int CuantasFormas(int m, int n, vector<int> &pos) {
    M = vector<vector<int>> (m,vector<int>( n,0));
    B = crearMatrizBordes(m,n); // matriz que almacena la cantidad de bordes libres de cada celda
    int res = 0;
    function<void(int,int,int)> f = [&](int i, int j, int c) -> void {
        if (!enRango(m,n,i,j) ) {
            return ;
        }
        //if (checkOcupados(M, c, pos)){
        //    return;
        //}

        if (M[i][j] == 0) {
            if (!distanciasPosibles(i,j,pos,c,m*n)){
                return ;
            }
            M[i][j] = c;
        } else {
            return;
        }

        if (!checkCorrectos(i,j,c,pos)) {
            M[i][j] = 0;
            return;
        }

        disminuirUnoAlrededor(i,j,m,n);


        if (diagonalEncerrada(i,j,m,n) || otraEncerrada (i,j,m,n) || ultimaEncerrada(i,j)) {
            M[i][j] = 0;
            aumentarUnoAlrededor(i,j,m,n);
            return;
        }

        if (c == m*n) {
            if  (esValida(pos))  {
                res++;
            }
        } else {
            f(i+1,j,c+1); // cambiar vector cambiar fila
            f(i-1,j,c+1);
            f(i,j+1,c+1); // cambiar columna
            f(i,j-1,c+1);
        }
        M[i][j] = 0;
        aumentarUnoAlrededor(i,j,m,n);
    };
    f(0,0,1);
    return res;
}

int main() {
    unsigned t0, t1;
    int m = 1 , n = 1 ;
    int i = 1;
    while (m!=0 && n !=0 ) {
        cin >> m >> n;
        t0=clock();
        if (m!=0 || n !=0) {
            vector<int> v(6);
            for (auto &x: v) {
                cin >> x;
            }

            cout << "Case " << i <<": " << CuantasFormas(m, n, v) << endl;
            i++;
            t1 = clock();

            double time = (double(t1-t0)/CLOCKS_PER_SEC);
            cout << "Execution Time: " << time << endl;
        }
    }
    return 0;
}
