#include <iostream>
#include <vector>
#include <cmath>
#include "utility"
#include <tuple>

using namespace std;
int max(vector<tuple<int,int,int>> A){
    int max = get<1>(A[0]);
    for (int i = 0; i < A.size() ; ++i) {
        if (get<1>(A[i]) > max){
            max = get<1>(A[i]);
        }
    }
    return max;
}
vector<tuple<int,int,int>> ordenarPorSegundaComponente(vector<tuple<int,int,int>> A){
    int nBuckets = max(A) + 1;
    vector<vector<tuple<int,int,int>>> buckets(nBuckets);
    for (auto i : A){
        int indice = get<1>(i);
        buckets[indice].push_back(i);
    }
    vector<tuple<int,int,int>> sorted;
    for (auto buck: buckets){
        if(buck.size() != 0){
            for(auto par : buck){sorted.push_back(par);}
        }
    }
    return sorted;
}


bool noSeSolapan(vector<tuple<int,int,int>> &A,vector<tuple<int,int,int>> &res, int ultimoRes, int i) {
    // A[i] es el que ya esta agregado

    return get<1>(res[ultimoRes]) <= get<0>(A[i]);
    //    return  res[ultimoRes].second <=A[i].first ;
}
vector<tuple<int,int,int>> greedy(vector<tuple<int,int,int>> A) {
    if (A.size() == 0){
        return {};
    }
    else{
        A = ordenarPorSegundaComponente(A);
        vector<tuple<int,int,int>> res = { A[0] };
        int ultimoRes = 0;
        int n = A.size();
        for (int i = 0; i < n; i++) {
            if (noSeSolapan(A,res,ultimoRes,i)) {
                res.push_back(A[i]);
                ultimoRes += 1;
            }
        }
        return res;
    }
}
/*
int*/
/// MAIN

int main() {
    int n;
    cin >> n ;
    vector<tuple<int,int,int>> A(n);
    for (int i = 0; i < n ; ++i) {
        int p1,p2;
        cin >> p1;
        cin >> p2;
        tuple<int,int,int> tuple(p1,p2,i+1);
        A[i] = tuple;
    }
    vector<tuple<int,int,int>> v = greedy(A);
    int maximo = v.size();
    cout << maximo << endl;
    for (auto x :v){
        cout << get<2>(x) << endl;
    }

    return 0;
}