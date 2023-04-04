#include <iostream>
#include <sstream>
#include <vector>
#include <regex>
#include <string>

using namespace std;

// Generic node of a Binary Tree
struct node {
    int key;
    node *left;
    node *right;
    node *parent;

    node(int k) {
        key = k;
        left = nullptr;
        right = nullptr;
        parent = nullptr;
    }

    node(int k, node *left, node *right, node *parent) {
        key = k;
        left = left;
        right = right;
        parent = parent;
    }
};

ostream &operator<<(ostream &out, const vector<int> &vec);
istream &operator>>(istream &in, vector<int> &vec);
void tokenize(std::string const &str, const char delim, std::vector<std::string> &out);
void preOrderPrint(node *root);
void inOrderPrint(node *node);
void insertBST(node *&root, int k);

string readBSTfromPolishFrom();

// BST verify
void buildBSTfromPolishForm(vector<int> input, node *root);

// BST graphically print 
void printBT(const std::string& prefix, const node* node, bool isLeft);
void printBT(const node* node);

int main(int argc, char const *argv[]) {
    vector<string> input = vector<string>();

    node *root = nullptr;

    readBSTfromPolishFrom(input);

    /// Print input for debug
    // for (int i = 0; i < input.size(); i++) {
    //     cout << input[i] << " ";
    // }


    


    return 0;
}

// Insert a new key in a BST
void insertBST(node *&root, int k) {
    node *newNode = new node(k);
    
    if (root == nullptr) {
        root = *&newNode;
    } else {
        node *y = nullptr;
        node *x = nullptr;

        y = root->parent;
        x = root;

        while (x != nullptr) {
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
        }
        else {
            y->right = newNode;
        }
    }
}

// Build a BST from polish form
void buildBSTfromPolishForm(vector<int> input, node *root){
    root = new node(input.at(0));

    node *left;
    node *right;

    int len = 3;

    while (len < input.size()) {
        if (left->key != 0){
            left->left->key = input.at(len);
            left->right->key = input.at(len + 1);

            left = left->left;
            right = left->right;
        } else {
            right->left->key = input.at(len);
            right->right->key = input.at(len + 1);

            left = right->left;
            right = right->right;
        }
        len += 2;
    }
    
    
    
}

// Read BST input from polish form for build a BST
void readBSTfromPolishFrom(vector<string> &out){
    string line;

    getline(cin, line);

    tokenize(line, ' ', out);
}
 

/// COMMON OPERATION
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

void tokenize(string const &str, const char delim, vector<string> &out) { 
    // construct a stream from the string 
    stringstream ss(str); 
 
    string s; 
    while (std::getline(ss, s, delim)) { 
        out.push_back(s); 
    }
}

void printBT(const std::string& prefix, const node* node, bool isLeft){
    if( node != nullptr ) {
        std::cout << prefix;

        std::cout << (isLeft ? "|--" : "---" );

        // print the value of the node
        std::cout << node->key << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "|   " : "    "), node->right, true);
        printBT( prefix + (isLeft ? "|   " : "    "), node->left, false);
    }
}

// In-Order visit to generic tree
void inOrderPrint( node *node) {
    if (node != nullptr) {
        inOrderPrint(node->left);
        cout << node->key << " ";
        inOrderPrint(node->right);
    }
}

// Pre-Order visit to generic tree
void preOrderPrint(node *node) {
    if (node != nullptr) {
        cout << node->key << " ";
        preOrderPrint(node->left);
        preOrderPrint(node->right);
    }
}

void printBT(const node* node){
    printBT("", node, false);    
}