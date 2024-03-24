#include <iostream>
#include <vector>
#include <cmath>
#include <cassert>


using namespace std;


long long int mod_bin_exp(long long int x, long long y, long long int l) {
    if(y == 0){
        return 1;
    }else{
        if(y%2==0){
            long long int tmp = mod_bin_exp(x,y/2,l);
            return (tmp*tmp)%l;
        }else{
            long long int tmp = mod_bin_exp(x,y/2,l);
            return (((tmp*tmp)%l)*x)%l;
        }
    }
}
long long int mod(long long int a, long long int b){
    long long int resto = a % b;
    while(resto < 0){
        resto = resto + b;
    }
    return resto;
}


long long int PD(vector<vector<long long int>> &M, long long int i, long long int j, vector<long long int> &v, long long int n, long long int r, long long int m) {
    if(j<0){
        j = j+m;
    }
    if(i == n){
        return j == r;
    }else{
        if(M[i][j] == -1){
            bool res = PD(M,i+1,mod(j+v[i],m),v,n,r,m)||
                    PD(M,i+1,mod(j-v[i],m),v,n,r,m)   ||
                    PD(M,i+1,mod(j*v[i],m),v,n,r,m)  ||
                    PD(M,i+1,int(mod_bin_exp(j,v[i],m)),v,n,r,m);

            M[i][j] = res;

        }
        return M[i][j];
    }
}



long long int iniciarPD(long long int n, long long int m,vector<long long int> v,long long int r){
    vector<vector<long long int>> M(n, vector<long long int>(m,-1));// matriz de m filas y n columnas
    return PD(M,1,v[0],v,n,r,m);
}




int main() {
    long long int i;
    cin >> i;
    for(long long int s=0;s<i;s++){
        long long int n,r,m;
        cin >> n >> r >> m;
        vector<long long int> v(n);
        for(long long int j=0;j<n;j++){
            long long int subV;
            cin >> subV;
            v[j] = subV;
        }
        long long int res;
        string sol;
        if(v.size()!=1){
            res = iniciarPD(n,m,v,r);
        }else{
            res = mod(v[0],m) == r;
        }
        if(res == 1){
            sol = "Si";
        }else{
            sol = "No";
        }
        cout << sol << endl;
    }
}

