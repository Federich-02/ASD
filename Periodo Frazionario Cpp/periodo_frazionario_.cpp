#include <iostream>
#include <sstream>
#include <vector>
#include <time.h>
#include <chrono>
#include <math.h>

using namespace std;
using namespace std::chrono;

#define NUM_OF_REPETITION 5


int periodNaive(string str);
int periodSmart(string str);
int periodNaiveSub(string str);

string generateStringFromLength(int len);
double getResolution();

string generateStringWorstCase(int len);

typedef duration<double, seconds::period> secs;

int main(int argc, char const *argv[]) {
    string str = "";
    int len = 0;
    double ris = getResolution();
    int count = 0;

    vector<double> algTimes = vector<double>();
    vector<double> tempAlgTimesByLen = vector<double>();

    cout << "Internal clock resolution: " << ris << endl;

    steady_clock::time_point end;
    steady_clock::time_point start;
    
    for (int i = 0; i < 100; i++) {

        len = 100 * pow(1.06478598, i);
        
        for (int j = 0; j < NUM_OF_REPETITION; j++) {
            count = 0;
            str = generateStringFromLength(len);
            
            start = steady_clock::now();
            do {
                periodSmart(str);
                count++;
                end = steady_clock::now();
            }while(duration_cast<secs>(end - start).count() <= (ris * (1/0.001 + 1)));
            
            double tempTime = (duration_cast<secs>(end - start).count()) / count;
            tempAlgTimesByLen.push_back(tempTime);
        }
        
        for(int i=0; i<tempAlgTimesByLen.size(); i++) {
            cout << fixed << tempAlgTimesByLen.at(i) << "\t";
        }

        cout << endl;

        tempAlgTimesByLen.clear();
    }
    
    return 0;
}

//////////////////////////////////////////////////////////////////////////////
// CALCULATE MIN PERIOD OF A STRING (NAIVE)
int periodNaive(string str) {
    int p, j;
    
    //Iterates from p equal to 1 up to the length of the string minus one
    for (p = 1; p < str.size(); p++) {

        //Iterates from j equal to p plus one up to the length of the string
        //If the characters identified by the two indices are the same, it passes to the j+1th character
        //If, on the other hand, they are different, the nested cycle is interrupted by continuing the external one
        for (j = p+1; j < str.size()+1 && str.at(j-1) == str.at(j-p-1); j++) {

            //If the loop reaches the end of the string, the period has been found and is returned terminating the process
            if (j == str.size()) return p;
        }
    }
    //The function terminates regardless when the outer loop reaches the length of the string
    return p;
}


//////////////////////////////////////////////////////////////////
// CALCULATE MIN PERIOD OF A STRING (SMART)
int periodSmart(string str){
    const int n = str.length();
    //A support vector r is initialized which will contain the lengths of the prefixes
    int r[n];
    //vector<int> r(n, 0);

    //Set every element of the array equal to 0
    for(int i=0;i<n;i++){
        r[i]=0;
    }
    
    //A for loop to iterate over the string and look up a prefix and suffix by updating r
    for (int i = 1; i < n; i++) {

        //Variable "j" used to keep track of the current prefix/suffix index updates based on character comparisons.
        int j = r[i-1];
        while (j > 0 && str.at(i) != str.at(j)) {
            j = r[j-1];
        }
        if (str.at(i) == str.at(j)) {
            r[i] = j+1;
        }
    }

    //Calculate the minimum period by subtracting the last value of the "r" array from the length of the string.
    int p = n - r[n-1];
    return p;
}


/////////////////////////////////////////////////////////////////////////////////////////
// GENERATE A STRING FROM A GIVEN LENGTH
// This code basically generates a period of a random length ( < len ) and copies it 
// several times until it creates the string with the required length
// Example: Length=6 Period_length=2 Period_string="ab" String="acacac" 
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

    return str;
}

/////////////////////////////////////////////////////////////////////////////////////////
// GENERATE THE WORSTE CASE FROM THE GIVEN LENGTH
// In this case the worst case is the repetition of the same letter excluding the last
// Example len: 6 -> str: "aaaaab" 
string generateStringWorstCase(int len){
    srand(time(NULL));
    string str = "";

    // Generate period
    for (int i = 0; i < len - 1; i++) {
        str.push_back('a');
    }
    str.push_back('b');

    return str;
}

//////////////////////////////////////////////
// GET THE RESOLUTION OF THE INTERNAL CLOCK
double getResolution() {
    steady_clock::time_point start = steady_clock::now();
    steady_clock::time_point end;
    do {
        end = steady_clock::now();
    } while (start == end);
    
    return duration_cast<secs>(end - start).count();
}



////////////////////////////////////////////////////////////////
// CALCULATE MIN PERIOD OF A STRING USING THE FUNCTION SUBSTRING
// Different from how it was explained in class
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