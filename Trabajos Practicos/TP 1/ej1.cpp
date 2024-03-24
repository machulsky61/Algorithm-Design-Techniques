#include <iostream>
#include <vector>
#include <set>

using namespace std;


int contador = 0;
vector<vector<int>> res;

void BT(vector<vector<int>> &M, int i, int j, set<int> &r, int k){
    if(contador == k){
        return;
    }else{
        int n = M.size();
        int cteMagica = (((n*n*n) + n)/(2));

        if(i == n && j == 0){
            int sDiag = 0;
            for (int s = 0; s<n; s++){
                sDiag += M[s][s];
            }
            if(sDiag == cteMagica){
                contador++;
                if(contador == k){
                    res = M;
                    return;
                }
            }else{
                return;
            }
        }else{


            ///si complete la antidiag y la suma =! cte magica -> corto la recursion.
            if(i==n-1 && j==1){
                int sAnti = 0;
                for(int s=0;s<n;s++){
                    for(int u=0;u<n;u++){
                        if(s+u == n-1){
                            sAnti += M[s][u];
                        }
                    }
                }
                if(sAnti != cteMagica){
                    return;
                }
            }
            ///si estoy por completar una fila/columna, veo que el numero q suma == cte magica este en los restantes y lo pongo, sino -> podo
            if(j==n-1){//por completar fila (contiene ultima pos)
                int sumParcial = 0;
                for(int s=0;s<n-1;s++){
                    sumParcial+= M[i][s];
                }
                int necesito = cteMagica - sumParcial;
                if(necesito < n*n+1 && r.count(necesito) == 1){
                    M[i][j] = necesito;
                    r.erase(necesito);
                    BT(M,i+1,0,r,k);
                    M[i][j]=0;
                    r.emplace(necesito);
                }else{
                    return;
                }
            }else{
                if(i==n-1 && j!=n-1){//columna y NO ultima pos
                    int sumParcial = 0;
                    for(int s=0;s<n-1;s++){
                        sumParcial+=M[s][j];
                    }
                    int necesito = cteMagica - sumParcial;
                    if(necesito < n*n+1 && r.count(necesito) == 1){
                        M[i][j] = necesito;
                        r.erase(necesito);
                        BT(M,i,j+1,r,k);
                        M[i][j]=0;
                        r.emplace(necesito);
                    }else{
                        return;
                    }
                }else{
                    ///todo el codigo

                    //calculo las sumas parciales de las filas y col
                    int parcialFil = 0;
                    int parcialCol = 0;
                    for(int s=0;s<n;s++){
                        parcialFil += M[i][s];
                        parcialCol += M[s][j];
                    }

                    for(int l =1; l<n*n+1; l++){
                        if(r.count(l)==1){
                            ///si agregndo l me paso de la cte
                            if(parcialCol+l > cteMagica || parcialFil+l > cteMagica){
                                continue;
                            }

                            ///veo si l + sumParcial + max(r) < cteMagica
                            if(j==n-2){
                                if(l + parcialFil +  *(r.rbegin()) < cteMagica){
                                    continue;
                                }
                            }
                            if(i==n-2){
                                if(l + parcialCol + *(r.rbegin()) < cteMagica){
                                    continue;
                                }
                            }


                            M[i][j] = l;
                            r.erase(l);
                            if(i < n && j == n-1){ // me mantengo en rango y paso a hacer bt con la sig pos
                                BT(M, i+1, 0, r, k);
                            }else{
                                BT(M, i, j+1, r, k);
                            }
                            M[i][j]=0;
                            r.emplace(l);
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int n;
    int k;
    cin >> n >> k;

    set<int> r;
    for(int i = 1; i < (n*n) + 1; i++){//set de restantes
        r.insert(i);
    }


    vector<vector<int>> M(n,vector<int>(n,0));
    BT(M,0,0,r,k);
    if(k <= contador){
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                cout << res[i][j] <<" ";
            }
            cout << endl;
        }
    }else{
        cout << -1 << endl;
    }
}