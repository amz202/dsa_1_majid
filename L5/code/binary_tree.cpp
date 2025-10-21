#include <iostream>
using namespace std;

template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    
    Node(T value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

template <typename T>
class BinarySearchTree {
public:
    Node<T>* root;

    //constructor
    BinarySearchTree() {
        root = nullptr;
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
        }

        return node;
    }

    void preOrder(Node<T>* node){
        if(node!=nullptr){
            cout<< node->data <<" ";
            preOrder(node->left);
            preOrder(node->right);
        }
    }
    
    void inOrder(Node<T>* node){
        if(node!=nullptr){
            inOrder(node->left);
            cout<< node->data <<" ";
            inOrder(node->right);
        }
    }

    void postOrder(Node<T>* node){
        if(node!=nullptr){
            postOrder(node->left);
            postOrder(node->right);
            cout<< node->data <<" ";
        }
    }

    Node<T>* findMin(Node<T> *node){
        while (node->left != nullptr){
            node = node->left;
        }
        return node;
    }

    Node<T>* deleteValue(Node<T>* node, T value){
        if(node==nullptr){
            cout<<"Not Found"<<endl;
            return node;
        }
        if(value<node->data){
            node->left = deleteValue(node->left, value);
        }
        else if(value>node->data){
            node->right = deleteValue(node->right, value);
        }
        else if(value==node->data){
            //no left child
            if(node->left==nullptr){
                Node<T>* temp = node->right;
                delete node;
                return temp;
            }

            //no right child
            else if(node->right==nullptr){
                Node<T>* temp = node->left;
                delete node;
                return temp;
            }

            //2 child
            Node<T>* temp = findMin(node->right);
            node->data = temp->data;
            node->right = deleteValue(node->right, temp->data);
        
        }
        return node;
    }

    int countNodes(Node<T>* node) {
        if (node == nullptr) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void insert(T value) {
        root = insertValue(root, value);
    }

    void remove(T value) {
        root = deleteValue(root, value);
    }

    bool isEmpty() {
        return root == nullptr;
    }

    int size() {
        return countNodes(root);
    }

};

//function to test BST with different sizes
void testSmallArray() {
    cout << "Testing with small array (size 10)" << endl;
    BinarySearchTree<int> bst;
    int arr[] = {15, 10, 20, 8, 12, 25, 6, 11, 13, 27};
    
    cout << "Inserting: ";
    for(int i = 0; i < 10; i++) {
        cout << arr[i] << " ";
        bst.insert(arr[i]);
    }
    cout << endl;
    
    cout << "In-Order: ";
    bst.inOrder(bst.root);
    cout << endl;
    cout << "Tree size: " << bst.size() << endl;
    
    cout << "Deleting 10 and 25" << endl;
    bst.remove(10);
    bst.remove(25);
    cout << "In-Order after deletion: ";
    bst.inOrder(bst.root);
    cout << endl;
}

void testLargeArray() {
    cout << "Testing with larger array (size 100)" << endl;
    BinarySearchTree<int> bst;
    
    cout << "Inserting 100 values (1 to 100)" << endl;
    for(int i = 1; i <= 100; i++) {
        bst.insert(i);
    }
    
    cout << "Tree size: " << bst.size() << endl;
    cout << "Deleting some values (50, 75, 25)" << endl;
    bst.remove(50);
    bst.remove(75);
    bst.remove(25);
    cout << "Tree size after deletion: " << bst.size() << endl;
}

int main() {
    BinarySearchTree<int> bst;
    int choice, value;

    while (true) {
        cout << "a) Insert new data" << endl;
        cout << "b) In-Order Traversal" << endl;
        cout << "c) Pre-Order Traversal" << endl;
        cout << "d) Post-Order Traversal" << endl;
        cout << "e) Delete an item" << endl;
        cout << "f) Test with small array (size 10)" << endl;
        cout << "g) Test with large array (size 100)" << endl;
        cout << "h) Show tree size" << endl;
        cout << "i) Exit" << endl;
        cout << "Enter : ";
        
        char ch;
        cin >> ch;

        switch (ch) {
            case 'a':
            case 'A':
                cout << "Enter value to insert: ";
                cin >> value;
                bst.insert(value);
                cout << "Value " << value << " inserted" << endl;
                break;

            case 'b':
            case 'B':
                if (bst.isEmpty()) {
                    cout<<"Empty Tree"<<endl;
                } else {
                    cout << "In-Order Traversal: ";
                    bst.inOrder(bst.root);
                    cout << endl;
                }
                break;

            case 'c':
            case 'C':
                if (bst.isEmpty()) {
                    cout<<"Empty Tree"<<endl;
                } else {
                    cout << "Pre-Order Traversal: ";
                    bst.preOrder(bst.root);
                    cout << endl;
                }
                break;

            case 'd':
            case 'D':
                if (bst.isEmpty()) {
                    cout<<"Empty Tree"<<endl;
                } else {
                    cout << "Post-Order Traversal: ";
                    bst.postOrder(bst.root);
                    cout << endl;
                }
                break;

            case 'e':
            case 'E':
                if (bst.isEmpty()) {
                    cout<<"Empty Tree"<<endl;
                } else {
                    cout << "Enter value to delete: ";
                    cin >> value;
                    bst.remove(value);
                    cout << "Deletion operation completed" << endl;
                }
                break;

            case 'f':
            case 'F':
                testSmallArray();
                break;

            case 'g':
            case 'G':
                testLargeArray();
                break;

            case 'h':
            case 'H':
                cout << "Current tree size: " << bst.size() << " nodes" << endl;
                break;

            case 'i':
            case 'I':
                cout << "Exiting" << endl;
                return 0;

            default:
                cout << "Invalid choice" << endl;
                break;
        }
    }

    return 0;
}