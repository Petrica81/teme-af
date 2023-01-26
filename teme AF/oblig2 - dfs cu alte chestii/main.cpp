#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//Complexitatea solutiei mele este O(n+m)
//Incepand de la primul nod din sirul dat, rulez DFS cautand daca exista elementul urmator astfel incat sa coincida cu un DFS
int main() {
    //declar variabilele necesare si citesc datele
    int n,m;
    cin>>n>>m;
    vector<vector<int>> graf(n+1);
    queue<int> drum; // permutarea pe care vreau sa o gasesc
    vector<bool> vizitat(n+1,0); // pentru a marca nodurile prin care am trecut
    vector<int> DFS(1,-1);
    for(int i = 0; i < n; i++){
        int x;
        cin>>x;
        drum.push(x);
    }
    for( int i = 0; i < m; i++){
        int x,y;
        cin>>x>>y;
        graf[x].push_back(y);
        graf[y].push_back(x);
    }
    int nod,mai_am;
    bool gasit;
    //de aici incepe rezolvarea
    while(drum.size() != 1){
        // primul nod o sa fie primul din sir , acesta este cu siguranta in pozitia corecta
        // deoarece de la el incep parcurgerea
        DFS.push_back(drum.front());
        vizitat[drum.front()] = 1; // il marchez
        drum.pop(); // il scot din sirul dat
        nod = DFS.size()-1; // vreau pozitia ultimului element din DFS
        gasit = 0; // resetez valoarea pentru fiecare nod cautat
        mai_am = 0; // o variabila care imi zice daca mai am noduri neparcurse adiacente cu nodul actual
        while(nod != 0 && gasit == 0){ // cat timp nu am gasit nodul urmator cautat si mai am elemente in DFS neverificate
            for(int i = 0; i < graf[DFS[nod]].size(); i++){//parcurg nodurile adiacente , nodului curent din DFS
                if(graf[DFS[nod]][i] == drum.front()) gasit = 1; // daca il gasesc , memorez ca l-am gasit
                if(vizitat[graf[DFS[nod]][i]] == 0) mai_am = 1; // daca am cel putin  un nod adiacent nevizitat, memorez acest lucru
            }
            if(mai_am == 1 && gasit == 0){
                //daca am noduri adiacente nevizitate , dar niciunul nu este cel cautat , atunci se termina procesul
                cout<<0;
                return 0;
            }
            if(mai_am == 0){
                //daca nu mai am noduri adiacente nevizitate pentru nodul curent atunci il sterg din DFS pentru a nu-l parcurge din nou
                DFS.erase(DFS.begin()+nod);
                nod--; //scad pozitia cu 1 deoarece am sters un element;
            }
        }
        //daca nu l-am gasit in toata parcurgerea de mai sus inseamna ca sunt 2 componenete conexe diferite
        if(gasit == 0){
            cout<<0;
            return 0;
        }
    }
    //daca totul a mers bine , felicitari, este posibil
    cout<<1;
    return 0;
//    4 6
//    1 4 2 3
//    1 2
//    1 3
//    1 4
//    3 2
//    4 2
//    3 4
}