#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

/// Generic node of a Binary Tree
struct node {
    int key;
    string alfaNumKey;
    int height;
    node *left;
    node *right;
    node *parent;

    node(int k) {
        key = k;
        left = new node(-1, nullptr, 0, nullptr, nullptr, nullptr);
        right = new node(-1, nullptr, 0, nullptr, nullptr, nullptr);
        parent = nullptr;
    }

    node(int k, string alfaNumKey, int height, node *left, node *right, node *parent) {
        key = k;
        alfaNumKey = alfaNumKey;
        height = height;
        left = left;
        right = right;
        parent = parent;
    }
};

void readCommand(vector<string> &out);

void insertAVL(node *&root, int k);
void balanceAVL(node *&root);

/// BST graphically print - No required
ostream &operator << (ostream &out, const vector<int> &vec);
istream &operator >> (istream &in, vector<int> &vec);

void printBT(const std::string& prefix, const node* node, bool isLeft);
void printBT(const node* node);

/// ---------------------------MAIN---------------------------
int main(int argc, char const *argv[]) {
    vector<string> command = vector<string>();
    bool status = true;

    node *root = nullptr;

    do {
        readCommand(command);

        if (command[0] == "insert") {

        } else if (command[0] == "find"){

        } else if (command[0] == "exit") {
            status = false;
        } else {
            cout << "Invalid command" << endl;
        }

    } while (status);
    
}

// Read BST input from polish form for build a BST
void readCommand(vector<string> &out) {
    // Get input from console
    string line;
    getline(cin, line);

    // Convert input into a new string-stream
    stringstream ss(line);

    // Convert stream into a array
    string s;
    while (getline(ss, s, ' ')) {
        out.push_back(s);
    }
}

// Insert
void insertAVL(node *&root, int k) {
    node *newNode = new node(k);
    
    if (root == nullptr) {
        root = *&newNode;
        root->height = 1;
    } else {
        node *y = root->parent;
        node *x = root;

        while (x->key != -1) {
            if (x->key > k) {
                y = x;
                x = y->left;
            } else {
                y = x;
                x = y->right;
            }
        }

        newNode->parent = y;

        if (y->key > k) {
            y->left = newNode;
        } else {
            y->right = newNode;
        }

        // Update nodes height
        // while () {

        // }
    }
}

/// -----------------------COMMON OPERATION-----------------------
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
    while (is >> value){
        
        vec.push_back(value);
    }
    return in;
}

void printBT(const node* node){
    printBT("", node, false);    
}

void printBT(const string& prefix, const node* node, bool isLeft){
    if( node != nullptr ) {
        cout << prefix;

        cout << (isLeft ? "|--" : "---" );

        // print the value of the node
        cout << "(" << node->key << ")" << endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "|   " : "    "), node->right, true);
        printBT( prefix + (isLeft ? "|   " : "    "), node->left, false);
    }
}