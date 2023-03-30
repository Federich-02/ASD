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

// Calculate fractionary period of a string
int periodNaive(string str) {
    for (int p = 0; p < str.length(); p++){
        if (str.substr(1, str.length() - p) == str.substr(p + 1, str.length())){
            return p;
        }
    }

    return -1;
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