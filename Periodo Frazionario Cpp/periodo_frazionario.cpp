#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

ostream &operator << (ostream &out, const vector<int> &vec);
istream &operator >> (istream &in, vector<int> &vec);

int periodNaive(string str);
int periodSmart(string str);

int main(int argc, char const *argv[]) {
    string str = "";

    cin >> str;

    cout << periodNaive(str)<<endl;
    cout << periodSmart(str)<<endl;

    return 0;
}

// Calculate fractionary period of a string in naive mode
int periodNaive(string str) {
    int p, j;
    
    for (p = 1; p < str.size(); p++) {
        for (j = p+1; j < str.size()+1 && str.at(j-1) == str.at(j-p-1); j++) {
            if (j == str.size()) return p;
        }
        
    }
    return p;
}
int periodSmart(string str){
    int n = str.length();
    vector<int> r(n, 0);
    
    for (int i = 1; i < n; i++) {
        int j = r[i-1];
        while (j > 0 && str.at(i) != str.at(j)) {
            j = r[j-1];
        }
        if (str.at(i) == str.at(j)) {
            r[i] = j+1;
        }
    }

    int p = n - r[n-1];
    return p;
}


ostream &operator << (ostream &out, const vector<int> &vec) {
    for (int i = 0; i < vec.size(); i++)
        out << vec[i] << " ";
    return out;
}

istream &operator >> (istream &in, vector<int> &vec) {
    // scan line of text 
    string line;
    getline(in, line);

    // convert line of text into a new input stream
    istringstream is(line);
    
    // convert new input stream into array
    int value;
    while (is >> value)
        vec.push_back(value);

    return in;
}