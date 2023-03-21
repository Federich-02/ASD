#include <iostream>
#include <sstream>
#include <vector>

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
void preOrderPrint(node *root);
void inOrderPrint(node *node);
void insertBST(node *&root, int k);
void printBT(const std::string& prefix, const node* node, bool isLeft);
void printBT(const node* node);

int main(int argc, char const *argv[]) {
    node *root = nullptr;

    vector<int> A = vector<int>();

    cin >> A;

    for (int i=0; i<A.size(); i++){
        insertBST(root, A.at(i));
    }

    inOrderPrint(root);


    return 0;
}

// Pre-Order visit to generic tree
void preOrderPrint(node *node) {
    if (node != nullptr) {
        cout << node->key << " ";
        preOrderPrint(node->left);
        preOrderPrint(node->right);
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

void printBT(const node* node){
    printBT("", node, false);    
}