#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

ifstream fin ("maxflow.in");
ofstream fout ("maxflow.out");

//Complexitatea algotirmului este O(N^2 * M)
// Pentru a folosesc Algoritmul lui Dinic pentru max flow,
// iar pentru b mai aplic o data BFS pe graful rezidual si iau toate muchiile dintre un nod vizitat si unul nevizitat
int n;
bool BFS(vector<vector<int>>& graf, vector<vector<int>>& capacitati, vector<int>& nivel){
    for(int i = 2; i <= n; i++)
        nivel[i] = -1;
    nivel[1] = 0;

    queue<int> q;
    q.push(1);

    while(!q.empty()){
        int nod = q.front();
        q.pop();
        for(int i = 0; i < graf[nod].size(); i++){
            int nod_aux = graf[nod][i];
            if (capacitati[nod][nod_aux] > 0 && nivel[nod_aux] < 0){
                nivel[nod_aux] = nivel[nod] + 1;
                q.push(nod_aux);
            }
        }
    }
    //daca nu ajung la destinatie returnez false
    if(nivel[n] < 0) return false;
    else return true;
};

void BFS_cut(vector<vector<int>>& graf, vector<vector<int>>& capacitati,vector<pair<int,int>>& muchii){
    //rulez un BFS pentru a vedea toate nodurile pe care le pot atinge
    queue<int> q;
    q.push(1);
    vector<int> vizitat(n+1,0);
    while(!q.empty()){
        int nod = q.front();
        q.pop();
        for(int i = 0; i < graf[nod].size(); i++){
            int nod_aux = graf[nod][i];
            if (capacitati[nod][nod_aux] > 0 && vizitat[i] == 0){
                q.push(nod_aux);
            }
        }
        vizitat[nod] = 1;
    }

    //pentru toate nodurile nevizitate vad daca au muchie catre un nod vizitat
    for(int i = 1; i <= n; i++) {
        if(vizitat[i] == 0){
            for(int j = 0; j < graf[i].size(); j++){
                if(vizitat[graf[i][j]] == 1 && capacitati[i][graf[i][j]] != 0 && capacitati[graf[i][j]][i] == 0){
                    //salvez muchia si o marchez
                    capacitati[graf[i][j]][i] = -1;
                    muchii.push_back({graf[i][j],i});
                }
            }
        }
    }
};

int trimite_flux(vector<vector<int>>& graf, vector<vector<int>>& capacitati, vector<int>& nivel, vector<int>& count, int nod , int flow){
    if(nod == n)
        return flow;
    if(count[nod] == graf[nod].size())
        return 0;

    for(auto nod2 : graf[nod]){
        if(capacitati[nod][nod2] > 0){
            count[nod]++;
            if(nivel[nod2] == nivel[nod]+1){
                int flow_aux = min(flow,capacitati[nod][nod2]);

                int capac_minima = trimite_flux(graf,capacitati,nivel,count,nod2,flow_aux);
                if(capac_minima > 0){
                    if(capacitati[nod2][nod] == 0)
                        graf[nod2].push_back(nod);
                    capacitati[nod][nod2] -= capac_minima;
                    capacitati[nod2][nod] += capac_minima;

                    return capac_minima;
                }
            }
        }
    }


    return 0;
}

int main() {
    int m;
    fin>>n>>m;

    vector<vector<int>> graf, capacitati; //lista de adiacenta, respectiv matrice cu capacitati
    graf.resize(n+1);
    capacitati.resize(n+1, vector<int> (n+1, 0));

    //citesc datele
    for(int i = 0; i < m; i++){
        int sursa,destinatie,cost;
        fin>>sursa>>destinatie>>cost;
        //daca am mai multe muchii intre aceleasi noduri, tin minte doar una si adun capacitatile
        if( capacitati[sursa][destinatie] == 0) {
            capacitati[sursa][destinatie] = cost;
            graf[sursa].push_back(destinatie);
        }
        else
            capacitati[sursa][destinatie] += cost;
    }
    //rezolvare (folosesc algoritmul lui dinic chiar daca nu este neaparat necesar)
    int flow_max = 0;
    vector<int> nivel(n+1,-1);

    while(BFS(graf, capacitati, nivel)){
        vector<int> count(n+1, 0);
        int aux = trimite_flux(graf,capacitati,nivel,count,1,10000);
        while(aux){
            flow_max += aux;
            aux = trimite_flux(graf,capacitati,nivel,count,1,10000);
        }
    }
    fout<<flow_max;

    //b)
    vector<pair<int,int>> taietura;
    BFS_cut(graf,capacitati,taietura);
    for(int i = 0; i < taietura.size(); i++)
        cout<<taietura[i].first<<" "<<taietura[i].second<<endl;
}
