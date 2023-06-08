/*
    Arghittu Thomas
*/

#include <iostream>

using namespace std;

int editingDistance(string str1, string str2);

int main(int argc, char const *argv[]) {
    
    string str1 = "", str2 = "";

    cin >> str1;
    cin >> str2;

    cout << editingDistance(str1, str2) << endl;

    return 0;
}

// Editing distance
int editingDistance(string str1, string str2) {
    const int len1 = str1.size();
    const int len2 = str2.size();
    
    int m[len1+1][len2+1];

    int balance = 0;

    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0) {
                m[i][j] = j;
            } else if (j == 0) {
                m[i][j] = i;
            } else {
                if (str1.at(i-1) == str2.at(j-1)) {
                    balance = 0;
                } else {
                    balance = 1;
                }

                m[i][j] = min(
                        m[i-1][j] + 1,
                        min(
                            m[i][j-1] + 1,
                            m[i-1] [j-1] + balance
                        )
                    );
            }
        }
    }

    // for (int i = 0; i<len1; i++) {
    //     for (int j = 0; j<len2; j++) {
    //         cout << m[i][j] << "   ";
    //     }
    //     cout << endl;
    // }

    // cout << endl;


    return m[len1][len2];
}