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

    cout << periodNaive(str);

    return 0;
}

// Calculate fractionary period of a string in naive mode
int periodNaive(string str) {
    int p = 0;
    int j = 0;
    
    for (p = 1; p <= str.size(); p++) {
        for (j = p+1; j <= str.size(); j++) {
            if (str.at(j) != str.at(j-p))
                break;
        }
        if (j == str.size())
            return p;
    }
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