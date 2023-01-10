#include <iostream>
using namespace std;

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int data) {
        key = data;
        left = right = NULL;
        height = 0;
    }
};

class BST {
    Node* root;

public:
    BST() {
        root = NULL;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int height(Node* node) {
        if (node == NULL)
            return -1;
        
        return node->height;
    }

    int getBalance(Node* node) {
        if (node == NULL)
            return 0;       
        
        return height(node->left) - height(node->right);
    }

    Node* leftRotate(Node* z) {
        Node* y = z->right;
        Node* T2 = y->left;

        y->left = z;
        z->right = T2;

        z->height = max(height(z->left), height(z->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        return y;
    }

    Node* rightRotate(Node* z) {
        Node* y = z->left;
        Node* T3 = y->right;

        y->right = z;
        z->left = T3;

        z->height = max(height(z->left), height(z->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        
        return y;
    }

    Node* insert(Node* root, int data) {

        if (root == NULL)
            root = new Node(data);
        
        else if (data < root->key)
            root->left = insert(root->left, data);
        
        else if (data > root->key)
            root->right = insert(root->right, data);
        
        else 
            return root;
        
        root->height = 1 + max(height(root->left), height(root->right));
       
        int balance = getBalance(root);
        
        if (balance > 1 && data < root->left->key)
            return rightRotate(root);
       
        if (balance < -1 && data > root->right->key)
            return leftRotate(root);
        
        if (balance > 1 && data > root->left->key) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
       
        if (balance < -1 && data < root->right->key) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
        
        return root;
    }

    void insert(int data) {
        root = insert(root, data);
    }

    Node* search(Node* root, int data) {
        if (root == NULL || root->key == data)
            return root;

        if (root->key < data)
            return search(root->right, data);

        return search(root->left, data);
    }

    Node* search(int data) {
        return search(root, data);
    }

    Node* remove(Node* root, int data) {		

        if (root == NULL)
            return root;
        
        if (root->key > data)
            root->left = remove(root->left, data);
        
        else if (data > root->key)
            root->right = remove(root->right, data);
       
        else {
            if (root->left == NULL) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
           
            else if (root->right == NULL) {
                Node* temp = root->left;
                delete root;
                return temp;
            }

            Node* temp = rightmostNode(root->left);
            root->key = temp->key;
            root->left = remove(root->left, temp->key);
        }
        
        if (root == NULL)
            return root;
        
        root->height = 1 + max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);
       
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
        
        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);
        
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    Node* rightmostNode(Node* node) {
        Node* current = node;

        while (current->right != NULL)
            current = current->right;

        return current;
    }

    /*Node* findMax() {
        if (root == NULL)
            return NULL;

        Node* current = root;

        while (current->right != NULL)
            current = current->right;

        return current;
    }

    Node* findMin() {
        if (root == NULL)
            return NULL;

        Node* current = root;

        while (current->left != NULL)
            current = current->left;

        return current;
    }*/

    void preorder(Node* root) {
        if (root != NULL) {
            cout << root->key << " ";
            preorder(root->left);
            preorder(root->right);
        }
    }

    void inorder(Node* root) {
        if (root != NULL) {
            inorder(root->left);
            cout << root->key << " ";
            inorder(root->right);
        }
    }

    void postorder(Node* root) {
        if (root != NULL) {
            postorder(root->left);
            postorder(root->right);
            cout << root->key << " ";
        }
    }

    void print(Node* node, string spacing, string edge, bool hasLeftChild) {
        if (node != NULL) {
            cout << "\n" << spacing << edge << node->key;

            if ((node->left == NULL) && (node->right == NULL)) {
                cout << "\n" << spacing; 

                if (hasLeftChild) { 
                    cout << "    |";
                }
            }

            else {
                string newSpace = spacing + (hasLeftChild ? "    |    " : "       ");
                print(node->right, newSpace, "    [-----", node->left != NULL);
                print(node->left, newSpace, "    (-----", false);
            }
        }
    }

    void print(Node* root) {
        if (root == NULL) {
            return;
        }

        cout << root->key;
        print(root->right, "", "    [-----", root->left != NULL);
        print(root->left, "", "    (-----", false);
    } 
};

int main() {
    
    BST Tree;
    Node* root = NULL;

    int choice, addNum, removeNum, searchNum;

    while (1) {

        cout << "\n" << string(58, '*');
        cout << "\n\t     Binary Search Tree Operations " << "\n";
        cout << string(58, '*') << "\n";
        cout << " 1) Insertion \t\t\t 5) Deletion \n 2) Pre-Order Traversal \t 6) Search \n 3) In-Order Traversal"
                "\t\t 7) Display Balanced BST \n 4) Post-Order Traversal \t 8) Exit  \n";
        cout << "\n Enter your choice: ";
        cin >> choice;

        if (choice < 1 || choice > 8)
            cout << "\n ERROR! Incorrect choice. Please choose a number between 1 and 8.\n";

        switch (choice) {
        case 1:
            cout << "\n Enter a number to be inserted into the BST: ";
            cin >> addNum;
            cout << "\n";
            root = Tree.insert(root, addNum);
            cout << " " << addNum << " inserted\n";
            break;

        case 2:
            cout << "\n Pre-Order Traversal: \n";
            cout << " "; Tree.preorder(root);
            cout << "\n";
            break;

        case 3:
            cout << "\n In-Order Traversal: \n";
            cout << " "; Tree.inorder(root);
            cout << "\n";
            break;

        case 4:
            cout << "\n Post-Order Traversal: \n";
            cout << " "; Tree.postorder(root);
            cout << "\n";
            break;

        case 5:
            cout << "\n Enter a number to be deleted from the BST: ";
            cin >> removeNum;
            cout << "\n";
            Tree.remove(root, removeNum);
            cout << " " << removeNum << " deleted\n";
            break;

        case 6:
            cout << "\n Enter a number to be searched for in the BST: ";
            cin >> searchNum;
            if (Tree.search(root, searchNum))
                cout << "\n Element " << searchNum << " found\n";
            else
                cout << "\n Element " << searchNum << " not found\n";
            break;

        case 7:
            cout << "\n Displayed balanced BST: ";
            cout << "\n\n";
            cout << "  "; Tree.print(root);
            cout << "\n";
            break;

        case 8:
            return 0;
            break;
        }
    }
    return 0;   
}
