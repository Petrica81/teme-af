#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin ("harta.in");
ofstream fout ("harta.out");

//Complexitatea algotirmului este O(N*N * M^2) N =  numar de noduri dat ca input , M =  numarul de muchii TOTAL
//Creez un cuplaj in care dublez nodurile(nodurile din stanga sunt conectate cu toate din dreapta inafar de el insusi prin capacitate 1)
//leg nodurile din stanga la o sursa prin capacitati egale cu gradele exterioare ale lor
//leg nodurile din dreapta la nodul final prin capacitati egale cu gradele interioare.
int n,m;
bool BFS(vector<vector<int>>& graf, vector<vector<int>>& capacitati, vector<int>& parinte){
    vector<bool> vizitat;
    vizitat.resize(n+m+2, false);
    queue<int> q;
    q.push(0);
    vizitat[0] = true;
    parinte[0] = -1;

    while(!q.empty()){
        int nod = q.front();
        q.pop();
        for(int i = 0; i < graf[nod].size(); i++){
            int nod_aux = graf[nod][i];
            if (capacitati[nod][nod_aux] > 0 && vizitat[nod_aux] == 0){
                parinte[nod_aux] = nod;
                q.push(nod_aux);
                vizitat[nod_aux] = 1;
                if(nod_aux == m+n+1) return true;
            }
        }
    }
    //daca nu ajung la destinatie returnez false
    return false;
}

int main() {
    //am refolosit in mare codul de la cuplaj asa ca am lasat cu m si n
    fin>>n;
    m = n;
    vector<vector<int>> graf, capacitati; //lista de adiacenta, respectiv matrice cu capacitati

    graf.resize(n+m+2);
    capacitati.resize(n+m+2, vector<int> (n+m+2, 0));

    for(int i = 1; i <= n; i++) {
        int auxin, auxout;
        fin>>auxout>>auxin;
        capacitati[0][i] = auxout;
        graf[0].push_back(i);
        capacitati[i+n][n+m+1] = auxin;
        graf[i+n].push_back(m+n+1);
    }

    //citesc datele
    for(int i = 1; i <= n; i++){
        for(int j = n+1; j <= n+m ; j++){
            if(i != j - n){
                capacitati[i][j] = 1;
                graf[i].push_back(j);
            }
        }
    }

//    for(int i = 0; i <= n+m+1; i++){
//        for(int j = 0; j <= n+m+1 ; j++){
//            cout<<capacitati[i][j]<<" ";
//        }
//        cout<<endl;
//    }
    //rezolvare (folosesc algoritmul Edmonds–Karp)
    int flow_max = 0;
    vector<int> parinte(n+m+2);

    while(BFS(graf, capacitati, parinte)){
        int flow_curent = 100000, i = n+m+1;
        while(i != 0){
            int nod = parinte[i];
            flow_curent = min(flow_curent, capacitati[nod][i]);
            i = parinte[i];
        }
        i = n+m+1;
        while(i != 0){
            int nod = parinte[i];
            if(capacitati[i][nod] == 0) graf[i].push_back(nod);
            capacitati[nod][i] -= flow_curent;
            capacitati[i][nod] += flow_curent;
            i = parinte[i];
        }
        flow_max += flow_curent;
    }
    fout<<flow_max<<'\n';

    for(int i = 1; i <= n; i++)
        for(int j = 0; j < graf[i].size(); j++)
            if(capacitati[i][graf[i][j]] == 0 && graf[i][j] > n) {
                fout << i << " " << graf[i][j] - n;
                fout<<'\n';
            }
}
