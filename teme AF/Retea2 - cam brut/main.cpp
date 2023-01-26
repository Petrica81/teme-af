#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <iomanip>
using namespace std;

#define nrmare 100000000

ifstream fin("retea2.in");
ofstream fout("retea2.out");

//functie pentru distanta ca sa nu o scriu mereu
double dist(pair<int,int> x, pair<int,int> y){
    return sqrt(pow(1.0*(x.first - y.first),2) + pow(1.0*(x.second - y.second), 2));
}

//Crearea distantelor initiale ma costa O(n*m) , iar procesul de rezolvare O(m*m)
int main() {
    // Citire si salvare date
    int n,m;
    vector<pair<int,int>> centrale,blocuri;
    fin>>n>>m;
    for(int i = 0; i < n ; i++){
        int x,y;
        fin >>x>>y;
        centrale.push_back(make_pair(x,y));
    }
    for(int i = 0; i < m ; i++){
        int x,y;
        fin >>x>>y;
        blocuri.push_back(make_pair(x,y));
    }
    fin.close();

    // Rezolvare
    vector<double> distante(m,1000000); //distantele de la blocuri la o sursa
    //calculez distantele de la centrale la blocuri
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            if(dist(centrale[i],blocuri[j]) < distante[j])
                distante[j] = dist(centrale[i],blocuri[j]);

    //
    double total = 0;
    vector<bool> vizitat(m,0);
    for(int j = 0; j < m; j++){//aplic algoritmul de atatea ori cate blocuri am
        double minim = nrmare;
        int bloc = 0;
        for(int i = 0; i < m; i++)//parcurg vectorul de blocuri nevizitate si salvez minimul actual
            if(vizitat[i] == 0 && distante[i] < minim){
                bloc = i;
                minim = distante[i];
            }
        vizitat[bloc] = 1;
        total += minim; //il adaug in costul total
        //acum reactualizez costurile pentru blocurile nevizitate, in caz ca este mai eficient sa il leg la blocul nou adaugat
        for(int i = 0; i < m; i++)
            if(!vizitat[i])
                if(dist(blocuri[i],blocuri[bloc]) < distante[i])
                    distante[i] = dist(blocuri[i],blocuri[bloc]);
    }
    fout<<fixed<<setprecision(6)<<total;
    return 0;
}
