#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

/// Generic node of a Binary Tree
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

/// BST operations
void readBSTfromPolishFrom(vector<string> &out);
void buildBSTfromPolishForm(vector<string> input, node *&root);

void insertBST(node *&root, int k);

node* BSTSuccessor(node *x);
node* BSTMin(node *x);

int checkBST(node *root);

/// BST graphically print - No required
ostream &operator << (ostream &out, const vector<int> &vec);
istream &operator >> (istream &in, vector<int> &vec);

void printBT(const std::string& prefix, const node* node, bool isLeft);
void printBT(const node* node);

int main(int argc, char const *argv[]) {
    
    // -----------------------Exercise 18-----------------------
    
    vector<string> input = vector<string>();
    node *root = nullptr;

    readBSTfromPolishFrom(input);

    buildBSTfromPolishForm(input, root);

    cout << checkBST(root) << endl;
    
    return 0;
}

/// -----------------------BST operations-----------------------
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
void buildBSTfromPolishForm(vector<string> input, node *&root) {
    // Insert root (If null return)
    if (input[0] == "NULL") {
        node *newNode = new node(-1);
        root = newNode;
        return;
    } else {
        node *newNode = new node(stoi(input[0]));
        root = newNode;
    }

    // Insert all elements
    node *prec = root;

    for (int i = 1; i < input.size(); i++) {
        node *newNode = nullptr;
        
        if (input[i] == "NULL") {
            newNode = new node(-1);

            if (prec->left == nullptr) {
                prec->left = newNode;
            } else if (prec->right == nullptr) {
                prec->right = newNode;
            }
            newNode->parent = prec;
            while (prec->left != nullptr && prec->right != nullptr && i < input.size() -1) {
                prec = prec->parent;
            }
        } else {
            newNode = new node(stoi(input[i]));
            
            if (prec->left == nullptr) {
                prec->left = newNode;
            } else if (prec->right == nullptr) {
                prec->right = newNode;
            }
            newNode->parent = prec;
            prec = newNode;
        }
    }
}

// Read BST input from polish form for build a BST
void readBSTfromPolishFrom(vector<string> &out){
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

// Check a if a tree is a BST
int checkBST(node *root) {
    node *x = BSTMin(root);

    while (BSTSuccessor(x) != nullptr) {        
        if (x->key > BSTSuccessor(x)->key){
            return 0;
        }
        x = BSTSuccessor(x);
    }
    
    return 1;
}

// Find the successor of a node in BST (if not exist then return null)
node* BSTSuccessor(node *x){
    if (x->right->key != -1){
        return BSTMin(x->right);
    } else {
        node *y = x->parent;
        while (y != nullptr && x != y->left) {
            x = y;
            y = x->parent;
        }
        return y;
    }
}

// Find the node with min value of a BST
node* BSTMin(node *x){
    if (x->key != -1 && x->left->key == -1) {
        return x;
    } else {
        return BSTMin(x->left);
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
