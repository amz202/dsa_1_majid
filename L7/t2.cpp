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

        temp->right = node;
        node->left = tree;

        node->height = max(height(node->left), height(node->right)) + 1;
        temp->height = max(height(temp->left), height(temp->right)) + 1;

        return temp;
    }

    Node<T>* rotateLeft(Node<T>* node){
        Node<T>* temp = node->right;
        Node<T>* tree = temp->left;

        temp->left = node;
        node->right = tree;

        node->height = max(height(node->left), height(node->right)) + 1;
        temp->height = max(height(temp->left), height(temp->right)) + 1;

        return temp;
    }

    Node<T>* insertValue(Node<T>* node, T value){
        if(node == nullptr){
            return new Node<T>(value);
        }

        if(value < node->data){
            node->left = insertValue(node->left, value);
        }else if(value > node->data){
            node->right = insertValue(node->right, value);
        }
        else{
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        if(balance > 1 && value < node->left->data){
            return rotateRight(node);
        }

        if(balance < -1 && value > node->right->data){
            return rotateLeft(node);
        }

        if(balance > 1 && value > node->left->data){
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if(balance < -1 && value < node->right->data){
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    Node<T>* findMin(Node<T>* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    Node<T>* deleteValue(Node<T>* node, T value) {
        if (node == nullptr) {
            return node;
        }

        if (value < node->data) {
            node->left = deleteValue(node->left, value);
        }
        else if (value > node->data) {
            node->right = deleteValue(node->right, value);
        }
        else {
            if (node->left == nullptr) {
                Node<T>* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) {
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }

            Node<T>* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteValue(node->right, temp->data);
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balance > 1 && balanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balance < -1 && balanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    void insert(T value) {
        root = insertValue(root, value);
    }

    void remove(T value) {
        root = deleteValue(root, value);
    }

    void preOrder(Node<T>* node) {
        if (node != nullptr) {
            cout << node->data << " ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    void displayPreOrder() {
        preOrder(root);
        cout << endl;
    }
};

int main() {
    AVLTree<int> avl;
    
    int sequence[] = {10, 20, 30, 40, 50, 25};
    
    for (int i = 0; i < 6; i++) {
        avl.insert(sequence[i]);
        avl.displayPreOrder();
    }
    
    cout << "Deleting 50:" << endl;
    avl.remove(50);
    avl.displayPreOrder();
    
    cout << "Deleting 40:" << endl;
    avl.remove(40);
    avl.displayPreOrder();
    
    cout << "Deleting 20:" << endl;
    avl.remove(20);
    avl.displayPreOrder();
    
    return 0;
}