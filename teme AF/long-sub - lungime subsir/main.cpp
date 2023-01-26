#include <iostream>
#include <vector>
#include <string>

using namespace std;
//complexitatea este O(n*m) unde n,m sunt lungimile lui text1, respectiv text2;
int longestCommonSubsequence(string text1, string text2) {
    vector<vector<int>> matrice(text1.size()+1, vector<int> (text2.size()+1, 0));
    // pentru fiecare element din matrice , daca literele cu indicii respectivi - 1 din fiecare cuvant sunt egale,
    // iau elementul anterior de pe diagonala + 1, altfel iau maximul dintre cel de deasupra si cel din stanga
    for(int i = 1; i <= text1.size(); i++){
        for(int j = 1; j <= text2.size(); j++){
            if(text1[i-1] == text2[j-1]) matrice[i][j] = matrice[i-1][j-1] + 1;
            else matrice[i][j] = max(matrice[i-1][j],matrice[i][j-1]);
        }
    }
    //returnez ultimul element din matrice
    return matrice[text1.size()][text2.size()];
}
int main() {
    string text1 = "abcde", text2 = "ace";
    cout<<longestCommonSubsequence(text1, text2);
}
