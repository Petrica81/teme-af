#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin ("drumuri2.in");
ofstream fout ("drumuri2.out");

//Complexitatea algotirmului este O(N * M^2)
int n,m;
bool BFS(vector<vector<int>>& graf, vector<vector<int>>& capacitati, vector<int>& parinte){
    vector<bool> vizitat;
    vizitat.resize(n*2+2, 0);
    queue<int> q;
    q.push(0);
    vizitat[0] = 1;
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
                if(nod_aux == n*2+1) return true;
            }
        }
    }
    //daca nu ajung la destinatie returnez false
    return false;
};

int main() {
    fin>>n>>m;
    vector<vector<int>> graf, capacitati; //lista de adiacenta, respectiv matrice cu capacitati

    graf.resize(n*2+2);
    capacitati.resize(n*2+2, vector<int> (n*2+2, 0));
    //Folosesc algoritmul de cuplaj , doar ca dublez nodurile
    // si permit si trecerea din partea dreapta in stanga.
    // Leg nodurile de un nod de start pentru cuplaj
    for(int i = 1; i <= n; i++) {
        capacitati[0][i] = 1;
        graf[0].push_back(i);
    }
    // Leg nodurile dubluri de un nod final pentru cuplaj
    for(int i = n+1; i <= n*2; i++) {
        capacitati[i][n * 2 + 1] = 1;
        graf[i].push_back(n*2+1);
        //in plus , le leg si de echivalentul lor din dreapta
        graf[i].push_back(i-n);
        capacitati[i][i-n] = 1;
    }

    //citesc datele
    for(int i = 0; i < m; i++){
        int sursa,destinatie;
        fin>>sursa>>destinatie;
        capacitati[sursa][n+destinatie] = 1;
        graf[sursa].push_back(n+destinatie);
    }
    //rezolvare (folosesc algoritmul Edmonds–Karp)
    int flow_max = 0;
    vector<int> parinte(n*2+2);

    while(BFS(graf, capacitati, parinte)){
        int flow_curent = 100000, i = n*2+1;
        while(i != 0){
            int nod = parinte[i];
            flow_curent = min(flow_curent, capacitati[nod][i]);
            i = parinte[i];
        }
        i = n*2+1;
        while(i != 0){
            int nod = parinte[i];
            capacitati[nod][i] -= flow_curent;
            capacitati[i][nod] += flow_curent;
            graf[i].push_back(nod);
            i = parinte[i];
        }
        flow_max += flow_curent;
    }
    fout<<n - flow_max<<'\n';
}
