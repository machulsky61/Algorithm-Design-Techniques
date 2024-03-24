#include <iostream>
#include <list>
#include <cmath>

using namespace std;

double calcularDistancia(double r, double a){
    return sqrt(r * r - a * a);
}

int main() {
    list<pair<double, double>> distancias;
    int cantidad;
    int largo ;
    int ancho ;
    int a, b;

    while(cin >> cantidad ) {
        cin >> largo >> ancho;
        int aspersores = 0;
        distancias.clear();
        for (int i = 0; i < cantidad; i++) {
            cin >> a >> b;
            if((double)b > (double)ancho/2) {//radio es mayor o igual a la mitad del ancho
                double rango = calcularDistancia((double)b, (double) ancho / 2);
                distancias.push_back({a - rango, a + rango});
            }
        }
        
        distancias.sort();
        double puntoAnterior = 0.0;
        while (!distancias.empty() && puntoAnterior < largo) {
            pair<double, double> temp = distancias.front();
            distancias.pop_front();
            if (temp.first <= puntoAnterior) {
                for (auto &d : distancias) {
                    if (d.first <= puntoAnterior && d.second > temp.second) {
                        temp = d;
                    }
                }
                    puntoAnterior = temp.second;
                    aspersores++;
            }
        }
        aspersores = puntoAnterior >= largo ? aspersores : -1;
        cout << aspersores << endl;
    }
    return 0;
}