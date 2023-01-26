#include <iostream>
#include <vector>

using namespace std;
//Complexitate O(n*m), n,m reprezentand lungimile sirurilor
string shortestCommonSupersequence(string str1, string str2) {
    int n = str1.size(), m = str2.size();
    vector<vector<int>> matrice(n+1, vector<int> (m+1, n+m)); //creez matricea plina de valori = m+n
    //pentru fiecare element , daca indicii -1 din cuvinte sunt egali , iau elementul anterior de pe diagonala -1, altfel
    // iau minimul dintre cel din stanga si cel de deasupra
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= m; j++){
            if(str1[i-1] == str2[j-1]) matrice[i][j] = matrice[i-1][j-1] - 1;
            else matrice[i][j] = min(matrice[i-1][j],matrice[i][j-1]);
        }
    }

    string raspuns = "";//solutia mea
    if(matrice[n][m] == n+m) return str1 + str2;//daca ultimul element este m+n inseamna ca nu au nimic in comun
    else{
        string aux = ""; //tot solutia dar in ordine inversa o sa se salveze
        //parcurg matricea de la coada la capat si salvez in aux fiecare litera prin care am trecut
        int i = n, j = m;
        while(i != 0 && j != 0){
            //am de ales daca ma duc in sus, stanga sau pe diagonala
            if(matrice[i-1][j] == matrice[i][j]){
                aux += str1[i-1];
                i--;
            }
            else if(matrice[i][j-1] == matrice[i][j]){
                aux += str2[j-1];
                j--;
            }
            else if(matrice[i-1][j-1] == matrice[i][j] + 1){//ma duc pe diagonala in ultimul caz
                aux += str1[i-1];
                i--;
                j--;
            }
        }
        //nu termin in coltul din stanga al matricei , asa ca este nevoie sa aduc fiecare indice pana la zero
        while(i != 0){
            aux += str1[i-1];
            i--;
        }
        while(j != 0){
            aux += str2[j-1];
            j--;
        }
        //salvez inversul lui aux in raspuns
        for( i = aux.size()-1; i >= 0; i--)
            raspuns += aux[i];
    }
    return raspuns;
}
int main() {
    string s1 = "dumlab", s2 = "lal";
    cout<<shortestCommonSupersequence(s1,s2);
    return 0;
}
