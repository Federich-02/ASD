/*
    Arghittu Thomas

    AVL Implementation
    
    - Manca print nella forma polacca
    - Manca cancellazione e ricerca
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

/// Generic node of a Binary Tree
struct node {
    int key;
    int height;
    node *left;
    node *right;
    node *parent;

    node(int k) {
        key = k;
        height = 1;
        left = new node(-1, 0, nullptr, nullptr, nullptr);
        right = new node(-1, 0, nullptr, nullptr, nullptr);
        parent = nullptr;
    }

    node(int k, int height, node *left, node *right, node *parent) {
        key = k;
        height = height;
        left = left;
        right = right;
        parent = parent;
    }
};

void readCommand(vector<string> &out);

node * insertAVL(node *root, int k);

node * rightRotation(node *pin);
node * leftRotation(node *pinNode);

int max(int, int);
int getHeight(node * n);

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
        // for (int i=0; i<command.size(); i++)
        //     cout << command[i];

        if (command[0] == "i") {
            root = insertAVL(root, stoi(command[1]));
            printBT(root);
        } else if (command[0] == "f"){

        } else if (command[0] == "e") {
            status = false;
        } else {
            cout << "Invalid command" << endl;
        }

        command.clear();
    } while (status);
    
    return 0;
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
node * insertAVL(node *root, int k) {
    // Insert a new node on AVL
    node *newNode = new node(k);

    newNode->height = 1;
    newNode->left->left = nullptr;
    newNode->left->right = nullptr;
    newNode->right->left = nullptr;
    newNode->right->right = nullptr;
    
    if (root == nullptr) {
        root = newNode;
    } else {
        node *y = root->parent;
        node *x = root;

        // Perform the normal BST insertion
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

        // Update height of the tree => O(log n)
        if (y->left->key == -1 || y->right->key == -1) {
            x = y;
            while (x != nullptr) {
                x->height = max(getHeight(x->left) + 1, getHeight(x->right) + 1);
                x = x->parent;
            }
        }

        // Balance AVL
        while (y != nullptr) {
            if (y->parent == nullptr)
                break;
            if (y == y->parent->left) {
                if (abs(y->height - y->parent->right->height) > 1){
                    node * yy = y->parent;
                    if (y->right == newNode) {
                        yy->left = leftRotation(y);
                    }
                    
                    if (yy == root) {
                        root = rightRotation(yy);
                    } else {
                        if (yy == yy->parent->left) {
                            yy->parent->left = rightRotation(yy);
                        } else {
                            yy->parent->right = rightRotation(yy);
                        }
                    }
                    yy = yy->parent->parent;
                    while (yy != nullptr) {
                        yy->height--;
                        yy = yy->parent;
                    }
                }
            } else {
                if (abs(y->height - y->parent->left->height) > 1){
                    node * yy = y->parent;
                    if (y->left == newNode) {
                        yy->right = rightRotation(y);
                    }

                    if (yy == root) {
                        root = leftRotation(yy);
                    } else {
                        if (yy == yy->parent->left) {
                            yy->parent->left = leftRotation(yy);
                        } else {
                            yy->parent->right = leftRotation(yy);
                        }
                    }
                    yy = yy->parent->parent;
                    while (yy != nullptr) {
                        yy->height--;
                        yy = yy->parent;
                    }
                }
            }

            y = y->parent;
        }
    }

    return root;
}

node * rightRotation(node *pin) {
    node * temp = pin->left;

    pin->height = pin->height - 2;

    pin->left = temp->right;
    temp->right = pin;

    temp->parent = pin->parent;
    pin->parent = temp;

    return temp;
}


node * leftRotation(node *pin) {
    node * temp = pin->right;

    pin->height = pin->height - 2;

    pin->right = temp->left;
    temp->left = pin;

    temp->parent = pin->parent;
    pin->parent = temp;

    return temp;
}

int max(int a, int b) {
    if (a >= b)
        return a;

    return b;
}
int getHeight(node * n){
    if (n->key == -1)
        return 0;
    
    return n->height;
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
    if( node->key != -1 ) {
        cout << prefix;

        cout << (isLeft ? "|--" : "---" );

        // print the value of the node
        cout << "(k: " << node->key << ", h: " << node->height << ")" << endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "|   " : "    "), node->right, true);
        printBT( prefix + (isLeft ? "|   " : "    "), node->left, false);
    }
}