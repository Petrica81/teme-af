#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ifstream fin("easygraph.in");
ofstream fout("easygraph.out");

//complexitatea este O(N+M) pentru un test
long long n,maxim;
void dfs(long long nod, vector<vector<long long>> &graf){
    //ma duc cat de "adanc" pot din nodul actual si pe drumul de intoarcere
    // daca  lantul pana de la coada pana la cel actual este pozitiv, atunci schimb valoarea nodului actual
    // adaugand maximul
    long long maxaux = 0;
    for(long long i = 1; i < graf[nod].size(); i++) {
        dfs(graf[nod][i], graf);
        if (maxaux < graf[graf[nod][i]][0])
            maxaux = graf[graf[nod][i]][0];
    }

    //elimin muchiile dupa ce am trecut prin ele deja , oricum mai am nevoie de graf
    graf[nod].resize(1);

    if(maxaux > 0)
        graf[nod][0] = graf[nod][0] + maxaux;
    if(maxim < graf[nod][0])
        maxim = graf[nod][0];
}
int main() {
    long long t,m;
    fin>>t;
    while(t){
        fin>>n>>m;
        //pe pozitia 0 pentru fiecare nod o sa retin valoarea nodului
        vector<vector<long long>> graf(n+1,{0});
        for(long long i = 1; i <= n; i++)
            fin>>graf[i][0];
        //inserez arcele
        for(long long i = 1; i <= m; i++){
            long long x,y;
            fin>>x>>y;
            graf[x].push_back(y);
        }
        //setez maximul fiind valoare primului nod, in caz ca este mai mare , se va actualiza , iar daca nu
        // atunci el este raspunsul
        maxim = graf[1][0];
        for(long long i = 1; i <= n; i++)
            dfs(i,graf);//pentru fiecare nod aplic dfs
        fout<<maxim<<'\n';//afisez maximul
        t--;
    }
    return 0;
}
