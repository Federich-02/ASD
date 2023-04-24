/*
    Arghittu Thomas

    AVL Implementation

    - Funziona in tutti i casi base
    - Non aggiorna ancora le altezze degli alberi
    - Manca la verifica di bilanciamento non locale (aggiornare prima le altezze)
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
            
            // Verify if y height need to be updated
            if (y->right->key == -1) {
                y->height++;

                // Verify if tree need to be updated too
                if (y->parent != nullptr){
                    if (y == y->parent->left){
                        if (abs(y->height - y->parent->right->height) > 1){
                            if (root == y->parent){
                                root = rightRotation(y->parent);
                            } else {
                                y = y->parent;
                                y->parent->left = rightRotation(y);
                            }
                        }
                    } else {
                        if (abs(y->height - y->parent->left->height) > 1){
                            node * yy = y->parent;
                            yy->right = rightRotation(y);
                            
                            if (yy->parent == nullptr){
                                root = leftRotation(yy);
                            } else {
                                yy->parent->right = leftRotation(yy);
                            }
                        }
                    }
                }
            }
        } else {
            y->right = newNode;
            
            // Verify if y height need to be updated
            if (y->left->key == -1) {
                y->height++;

                // Verify if tree need to be updated too
                if (y->parent != nullptr){
                    if (y == y->parent->right){
                        if (abs(y->height - y->parent->left->height) > 1){
                            if (root == y->parent){
                                root = leftRotation(y->parent);
                            } else {
                                y = y->parent;
                                y->parent->right = leftRotation(y);
                            }
                        }
                    } else {
                        if (abs(y->height - y->parent->right->height) > 1){
                            node * yy = y->parent;
                            yy->left = leftRotation(y);
                            if (yy->parent == nullptr){
                                root = rightRotation(yy);
                            } else {
                                yy->parent->left = rightRotation(yy);
                            }
                        }
                    }
                }
            }
        }
    }

    return root;
}

node * rightRotation(node *pin){
    node * temp = pin->left;

    pin->left = temp->right;
    temp->right = pin;

    temp->parent = pin->parent;
    pin->parent = temp;

    return temp;
}


node * leftRotation(node *pin) {
    node * temp = pin->right;

    pin->right = temp->left;
    temp->left = pin;

    temp->parent = pin->parent;
    pin->parent = temp;

    return temp;
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