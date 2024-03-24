#include <iostream>
#include <vector>
#include <utility>

using namespace std;

int INF = 1e9;

int N, P;
vector<int> p;

vector<int> mejor_solucion; int mejor_p;

vector<int> completar_solucion(vector<int>& solucion_parcial, int i) {
    vector<int> solucion = solucion_parcial;

    for (int j=i; j<N; j++)
        solucion.push_back(j);
    
    return solucion;
}

void solve_aux(int i, int p_limite, int p_restante, vector<int>& solucion_parcial) {
    if (p_limite < 0 || P - p_limite + p_restante <= mejor_p)
        return; 

    if (p_restante <= p_limite) {
        mejor_solucion = completar_solucion(solucion_parcial, i);
        mejor_p = P - p_limite + p_restante;
        return;
    }

    if (i == N) {
        mejor_solucion = solucion_parcial; mejor_p = P - p_limite;
    } else {
        solucion_parcial.push_back(i);
        solve_aux(i+1, p_limite - p[i], p_restante - p[i], solucion_parcial);

        solucion_parcial.pop_back();
        solve_aux(i+1, p_limite, p_restante - p[i], solucion_parcial);
    }

    return; 
}

void solve() {
    int p_restante = 0;
    for (int i=0; i<p.size(); i++)
        p_restante += p[i];

    mejor_solucion.resize(0); mejor_p = 0;

    vector<int> solucion_parcial(0);

    solve_aux(0, P, p_restante, solucion_parcial);
}

int main() {
    cin >> N >> P;

    p.resize(N, -1);
    for (int i=0; i<N; i++) cin >> p[i];

    solve();

    cout << "La mejor solucion contiene " << mejor_solucion.size() << " elementos y pesa " << mejor_p << endl;
    cout << "----> ";

    for (int i=0; i<mejor_solucion.size(); i++) {
        cout << mejor_solucion[i] << " ";
    }
    cout << endl;

    return 0;
}
