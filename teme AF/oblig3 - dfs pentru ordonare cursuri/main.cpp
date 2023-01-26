#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//a)
//complexitatea acestui program este O(n+m) deoarece parcurg doar o data fiecare nod si arcele acestuia
bool DFS (int nod, vector<vector<int>>& graf, vector<int>& drum, vector<int>& vizitat){
    vizitat[nod] = 1; //marchez cursul vizitat
    for(int i = 0; i < graf[nod].size(); i++){
        int x = graf[nod][i]; // ca sa nu mai scriu graf[nod][i] de 3 ori
        if(vizitat[x] == 1) return 1; //daca cursul urmator era deja vizitat inseamna ca am dat de o bucla
        if(vizitat[x] == 0 && DFS(x,graf,drum,vizitat))return 1; // daca nu , atunci aplic acelasi algoritm pe cursul urmator
    }
    vizitat[nod] = -1; // dupa ce am parcurs cursurile pana la ultimul , le marcam cu -1
                        // pentru ca in caz ca apelam DFS petntru un curs care era anterior acestora, sa nu intoarca ca am bucla
    drum.push_back(nod); //inserez cursul in lista mea
    return 0;
}
vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites){
    //creez graful meu , de la un curs exista arce catre cursurile care sunt urmate dupa el
    vector<vector<int>> graf(numCourses);
    for(int i = 0; i < prerequisites.size(); i++)
        graf[prerequisites[i][1]].push_back(prerequisites[i][0]);
    vector<int> drum;// in drum salvez ordinea inversa cautata pentru a urma toate cursurile
    vector<int> vizitat(numCourses,0);
    for(int i = 0; i < numCourses; i++)//pentru fiecare curs nevizitat apelez DFS
        if(vizitat[i] == 0 && DFS(i,graf,drum,vizitat)) return {};
    reverse(drum.begin(),drum.end()); // "rasucesc" vectorul
    return drum;
}



//b)
//b-ul este identic cu a-ul doar ca mai iau o variabila "bucla" care ma atentionezeaza sa ma opresc
// si retine un primul curs din bucla
bool DFS2 (int nod, vector<vector<int>>& graf, vector<int>& drum, vector<int>& vizitat, int& bucla){
    vizitat[nod] = 1;
    for(int i = 0; i < graf[nod].size(); i++){
        // in acest DFS inserez elementele in drum doar daca este drumul cu bucla
        int x = graf[nod][i];
        if(vizitat[x] == 1) {
            bucla = x;
            drum.push_back(nod);
            return 1;
        }
        if(vizitat[x] == 0 && DFS2(x,graf,drum,vizitat,bucla)) {
            drum.push_back(nod);
            return 1;
        }
    }
    vizitat[nod] = -1;
    return 0;
}

vector<int> findOrder2(int numCourses, vector<vector<int>>& prerequisites){
    vector<vector<int>> graf(numCourses);
    for(int i = 0; i < prerequisites.size(); i++)
        graf[prerequisites[i][1]].push_back(prerequisites[i][0]);
    vector<int> drum;
    vector<int> vizitat(numCourses,0);
    int bucla;
    for(int i = 0; i < numCourses; i++)
        if(vizitat[i] == 0 && DFS2(i,graf,drum,vizitat,bucla)) {
            reverse(drum.begin(),drum.end()); // "rasucesc" vectorul ca sa am cursurile dinafara buclei la inceput
            drum.push_back(bucla); // inserez la final bucla
            while(drum[0] != bucla) drum.erase(drum.begin());// elimin elementele pana la primul nod din bucla
            return drum;
        }
    return {};  //daca nu exista nicio problema, retunez sirul vid
}

int main() {
//    vector<int> rez;
//    vector<vector<int>> muchii = {{1,0},{2,1},{3,2},{4,3},{5,4},{6,5},{3,6}};
//    rez = findOrder2(7,muchii);
//    for( int i = 0; i < rez.size(); i++) cout<<rez[i]<<" ";
    return 0;
}
