// Autor: Francisco Soulignac
// Resuelve UVA 10261 (Ferry Loading)
// El programa es una adaptación de uno que paso los tests de UVA.
// Sin embargo, este programa no fue comprobado contra el servidor


#include <iostream>
#include <vector>
#include <numeric>
#include <limits>

//Uso -1 como valor indefinido
static constexpr auto nil_b = -1;
using namespace std;

struct KnapsackSolver {
    //Trato al Beneficio y Peso como ints
    using Beneficio = int;  // beneficio es negativo cuando hay capacidad negativa
    using Peso = Beneficio;
    using Capacidad = Peso;
    using Solucion = vector<bool>;

    KnapsackSolver(Capacidad capacidad, const vector<Peso>& pesos, const vector<Beneficio>& beneficios);

    // Funcion de programacion dinamica (top-down)
    Beneficio beneficio_total() const;

    //Maximo beneficio poniendo solo elementos en [0, i)
    //cuando la capacidad es c
    Beneficio beneficio_total(Capacidad c, size_t i) const;

    //Reconstruccion de la solucion con elementos en [0, i)
    //cuando la capacidad es c
    Solucion solucion(Capacidad c, size_t i) const;

private:
    vector<Beneficio> beneficio_;
    vector<Peso> peso_;
    mutable vector<vector<Beneficio>> mem_;
};

KnapsackSolver::KnapsackSolver(Capacidad capacidad, const vector<Peso>& pesos, const vector<Beneficio>& beneficios) :
    beneficio_(beneficios),
    peso_(pesos),
    mem_(capacidad+1, vector<Beneficio>(beneficios.size()+1, nil_b))
{}

KnapsackSolver::Beneficio KnapsackSolver::beneficio_total() const {
    return beneficio_total(mem_.size()-1, 0);
}

KnapsackSolver::Beneficio KnapsackSolver::beneficio_total(Capacidad c, size_t i) const {
    // Caso base
    if (c < 0) return numeric_limits<Beneficio>::min();
    if (i == 0) return 0;

    if(mem_[c][i] == nil_b)
        mem_[c][i] = max(beneficio_total(c, i-1), beneficio_[i-1]+beneficio_total(c-peso_[i-1], i-1));

    return mem_[c][i];
}

KnapsackSolver::Solucion KnapsackSolver::solucion(Capacidad c, size_t i) const {
    Solucion res(i, false);
    for(; i > 0; --i) {
        if(beneficio_total(c, i) != beneficio_total(c, i-1)) {
            res[i-1] = true;
            c = c-peso_[i-1];
        }
    }
    return res;
}

constexpr int MAXN = 200;   //no entran mas de 200 autos

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
        

    int t; cin >> t;
    while(t--) {
        int capacidad; cin >> capacidad; capacidad*=100;
        int aux;

        vector<int> coches;
        while(cin >> aux, aux) if(coches.size() < MAXN)
            coches.push_back(aux);

        vector<int> sum(coches.size());
        partial_sum(coches.begin(), coches.end(), sum.begin());
        
        auto solver = KnapsackSolver(capacidad, coches, coches);
        auto x = 0ul;
        while(x < coches.size() and sum[x] - solver.beneficio_total(capacidad, x) <= capacidad) ++x;
        cout << x << '\n';

        for(auto l : solver.solucion(capacidad, x)) cout << (l ? "starboard\n" : "port\n");
        if(t) cout << '\n';
    }
    
    return 0;
}
