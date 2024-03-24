#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
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



vector<tuple<int,int,int>> read_input(int size) {
    vector<tuple<int,int,int>> input(size);
    string file_name = "inputs/input_" + to_string(size);
    cout << file_name << endl;
    ifstream read_file(file_name);
    for (int i=0; i<size; i++){
        int p1, p2;
        read_file >> p1;
        read_file >> p2;
        tuple<int,int,int> tuple(p1,p2,i+1);
        input[i] = tuple;
    }
    read_file.close();
    return input;
}

double measure(vector<tuple<int,int,int>> A) {
    auto start = chrono::high_resolution_clock::now();

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

    auto stop = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = stop - start;
    return diff.count();
}

int main() {
    int repeat = 10;
    ofstream output_file; output_file.open("runtime.csv");
    output_file << "n,time\n";
    
    int limit = 1<<27;
    for (int n=65536; n<limit; n*=2) {
        vector<tuple<int,int,int>> input = read_input(n);

        double counter = 0;
        for (int ignore=0; ignore<repeat; ignore++) counter += measure(input);
        
        output_file << n << "," << counter / repeat << endl;
    }

    output_file.close();
    return 0;
}
