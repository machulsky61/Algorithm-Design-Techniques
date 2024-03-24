
#include <iostream>
#include <vector>
#include <functional>

using namespace std;

constexpr int BOTTOM = -1;

int subconjuntos(int n, int k) {
    vector<vector<int>> M(n+1, vector<int>(k+1, BOTTOM));
    function<int(int,int)> f = [&](int i, int j) -> int {
        if(i == 0 and j == 0) return 1;
        if(j < 0 or j > i) return 0;
        if(M[i][j] == BOTTOM) M[i][j] = f(i-1, j) + f(i-1, j-1);
        return M[i][j];
    };
    return f(n,k);
}

int main() {
    int n, k;
    cin >> n >> k;
    cout << subconjuntos(n, k) << endl;
    return 0;
}
