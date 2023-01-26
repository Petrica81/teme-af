#include <iostream>
#include <vector>
#include <queue>

using namespace std;

//complexitatea este O(n+m)
class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        //declar si creez graful
        vector<vector<pair<int,int>>> graf(n);
        for(auto& i: flights)
            graf[i[0]].push_back({i[2],i[1]});//cost, nod

        queue<vector<int>> BFS;
        // o sa folosesc BFS pentru rezolvare, acesta o sa retina nodul, costul pana la nod si cati pasi am facut
        vector<int> dist(n,1000000);
        // in loc de un vector de vizitat o sa folosesc un vector de distante
        // deoarece vreau sa trec de mai multe ori printr-un nod doar daca am un cost mai mic
        //nu tinem cont de cate aterizari am facut sau mai avem , distantele care au trecut mai devreme
        //deja au fost inserate in BFS
        dist[src] = 0;
        pair<int,int> suma = {10000000,-1}; // am adaugat si -1 sumei pentru cazul in care nu ajunge la destinatie
        BFS.push({src,0,0}); // nod, cost(suma),  al catelea este
        while(!BFS.empty()){//cat timp am elemente in BFS
            auto nod = BFS.front();
            BFS.pop();
            if(nod[0] == dst && nod[1] < suma.first)
                //dacaam ajuns la destinatie salvez costul si nodul
                //daca le aveam deja ,dar costul este unul mai mic , atunci le updatez
                suma = {nod[1],nod[0]};

            else if(nod[2] <= k)//daca inca nu mi-am atins numarul limita de opriri si nici nu este nod final
                for(auto& i: graf[nod[0]]) //verific pentru toti vecinii
                    if( nod[1] + i.first < dist[i.second]){// daca costul este mai mic , actualizez si il inserez in BFS
                        BFS.push({i.second,nod[1]+i.first, nod[2]+1});
                        dist[i.second] = nod[1] + i.first;
                    }
        }
        if(suma.second == -1) return -1; //inseamna ca nu am ajuns la destinatie
        return suma.first; //costul pana la destinatie
    }
};
int main(){
    return 0;
}