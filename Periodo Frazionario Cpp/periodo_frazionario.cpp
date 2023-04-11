#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>

using namespace std;

ostream &operator << (ostream &out, const vector<int> &vec);
istream &operator >> (istream &in, vector<int> &vec);

int periodNaive(string str);
int periodSmart(string str);
int periodNaiveSub(string str);

string generateStringFromLength(int len);

int main(int argc, char const *argv[]) {
    string str = "";
    int len = 0;

    cin >> len;

    str = generateStringFromLength(len);

    cout << "Generated string: " << str << endl;

    cout << "Naive: " << periodNaive(str) << endl;
    cout << "Naive (Sub): " << periodNaiveSub(str) << endl;
    cout << "Smart " << periodSmart(str) << endl;
    

    return 0;
}

// Calculate min period of string with substring (Naive)
int periodNaiveSub(string str){
    int n = str.size();
    int p, x;

    for(p=1; p<n; p++){
        if(p<=n/2){x=p;}else{x=n-p;}

        int j=0;
        while((j+x)<n && str.substr(j,x)==str.substr(j+p,x)){
            j+=p;

            if((j+x+x)>n){ x=n-j-x; }
            if(x==0){return p;}
        }

        if((j+x)>=n){
            return p;
        }
    }
    return p;
}

// Calculate min period of a string (Naive)
int periodNaive(string str) {
    int p, j;
    
    for (p = 1; p < str.size(); p++) {
        for (j = p+1; j < str.size()+1 && str.at(j-1) == str.at(j-p-1); j++) {
            if (j == str.size()) return p;
        }
        
    }
    return p;
}

// Calculate min period of a string (Smart)
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

// Generate a string from length
string generateStringFromLength(int len){
    srand(time(NULL));
    string str = "";
    int period = rand() % (len - 1) + 1;

    // Generate period
    for (int i = 0; i < period; i++) {
        char c = rand() % 3 + 97;
        str.push_back(c);
    }
    
    // Copy period
    for (int i = period; i < len; i++) {
        str.push_back(str.at(i % period));
    }
    
    cout << "Generated period: " << period << endl;

    return str;
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