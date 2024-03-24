#include <iostream>
#include <vector>

using namespace std;

int N; vector<int> number;

vector<bool> CRIBA;

void cargar_criba() {
    CRIBA.resize(1e7, true);
    CRIBA[0] = CRIBA[1] = false;

    for (long i=2; i<=CRIBA.size(); i++)
        if (CRIBA[i] && i*i<=CRIBA.size())
            for (int j=i*i; j<=CRIBA.size(); j+=i)
                CRIBA[j] = false;
}

bool esPrimo(int x) {
    return CRIBA[x];
}

int solve_aux(int ultimo_indice, int cnt, vector<bool>& usado) {
    if (cnt == N)
        return esPrimo(number[0] + number[ultimo_indice]);

    else {
        int acum = 0;
        
        for (int i=0; i<N; i++) 
            if (!usado[i] && esPrimo(number[ultimo_indice] + number[i])) {
                usado[i] = true;
                acum += solve_aux(i, cnt+1, usado);
                usado[i] = false;
        }
        
        return acum;
    }
}

int solve() {
    vector<bool> usado(N, false);
    usado[0] = true;
    return N * solve_aux(0, 1, usado);
}

int main() {
    cin >> N; number.resize(N);

    for (int i=0; i<N; i++) cin >> number[i];

    cargar_criba();

    cout << solve() << endl;

    return 0;
}
