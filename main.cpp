#include <iostream>
#include <string>
//#include <cmath>
using namespace std;

string** Excel;
int filas, columnas;

void solicitarEspacio(){
    cin>>columnas>>filas;
    Excel= new string*[filas];
    for (int i = 0; i < filas; ++i)
        Excel[i] = new string[columnas];
}

void rellenarDatos(){
    string expresion;
    for (int i = 0; i < filas; ++i){
        for (int j = 0; j < columnas; ++j) {
            cin >> Excel[i][j];
        }
    }
}

int posColumna(string col){
    int pos = 0;

    if(col.size() == 1) pos = col[0] - 'A';
    else if(col.size() == 2) pos = 26*(col[0]-'A' +1) + (col[1]-'A');
    else pos = 26*26*(col[0]-'A' +1) + 26*(col[1]-'A' +1) + (col[2]-'A');

    /* Algoritmo General
    int length = col.size()-1;
    int factor;
    for(int i = length; i > 0;--i){
        factor = pow(26,i);
        pos+= factor*(col[length - i]-'A' + 1);
    }
    pos+= col[length] - 'A';
    */

    return pos;
}

pair<int,int> posicionCelda(string expresion){
    int nRow, nCol;
    for (int i = 0; i < expresion.size(); ++i) {
        if(isdigit(expresion[i])){
            string row = expresion.substr(i, expresion.size() - i);
            nRow = stoi(row) - 1;
            nCol = posColumna(expresion.substr(0, i));
            break;
        }
    }
    pair<int,int> pos(nRow,nCol);
    return pos;
}

string resolverCelda(int posX, int posY){
    if(Excel[posX][posY][0]=='='){
        string expresion = Excel[posX][posY];
        pair<int,int> posiciones;
        int value = 0;
        int aux=0;

        for (int i = 1; i < expresion.size() - 1; ++i) {
            if(expresion[i]=='+'){
                posiciones = posicionCelda(expresion.substr(i - aux,aux));
                value+=stoi(resolverCelda(posiciones.first,posiciones.second));
                aux = 0;
            }
            else aux++;
        }
        posiciones = posicionCelda(expresion.substr(expresion.size()- 1 - aux,aux+1));
        value+=stoi(resolverCelda(posiciones.first,posiciones.second));

        Excel[posX][posY] = to_string(value);

        return Excel[posX][posY];
    }
    return Excel[posX][posY];
}

void resolverExcel(){
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas - 1; ++j) {
            cout<< resolverCelda(i,j) <<" ";
        }
        cout<<resolverCelda(i,columnas-1)<<endl;
    }

}

int main(){
    int num;
    cin>>num;
    for (int i = 0; i <num; ++i) {
        solicitarEspacio();
        rellenarDatos();
        resolverExcel();
        Excel = nullptr;
    }

}
