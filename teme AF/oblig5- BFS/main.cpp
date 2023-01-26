#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

ifstream in("graf.in");
ofstream out("graf.out");
//complexitatea acestui program este O(n+m)
//solutia gasita de mine prezinta un BFS doar ca adaugam toate punctele de control la inceputul lui cu distanta 0
int main() {
    int n,m;
    in>>n>>m;
    vector<vector<int>> graf(n+1);
    queue<int> s;// ma refer la BFS
    vector<int> grad(n+1, -1);// gradul este -1 la inceput ca sa imi pot da seama daca are deja un grad sau nu
    int aux;
    for(int i = 0; i < m; i++){
        int y;
        in>>aux>>y;
        graf[aux].push_back(y);
        graf[y].push_back(aux);
    }
    while(in>>aux){//citesc punctele de control;
        s.push(aux);
        grad[aux] = 0;
    }
    while(s.size()){// cat timp am elemente in BFS (lucrez pe primul element)
        for(int i = 0; i < graf[s.front()].size(); i++){ // pentru toate nodurile adiacente primului nod din BFS
            if(grad[graf[s.front()][i]] == -1){ // daca nu are gradul setat
                grad[graf[s.front()][i]] = grad[s.front()] + 1; // ii atribui gradul nodului curent + 1
                s.push(graf[s.front()][i]);// il adaug in BFS
            }
        }
        s.pop(); // il elimin din BFS deoarece nu mai am nevoie de el
    }
    for(int i = 1; i <= n; i++)
        out<<grad[i]<<" ";
    return 0;
}
/*Drum elementar = nu se repeta noduri
Drum simplu = nu se repeta muchii
Graf partial = putem elimina muchii
Subgraf  = putem elimina noduri
Graf biconex -> graf care nu are noduri critice
Graf tare conex -> graf in care exista drum de la x la y, oricare ar fi x si y varfuri
Nr max muchii graf bipartit: par(n^2 / 4) impar(n + 1)(n - 1) / 4
Graf transpus (doar pe graf orientat) = inversam sensul muchiilor
Graf complementar = daca avem muchie -> eliminam
        = daca nu aveam original -> add
V = vertices;
E = edges;
Complexitate BFS and DFS -> O(V + E)
BFS -> arborele de inaltime minima

Muchie critica -> niv_min[j] > niv[i], unde j este fiu a lui i.
Nod critic -> radacina -> are cel putin 2 fii in arborele DF
	    -> alt nod -> are cel putin un fiu j cu niv_min[j] >= niv[i]
Complexitate algoritm muchii/noduri critice: O(V + E)
Complexitate Sortare Topologica -> O(V + E)
Complexitate Kruskal -> O(E log V)
Complexitate Prim -> O(V^2) or O(E log V)
Complexitate Dijkstra -> O(V^2) or O(E log V)
Complexitate Bellman-Ford -> O(E * V)
Complexitate Distante minime in DAG -> O(V+E)
Complexitate Floyd-Warshall -> O(V^3)
Complexitate Edmonds-Karp -> O(V*E^2)
Complexitate algoritmul lui Mickey Mouse ( Hierholzer ) -> O(E)
Taietura in retea -> este o bipartitie a multimii varfurilor a.i. Sursa si destinatia sunt in partitii diferite
Daca graful nu este biconex => nu este hamiltonian
Graf eulerian -> are toate nodurile de grad par
Algoritm verificare graf hamiltonian -> O(n^2 * 2^n)
*/