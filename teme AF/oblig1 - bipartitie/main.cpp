#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//a)
// Complexitatea gasita de mine este O(n+m)
bool possibleBipartition(int n, vector<vector<int>> dislikes) {
    //creez un graf in care perechile din dislikes sunt muchiile dintre noduri
    vector<vector<int>> graf(n+1);
    vector<int> culori(n+1,0);
    for( int i = 0 ; i < dislikes.size(); i++){
        graf[dislikes[i][0]].push_back(dislikes[i][1]);
        graf[dislikes[i][1]].push_back(dislikes[i][0]);
    }
    //aplic parcurgerea in latime pentru a incerca sa il "colorez"
    queue<int> BFS;
    for(int i = 1; i <= n; i++){//trec prin fiecare nod deoarece putem avea mai multe componente conexe
        if(culori[i] == 0){ //daca nu este colorat inca inseamna ca nu am parcursc componenta conexa
            BFS.push(i);// inserez primul nod in queue ca sa incep BFS-ul de la el
            culori[i] = 1;
            while(BFS.size() != 0){//cat timp am noduri de verificat
                for(int j = 0; j < graf[BFS.front()].size(); j++){ // parcurg nodurile adaciente primului element din queue
                    if(culori[graf[BFS.front()][j]] == 0){ //daca nu este "colorat" il adaug in queue si ii atribui culoarea complementara
                        BFS.push(graf[BFS.front()][j]);
                        culori[graf[BFS.front()][j]] = 3 - culori[BFS.front()];
                    }
                    //daca are deja o culoare atribuita si coincide cu culoare nodului curent,
                    //atunci nu putem obtine un graf bipartid si se termina programul
                    else if(culori[BFS.front()] == culori[graf[BFS.front()][j]]) return 0;
                }
                BFS.pop(); //scot primul element din queue dupa ce am terminat cu vecinii lui
            }
        }
    }
    // daca nu s-a oprit pana acum , atunci colorarea s-a putut efectua complet
    return 1;
}

//b)
// pentru B solutia este identica cu cea de la a, doar ca salvez nodurile in doi vectori;
vector<vector<int>> possibleBipartition2(int n, vector<vector<int>> dislikes) {
    vector<vector<int>> graf(n+1);
    vector<int> culori(n+1,0);
    for( int i = 0 ; i < dislikes.size(); i++){
        graf[dislikes[i][0]].push_back(dislikes[i][1]);
        graf[dislikes[i][1]].push_back(dislikes[i][0]);
    }
    vector<vector<int>> rez(2); //vectorul cu grupurile
    queue<int> BFS;
    for(int i = 1; i <= n; i++){
        if(culori[i] == 0){
            BFS.push(i);
            culori[i] = 1;
            while(BFS.size() != 0){
                for(int j = 0; j < graf[BFS.front()].size(); j++){
                    if(culori[graf[BFS.front()][j]] == 0){
                        BFS.push(graf[BFS.front()][j]);
                        culori[graf[BFS.front()][j]] = 3 - culori[BFS.front()];
                    }
                    else if(culori[BFS.front()] == culori[graf[BFS.front()][j]]) return {}; // returnez un vector vid daca nu se poate
                }
                rez[2-culori[BFS.front()]].push_back(BFS.front()); // in functie de culoare selectez in ce grup inserez nodul;
                BFS.pop();
            }
        }
    }
    return rez;
}

int main() {
    vector<vector<int>> rez;
    cout<<possibleBipartition(4, {{1,2},{1,3},{2,4}})<<endl;
    cout<<possibleBipartition(1,{})<<endl;
    rez = possibleBipartition2(10, {{1,2},{1,3},{2,4},{7,8}});
    for(int i = 0; i < rez[0].size();i++){
        cout<<rez[0][i]<<" ";
    }
    cout<<endl;
    for(int i = 0; i < rez[1].size();i++){
        cout<<rez[1][i]<<" ";
    }
    cout<<endl;
    return 0;
}
