#include <iostream>
#include <map>
#include <vector>

using namespace std;
//Complexitate O(N+M) deoarece in mare parte fac doar un dfs
map<int,vector<int>> graf;
map<int,int> out,in;
void dfs(int nod,vector<int>& vaux){
    while(out[nod]!=0){
        out[nod]--;//scad gradul
        //selectez ultimul nod in care se poate duce nodul meu
        int v = graf[nod][out[nod]];
        dfs(v,vaux);//continui dfs pe urmatorul nod
    }
    //salvez nodul in vaux(sunt in ordine inversa)
    vaux.push_back(nod);
}
vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
    //salvez perechile sub forma unei liste de adiacenta, dar din moment ce nu am noduri consecutive, folosesc map
    //in si out reprezinta gradul de intrare, respectiv de iesire pentru fiecare nod;
    for(auto i: pairs){
        graf[i[0]].push_back(i[1]);
        out[i[0]]++;
        in[i[1]]++;
    }

    //caut nodul cu care sa incep(trebuie ca gradul lui extern - intern sa fie 1, sau daca nu exista(toate au gradul par) atunci iau primul nod
    int start = out.begin()->first;
    for(auto i: out){
        if(i.second - in[i.first] == 1) start = i.first;
    }

    //aplic dfs si salvez ordinea in care s-au parcurs nodurile in 'vaux'
    vector<int> vaux;
    dfs(start,vaux);

    vector<vector<int>> sol;
    int prev = *--vaux.end();
    //formez vectorul meu solutie
    for(int i = vaux.size()-2; i >= 0; i--){
        sol.push_back({prev,vaux[i]});
        prev = vaux[i];
    }

    return sol;
}

int main() {
    vector<vector<int>> pairs = {{5,1},{4,5},{11,9},{9,4}};
    pairs = validArrangement(pairs);
    for(int i = 0; i < pairs.size(); i++){
        cout<<"["<<pairs[i][0]<<", "<<pairs[i][1]<<"], ";
    }
    return 0;
}
