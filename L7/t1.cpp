#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    int height;
    
    Node(T value) {
        data = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

template <typename T>
class AVLTree {
public:
    Node<T>* root;

    //constructor
    AVLTree() {
        root = nullptr;
    }

    int height(Node<T>* node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int max(int a, int b) {
        return (a > b) ? a : b;
    }

    int balanceFactor(Node<T>* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    Node<T>* rotateRight(Node<T>* node){
        Node<T>* temp = node->left;
        Node<T>* tree = temp->right;

        //rotation
        temp->right = node;
        node->left = tree;

        //height updates
        node->height = max(height(node->left), height(node->right)) + 1;
        temp->height = max(height(temp->left), height(temp->right)) + 1;

        return temp;
    }

    Node<T>* rotateLeft(Node<T>* node){
        Node<T>* temp = node->right;
        Node<T>* tree = temp->left;

        //rotation
        temp->left = node;
        node->right = tree;

        //height updates
        node->height = max(height(node->left), height(node->right)) + 1;
        temp->height = max(height(temp->left), height(temp->right)) + 1;

        return temp;
    }

    Node<T>* insertValue(Node<T>* node, T value){
        if(node == nullptr){ //base case
            return new Node<T>(value);
        }

        if(value<node->data){ //recursion start, condition to go left or right
            node->left = insertValue(node->left, value);
        }else if(value>node->data){
            node->right = insertValue(node->right,value);
        }

        else if(value==node->data){
            cout<<"no duplicates";
            return node;
        }

        //update height
        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        //Left Left Case
        if(balance > 1 && value < node->left->data){
            return rotateRight(node);
        }

        //Right Right Case
        if(balance < -1 && value > node->right->data){
            return rotateLeft(node);
        }

        //Left Right Case
        if(balance > 1 && value > node->left->data){
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        //Right Left Case
        if(balance < -1 && value < node->right->data){
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void insert(T value) {
        root = insertValue(root, value);
    }

    void preOrder(Node<T>* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void displayPreOrder() {
        cout << "Pre-Order: ";
        preOrder(root);
        cout << endl;
    }
};

int main() {
    AVLTree<int> avl;
    
    int sequence[] = {10, 20, 30, 40, 50};
    
    for (int i = 0; i < 5; i++) {
        cout << "\nInserting " << sequence[i] << ":" << endl;
        avl.insert(sequence[i]);
        avl.displayPreOrder();
    }
    
    cout << "\nTesting duplicates:" << endl;
    avl.insert(30); 
    avl.displayPreOrder();
    
    return 0;
}