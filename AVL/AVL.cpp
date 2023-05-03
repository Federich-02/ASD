/*
    Arghittu Thomas

    AVL Implementation
*/

#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

/// Generic node of a Binary Tree
struct node {
    int key;
    string alfNumKey;
    int height;
    node *left;
    node *right;
    node *parent;

    node(int k, string alfNumKeyVal) {
        key = k;
        alfNumKey = alfNumKeyVal;
        height = 1;
        left = new node(-1, 0, nullptr, nullptr, nullptr);
        right = new node(-1, 0, nullptr, nullptr, nullptr);
        parent = nullptr;
    }

    node(int k, string alfNumKeyVal, int height) {
        key = k;
        alfNumKey = alfNumKeyVal;
        height = height;
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


node * insertAVL(node *root, int k, string alfNumKey);
node * removeAVL(node *root, int key);
string findAVL(node *root, int key);

node * rightRotation(node *pin);
node * leftRotation(node *pinNode);
node * fixAVL(node * root, node * y);

int max(int, int);
int getHeight(node * n);
int getBalance(node * n);

node * successorAVL(node * y);
node * findAVLAdd(node *root, int key);

void printInPolishForm(node *root);

/// BST graphically print - No required
void readCommand(vector<string> &out);
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

        if (command[0] == "insert") {
            root = insertAVL(root, stoi(command[1]), command[2]);
            // printBT(root);
        } else if (command[0] == "find"){
            cout << findAVL(root, stoi(command[1])) << endl;
        } else if (command[0] == "show") {
            printInPolishForm(root);
            cout << endl;
        } else if (command[0] == "remove"){
            root = removeAVL(root, stoi(command[1]));
            // printBT(root);
        } else if (command[0] == "clear") {
            root = nullptr;
        } else if (command[0] == "exit") {
            status = false;
        } else {
            cout << "Invalid command" << endl;
        }

        command.clear();
    } while (status);
    
    return 0;
}

// Insert new node in AVL
// node * insertAVL(node *root, int k, string alfNumKey) {
//     // Insert a new node on AVL
//     node *newNode = new node(k, alfNumKey);

//     newNode->height = 1;
//     newNode->left->left = nullptr;
//     newNode->left->right = nullptr;
//     newNode->right->left = nullptr;
//     newNode->right->right = nullptr;
    
//     if (root == nullptr) {
//         root = newNode;
//     } else {
//         node *y = root->parent;
//         node *x = root;

//         // Perform the normal BST insertion
//         while (x->key != -1) {
//             if (x->key > k) {
//                 y = x;
//                 x = y->left;
//             } else {
//                 y = x;
//                 x = y->right;
//             }
//         }

//         newNode->parent = y;

//         if (y->key > k) {
//             y->left = newNode;
//         } else {
//             y->right = newNode;
//         }

//         // Update height of the tree => O(log n)
//         if (y->left->key == -1 || y->right->key == -1) {
//             x = y;
//             while (x != nullptr) {
//                 x->height = max(getHeight(x->left) + 1, getHeight(x->right) + 1);
//                 x = x->parent;
//             }
//         }

//         // Fix AVL
//         root = fixAVL(root, y);
//     }

//     return root;
// }

// AVL insertion operation
node * insertAVL(node *root, int k, string alfNumKey) {
    // Normal BST insertion (recursive)
    if(root == nullptr)
        return new node(k, alfNumKey);

    if(root->key == -1)
        return new node(k, alfNumKey);
    
    if(k < root->key)
        root->left = insertAVL(root->left, k, alfNumKey);
    else if (k > root->key)
        root->right = insertAVL(root->right, k, alfNumKey);
    else
        return root;

    // Update current node height
    root->height = max(getHeight(root->left) + 1, getHeight(root->right) + 1);

    int balance = getBalance(root);

    // Fix AVL if unbalanced

    // LL case
    if (balance > 1 && k < root->left->key)
        return rightRotation(root);
    // RR case
    if (balance < -1 && k > root->right->key)
        return leftRotation(root);
    // LR case
    if (balance > 1 && k > root->left->key) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    // RL case
    if (balance < -1 && k < root->right->key) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}


// Remove node from AVL
// node * removeAVL(node *root, int key) {
//     node * y = findAVLAdd(root, key);

//     if (y == nullptr) {
//         return root;
//     }

//     if (y->left->key == -1 && y->right->key == -1) {
//         if (y == root)
//             return nullptr;
        
//         y->key = -1;
//         y->height = 0;

//         if (y->parent->left->key == -1 || y->parent->right->key == -1) {
//             node * x = y->parent;
//             while (x != nullptr) {
//                 x->height = max(getHeight(x->left) + 1, getHeight(x->right) + 1);
//                 x = x->parent;
//             }
//         }

//         if (y->parent->left->key == -1 && y->parent->right->key == -1) {
//             root = fixAVL(root, y->parent);
//         } else {
//             if (y == y->parent->left)
//                 root = fixAVL(root, y->parent->right);
//             else
//                 root = fixAVL(root, y->parent->left);
//         }
//     } else if (y->right->key == -1) {
//         // Cerco il predecessore di y, lo scrivo al suo posto e chiamo fix sull'ex padre del predecessore
//         node * x = y->parent;
        
//         if (y != root) {
//             if (y == x->left) {
//                 x->left = y->left;
//                 x->left->parent = x;
//             } else {
//                 x->right = y->left;
//                 x->right->parent = x;
//             }
//         } else {
//             root = y->left;
//             root->parent = nullptr;
//         }

//         root = fixAVL(root, x);
//     } else if (y->left->key == -1) {
//         // Cerco il sucessore di y, lo scrivo al suo posto e chiamo fix sull'ex padre del sucessore
//         node * x = y->parent;

//         if (y != root) {
//             if (y == x->left) {
//                 x->left = y->right;
//                 x->left->parent = x;
//             } else {
//                 x->right = y->right;
//                 x->right->parent = x;
//             }
//         } else {
//             root = y->right;
//             root->parent = nullptr;
//         }

//         root = fixAVL(root, x);
//     } else {
//         // Cerco il successore o predecessore in base alle altezze del sotto albero e richiamo fix sull'ex padre
//         node * x = y->parent;
//         node * succ = successorAVL(y);
//         node * succPar = succ->parent;

//         if (y != root) {
//             if (y == x->left) {
//                 x->left = succ;
//                 succ->parent = x;

//                 if (y->right != succ)
//                     succ->right = y->right;
                
//                 succ->left = y->left;

//                 succ->height = y->height;

//                 if (succ == succPar->left)
//                     succPar->left = new node(-1, "");
//                 else if (succ == succPar->right)
//                     succPar->right = new node(-1, "");

//                 if (succPar == y)
//                     succPar = x->left;
//             } else {
//                 x->right = succ;
//                 succ->parent = x;

//                 if (y->right != succ)
//                     succ->right = y->right;
                
//                 succ->left = y->left;

//                 if (succ == succPar->left)
//                     succPar->left = new node(-1, "");
//                 else if (succ == succPar->right)
//                     succPar->right = new node(-1, "");

//                 if (succPar == y)
//                     succPar = x->right;
//             }
//             while (x != nullptr) {
//                 x->height = max(getHeight(x->left) + 1, getHeight(x->right) + 1);
//                 x = x->parent;
//             }

//         } else {
//             root = succ;
//             root->parent = nullptr;

//             if (y->right != succ) {
//                 succ->right = y->right;
//                 succ->right->parent = root;
//             }

//             succ->left = y->left;

//             root->left->parent = root;

//             root->height = max(getHeight(root->left) + 1, getHeight(root->right) + 1);
//             if (succPar == root) {
//                 if (root->left->key != -1)
//                     succPar = root->left;
//                 else if (root->right->key != -1)
//                     succPar = root->right;
//             }
//         }

//         root = fixAVL(root, succPar);
//     }

//     return root;
// }

node * removeAVL(node *root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = removeAVL(root->left, key);
    else if (key > root->key)
        root->right = removeAVL(root->right, key);
    else {
        if (root->left->key == -1 || root->right->key == -1) {
            node * temp;

            if (root->left->key != -1)
                temp = root->left;
            else
                temp = root->right;

            // No children case
            if (temp->key == -1) {
                temp = root;
                root = new node(-1, "", 0);
            }
            // One child case
            else {
                *root = *temp;
            }
        } else {
            node * temp = successorAVL(root->right);
            
            root->key = temp->key;
            root->alfNumKey = temp->alfNumKey;

            root->right = removeAVL(root->right, temp->key);
        }
    }


    if (root == nullptr)
        return root;

    if (root->key == -1)
        return root;

    // Update current node height
    root->height = max(getHeight(root->left) + 1, getHeight(root->right) + 1);

    int balance = getBalance(root);

    // Fix AVL if unbalanced

    // LL case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotation(root);
    // RR case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotation(root);
    // LR case
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    // RL case
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }

    return root;
}

// Find (Recursive)
string findAVL(node *root, int key) {
    if (root->key == -1)
        return "";
    
    if (root->key > key){
        return findAVL(root->left, key);
    } else if (root->key < key) {
        return findAVL(root->right, key);
    } else {
        return root->alfNumKey;
    }
}

// Fix AVL
// Return root
node * fixAVL(node * root, node * y) {
    while (y != nullptr) {

        if (y->parent == nullptr)
            break;
        
        if (y == y->parent->left) {
            // Check for rotation (RL or LL rotation)
            if (abs(y->height - y->parent->right->height) > 1){
                node * yy = y->parent;
                if (y->right->key != -1) {
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
                // Re-Update height
                yy = yy->parent->parent;
                while (yy != nullptr) {
                    yy->height--;
                    yy = yy->parent;
                }
            }
        } else {
            // Check for rotation (LR or RR rotation)
            if (abs(y->height - y->parent->left->height) > 1){
                node * yy = y->parent;
                if (y->left->key != -1) {
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
                // Re-Update height
                yy = yy->parent->parent;
                while (yy != nullptr) {
                    yy->height--;
                    yy = yy->parent;
                }
            }
        }
        // Iterate up the tree for any balancing
        y = y->parent;
    }
    
    return root;
}

// Print in polish form
void printInPolishForm(node *root) {
    if (root == nullptr) {
        cout << "NULL ";
        return;
    }
    if (root->key == -1){
        cout << "NULL ";
        return;
    }
    cout << root->key << ":" << root->alfNumKey << ":" << root->height << " ";
    printInPolishForm(root->left);
    printInPolishForm(root->right);
}

// Right rotation
node * rightRotation(node *pin) {
    node * temp = pin->left;
    node * T2 = temp->right;

    temp->right = pin;
    pin->left = T2;

    pin->height = max(getHeight(pin->left) + 1, getHeight(pin->right) + 1);
    temp->height = max(getHeight(temp->left) + 1, getHeight(temp->right) + 1);

    return temp;
}

// Left rotation
node * leftRotation(node *pin) {
    node * temp = pin->right;
    node * T2 = temp->left;

    temp->left = pin;
    pin->right = T2;

    pin->height = max(getHeight(pin->left) + 1, getHeight(pin->right) + 1);
    temp->height = max(getHeight(temp->left) + 1, getHeight(temp->right) + 1);
    
    return temp;
}

// Max between a or b
int max(int a, int b) {
    if (a >= b)
        return a;

    return b;
}

// Height of generic node
int getHeight(node * n){
    if (n->key == -1)
        return 0;
    
    return n->height;
}

// Get Balance factor of node N  
int getBalance(node * n) {  
    if (n->key == -1)  
        return 0;  
    return getHeight(n->left) - getHeight(n->right);  
} 

node * successorAVL(node * y) {
    if (y == nullptr)
        return nullptr;

    while (y->left->key != -1) {
        y = y->left;
    }

    return y;
}

// Find node in AVL (Recursive) and return address
node * findAVLAdd(node *root, int key){
    if (root->key == -1)
        return nullptr;
    
    if (root->key > key){
        return findAVLAdd(root->left, key);
    } else if (root->key < key) {
        return findAVLAdd(root->right, key);
    } else {
        return root;
    }
}

/// -----------------------COMMON OPERATION-----------------------

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