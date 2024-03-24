#include <iostream>
#include <vector>

using namespace std;

int N;
vector<char> letras;

char VOCAL = '.';
char CONSONANTE_NO_L = '[';
char L = 'L';
char WILDCARD = '_';

bool es_vocal(int i) {
    char character = letras[i];
    return character == VOCAL || character == 'A' || character == 'E' || character == 'I' || character == 'O' || character == 'U';
}

bool puede_ser_consonante(int i) {
    return i < 2 || (es_vocal(i-1) || es_vocal(i-2));
}

bool puede_ser_vocal(int i) {
    return i < 2 || (!es_vocal(i-1) || !es_vocal(i-2));
}

long solve_aux(int i, bool tiene_L) {
    if (i == N)
        return tiene_L;

    if (letras[i] != WILDCARD) 
        if ((es_vocal(i) && puede_ser_vocal(i))
                || !es_vocal(i) && puede_ser_consonante(i))
           return solve_aux(i+1, tiene_L || letras[i] == 'L');
        else
            return 0;

    long acum = 0;

    // Caso vocal
    if (puede_ser_vocal(i)) {
        letras[i] = VOCAL;
        acum += 5 * solve_aux(i+1, tiene_L);
        letras[i] = WILDCARD;
    }

    // Caso consonante no L
    if (puede_ser_consonante(i)) {
        letras[i] = CONSONANTE_NO_L;
        acum += 20 * solve_aux(i+1, tiene_L);
        letras[i] = WILDCARD;
    }

    // Caso L
    if (puede_ser_consonante(i)) {
        letras[i] = L;
        acum += solve_aux(i+1, true);
        letras[i] = WILDCARD;
    }

    return acum;
}

long solve() {
    return solve_aux(0, false);
}

int main() {
    cin >> N; 

    letras.resize(N);
    for (int i=0; i<N; i++) cin >> letras[i];

    cout << solve() << endl;

    return 0;
}
