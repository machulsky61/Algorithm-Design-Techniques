
#include <iostream>
#include <vector>
#include <limits>
#include <functional>

using namespace std;

constexpr int MINF = numeric_limits<int>::min();
constexpr int BOTTOM = -1;

int cd(const vector<int>& W, int k) {
    vector<vector<int>> M(W.size(), vector<int>(k+1, BOTTOM));
    function<int(int,int)> f = [&](int i, int j) -> int {
        if(j < 0) return MINF;
        if(i == -1) return 0;   //primer elemento es 0
        if(M[i][j] == BOTTOM) M[i][j] = max(f(i-1, j), W[i] + f(i-1, j-W[i]));
        return M[i][j];
    };
    return f(W.size()-1,k); //ultimo elemnto es size()-1
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> W(n);
    for(auto& w : W) cin >> w;

    cout << cd(W, k) << endl;
    return 0;
}

/*
Ejemplo: 7 canciones, 40 minutos
7 40
20 13 15 15 9 17 16

20 + 13
20 + 15
20 + 9
20 + 17
20 + 16
13 + 15 + 9
13 + 9 + 17
13 + 9 + 16
15 + 15 + 9
15 + 9 + 16 = 40 (optimo)
9 + 17
9 + 16
*/
