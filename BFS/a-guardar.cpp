// Autor: Francisco Soulignac
// No fue mayormente testeado


#include <vector>
#include <deque>
#include <tuple>
#include <iostream>
#include <iterator>

// Descripcion de los estados de cada casilla en el input
constexpr char CHAR_INICIO = 'C';
constexpr char CHAR_FIN = 'E';
constexpr char CHAR_OCUPADO = '#';

// Computo de las aristas corresopndientes a las transiciones
constexpr int PARADA = 0;
constexpr int HORIZONTAL = 1;
constexpr int VERTICAL = 2;
std::vector<int> ESTADOS = {PARADA, HORIZONTAL, VERTICAL};

std::vector<int> DIRECCIONES = {0,1,2,3};  //izquierda, derecha, arriba, abajo
std::vector<char> MOVIMIENTO_OPUESTO = {'R', 'L', 'D', 'U'};
std::vector<std::vector<int>> MOVER_ESTADO =
{
    {HORIZONTAL, HORIZONTAL, VERTICAL, VERTICAL},  //parada
    {PARADA, PARADA, HORIZONTAL, HORIZONTAL},  //horizontal
    {VERTICAL, VERTICAL, PARADA, PARADA}  //vertical
};
std::vector<std::vector<int>> MOVER_FILA =
{
    {0, 0, -2, 1},  //parada
    {0, 0, -1, 1},  //horizontal
    {0, 0, -1, 2}  //vertical
};
std::vector<std::vector<int>> MOVER_COLUMNA =
{
    {-2, 1, 0, 0},  //parada
    {-1, 2, 0, 0},  //horizontal
    {-1, 1, 0, 0}  //vertical
};

using Fila = std::vector<int>;
using Tablero = std::vector<Fila>;

int main() {
    int m, n; std::cin >> m >> n;

    int LIBRE = (n+5)*(m+5);
    int OCUPADO = LIBRE+1;

    //tablero con reborde
    std::vector<Tablero> tablero(ESTADOS.size(), Tablero(m+3, Fila(n+3, LIBRE)));
    for(auto s : ESTADOS) {
        for(auto i : {0,1,m+2}) tablero[s][i] = Fila(n+3, OCUPADO);
        for(auto i = 2ul; i < m+2; ++i) for(auto j : {0,1,n+2}) tablero[s][i][j] = OCUPADO;
    }
    for(auto j = 2ul; j < n+2; ++j) tablero[VERTICAL][m+1][j] = OCUPADO;
    for(auto i = 2ul; i < m+2; ++i) tablero[HORIZONTAL][i][n+1] = OCUPADO;

    int inicio_s = PARADA, inicio_i, inicio_j, fin_s = PARADA, fin_i, fin_j;
    for(int i = 2; i < m+2; ++i) for(int j = 2; j < n+2; ++j) {
        char c; std::cin >> c;
        switch(c) {
            case CHAR_INICIO:
                inicio_i = i;
                inicio_j = j;
                break;
            case CHAR_FIN:
                fin_i = i;
                fin_j = j;
                break;
            case CHAR_OCUPADO:
                for(auto s : ESTADOS) tablero[s][i][j] = OCUPADO;
                tablero[VERTICAL][i-1][j] = OCUPADO;
                tablero[HORIZONTAL][i][j-1] = OCUPADO;
                break;
        }
    }


    // BFS con aristas implicitas
    tablero[inicio_s][inicio_i][inicio_j] = 0;
    for(std::deque<std::tuple<int, int, int>> queue{{inicio_s, inicio_i, inicio_j}}; not queue.empty(); queue.pop_front())
    {
        auto [s, i, j] = queue.front();
        for(auto d : DIRECCIONES) {
            auto sd = MOVER_ESTADO[s][d];
            auto id = i + MOVER_FILA[s][d];
            auto jd = j + MOVER_COLUMNA[s][d];
            if(tablero[sd][id][jd] != LIBRE) continue;
            tablero[sd][id][jd] = tablero[s][i][j] + 1;
            if(sd == fin_s and id == fin_i and jd == fin_j) break;
            queue.push_back({sd, id, jd});
        }
    }

    // Reconstruccion de la solucion
    std::cout << tablero[fin_s][fin_i][fin_j] << std::endl;
    if(tablero[fin_s][fin_i][fin_j] == LIBRE) return 0;

    std::vector<char> res(tablero[fin_s][fin_i][fin_j], '.');
    while(tablero[fin_s][fin_i][fin_j] > 0) {
        for(auto d : DIRECCIONES) {
            auto sd = MOVER_ESTADO[fin_s][d];
            auto id = fin_i + MOVER_FILA[fin_s][d];
            auto jd = fin_j + MOVER_COLUMNA[fin_s][d];
            if(tablero[sd][id][jd] != tablero[fin_s][fin_i][fin_j] - 1) continue;
            res[tablero[fin_s][fin_i][fin_j] - 1] = MOVIMIENTO_OPUESTO[d];
            fin_s = sd; fin_i = id; fin_j = jd;
        }
    }
    std::copy(res.begin(), res.end(), std::ostream_iterator<char>(std::cout));
    std::cout << std::endl;

    return 0;
}
