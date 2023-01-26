#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

ifstream fin ("disjoint.in");
ofstream fout ("disjoint.out");
int n, m;
vector<pair<int,int>> multimi;

//Complexitatea este O(log*n) pentru operatia 2 si O(1) pentru operatia 1
int radacina(int x){
    int aux = x;
    while(multimi[aux].first != 0) aux = multimi[aux].first;// il updatam pe aux pana devine primul nod din multime
    if(multimi[x].first != 0){// daca tot am gasit radacina, legam direct nodul curent la ea
        // astfel la mai multe apeluri nu o sa faca acelasi drum mereu
        multimi[x].first = aux;
        x = multimi[x].first;
    }
    return x;// returnez elementul
}
void uniune(int x, int y){
    int radx = radacina(x), rady = radacina(y);// salvam radacina de la fiecare element
    //alegem multimea mai mare
    if(multimi[radx].second > multimi[rady].second){
        multimi[radx].second += multimi[rady].second; // adaugam numarul de elemente din cea mica la cea mare
        multimi[rady].first = radx;// unim multimea mica la cea mare
    }
    else{//idem
        multimi[rady].second += multimi[radx].second;
        multimi[radx].first = rady;
    }
}

int main() {
    fin>>n>>m;
    multimi.resize(n+1, {0,1});//setam pentru toate elementele ca au inaltimea 1 si nu au "tata"
    for(int i = 1; i <= m; i++){//citesc operatiile
        int op,x,y;
        fin>>op>>x>>y;
        if(op == 1){
            uniune(x,y);
        }
        if(op == 2){
            //daca au acelasi element in "varf" atunci sunt in aceeasi multime
            if(radacina(x) == radacina(y)) fout<<"DA\n";
            else fout<<"NU\n";
        }
    }
    for(int i = 0; i < n; i++){
        cout<<multimi[i].first<<" ";
    }
    return 0;
}
