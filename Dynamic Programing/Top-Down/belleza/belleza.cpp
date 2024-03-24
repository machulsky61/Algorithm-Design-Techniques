
#include <iostream>
#include <vector>
#include <limits>
#include <functional>

using namespace std;

using Matriz = vector<vector<int>>;
constexpr int BOTTOM = -1;

int belleza(const Matriz& B) {
    vector<int> m(B.size(), BOTTOM);
    function<int(int)> f = [&](int j) -> int {
        if(j == 0) return 0;
        if(m[j] == BOTTOM) {
            m[j] = B[0][j];
            for(int i = 0; i < j; ++i) m[j] = max(m[j], B[i][j] + f(i));
        }
        return m[j];
    };
    return f(B.size()-1);
}

int main() {
    int n;
    cin >> n;

    Matriz B(n, vector<int>(n));
    for(auto& R : B) for(auto &b: R) cin >> b;

    cout << belleza(B) << endl;
    return 0;
}

/*
Ejemplo: S = abc tiene 4 posiciones 0a1b2c3

4
0 4 2 1
0 0 3 1
0 0 0 5
0 0 0 0

|abc| = B[0,3] = 1
|ab|c| = B[0,2] + B[2,3] = 2 + 5 = 7
|1|23| = B[0,1] + B[1,3] = 4 + 1 = 5
|1|2|3| = B[0,1] + B[1,2] + B[2,3] = 4 + 3 + 5

Ejemplo: S = abcd tiene 5 posiciones 0a1b2c3d4
5
0 2 4 3 1
0 0 1 4 2
0 0 0 0 3
0 0 0 0 1
0 0 0 0 0

|abcd| = B[0,4] = 1
|abc|d| = B[0,3] + B[3,4] = 3 + 3 = 6
|ab|cd| = B[0,2] + B[2,4] = 4 + 3 = 7
|a|bcd| = B[0,1] + B[1,4] = 2 + 2 = 4
|ab|c|d| = B[0,2] + B[2,3] + B[3,4] = 4 + 0 + 1 = 5
|a|bc|d| = B[0,1] + B[1,3] + B[3,4] = 2 + 4 + 1 = 7
|a|b|cd| = B[0,1] + B[1,2] + B[2,4] = 2 + 1 + 3 = 6
|a|b|c|d| = B[0,1] + B[1,2] + B[2,3] + B[3,4] = 2 + 1 + 0 + 1 = 4
*/
