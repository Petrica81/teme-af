#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("cuvinte.in");

//functie pentru a calcula distanta
int LevDist(string cuv1, string cuv2){
    int n = cuv1.length(), m = cuv2.length();
    vector<vector<int>> matrice(1,{0});

    for(int j = 1; j <= m; j++)
        matrice[0].push_back(j);
    for(int i = 1; i <= n; i++)
        matrice.push_back({i});

    int aux;
    for(int i = 1; i <= n; i++)
        for(int j = 1; j <= m ; j++){
            if(cuv1[i-1] == cuv2[j-1]) aux = 0;
            else aux = 1;
            matrice[i].push_back(min(matrice[i-1][j] + 1, min(matrice[i][j-1] + 1, matrice[i-1][j-1] + aux)));
        }
    return matrice[n][m];
}

//algortimul facut de mine are complexitatea O((n+m)^2+n^3)
//n= numar cuvinte
//m = lungimea maxima a unui cuvant
int main() {
    //declar si citesc datele
    int k;
    cin>>k;
    vector<string> cuvinte;
    string aux;
    while(fin>>aux)
        cuvinte.push_back(aux);
    int n = cuvinte.size();
    fin.close();

    //declar matricea pentru distante si vectorul de clase
    vector<vector<int>> dist(n, vector<int> (n,0));
    vector<vector<int>>clase(n);
    for(int i = 0; i < n; i++) {
        clase[i].push_back(i);//indicele multimii in care sunt cuvintele
        clase[i].push_back(i);//indicele cuvantului
    }

    //inserez distantele in matrice
    for(int i = 0; i < n; i++) {
        for (int j = i; j < n; j++){
            if(i != j)dist[i][j] = LevDist(cuvinte[i],cuvinte[j]);
        }
    }

    for(int i_clas = 0 ; i_clas < n - k; i_clas++){
        int minim = 1000000,c1,c2;
        for(int i = 0; i < n; i++)
            for(int j = i+1; j < n; j++)
                if(dist[i][j] < minim && clase[i][0] != clase[j][0]){//daca gasesc o distanta mai mica intre doua cuvinte din clase diferite
                    //salvez indicii cuvintelor si actualizez minimul
                    minim = dist[i][j];
                    c1 = clase[i][0];
                    c2 = clase[j][0];
                }
        //pentru toate cuvintele din clasa care o sa dispara
        //le actualizez indicele in clase si dupa ce le-am mutat , le sterg
        for(int i = 1; i < clase[c2].size(); i++){
            clase[clase[c1][0]].push_back(clase[c2][i]);
            clase[clase[c2][i]][0] = clase[c1][0];
        }
        clase[c2].erase(clase[c2].begin()+1,clase[c2].end());
    }

    //caut distanta minima actuala, daca as fi luat minimul anterior ar da incorect cand minimul este ultimul de tipul lui
    int k2= 100000;
    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            if(dist[i][j] < k2 && clase[i][0] != clase[j][0]){
                k2 = dist[i][j];
            }

    //afisare
    for(int i = 0; i < n; i++) {
        if(clase[i].size() > 1){
            for (int j = 1; j < clase[i].size(); j++) {
                cout << cuvinte[clase[i][j]] << " ";
            }
            cout<<'\n';
        }
    }
    cout<< k2<<'\n';
    return 0;
}

