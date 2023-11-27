#include <iostream>
#include <algorithm>
using namespace std;

template<class T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    int height;
    
    Node(const T& val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

template <class T>
class AVLTree {
private:
    Node<T>* root;

    int height(Node<T> * node) {
        if (node == nullptr) return 0;
        return node->height;
    }

    int getBalance(Node<T>* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }

    Node<T>* rightRotate(Node<T>* root) {
        Node<T>* newRoot = root->left;
        Node<T>* temp = newRoot->right;

        newRoot->right = root;
        root->left = temp;

        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    Node<T>* leftRotate(Node<T>* root) {
        Node<T>* newRoot = root->right;
        Node<T>* temp = newRoot->left;

        newRoot->left = root;
        root->right = temp;

        root->height = 1 + max(height(root->left), height(root->right));
        newRoot->height = 1 + max(height(newRoot->left), height(newRoot->right));

        return newRoot;
    }

    Node<T>* insert(Node<T>* node, const T& data) {
        if (node == nullptr) return new Node<T>(data);

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        } else {
            return node; // Duplicate keys are not allowed in AVL tree
        }

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && data < node->left->data) {
            return rightRotate(node);
        }

        if (balance < -1 && data > node->right->data) {
            return leftRotate(node);
        }

        if (balance > 1 && data > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && data < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T>* minValueNode(Node<T>* node) {
        Node<T>* current = node;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    Node<T>* remove(Node<T>* node, const T& data) {
        if (node == nullptr) return node;

        if (data < node->data) {
            node->left = remove(node->left, data);
        } else if (data > node->data) {
            node->right = remove(node->right, data);
        } else {
            if (node->left == nullptr || node->right == nullptr) {
                Node<T>* temp = node->left ? node->left : node->right;

                if (temp == nullptr) {
                    temp = node;
                    node = nullptr;
                } else {
                    *node = *temp;
                }
                delete temp;
            } else {
                Node<T>* temp = minValueNode(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        if (node == nullptr) return node;

        node->height = 1 + max(height(node->left), height(node->right));

        int balance = getBalance(node);

        if (balance > 1 && getBalance(node->left) >= 0) {
            return rightRotate(node);
        }

        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        if (balance < -1 && getBalance(node->right) <= 0) {
            return leftRotate(node);
        }

        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    void inorder(Node<T>* node) {
        if (node == nullptr) return;
        inorder(node->left);
        cout << node->data << "\n";
        inorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(const T& data) {
        root = insert(root, data);
    }

    void remove(const T& data) {
        root = remove(root, data);
    }

    void inorderTraversal() {
        inorder(root);
    }
};

int main() {
    AVLTree<int> t;

    t.insert(20);
    t.insert(25);
    t.insert(15);
    t.insert(10);
    t.insert(30);
    t.insert(5);
    t.insert(35);
    t.insert(67);
    t.insert(43);
    t.insert(21);
    t.insert(89);
    t.insert(38);
    t.insert(69);
    t.insert(63);

    t.remove(63);
    t.remove(67);
    t.remove(89);
    t.remove(69);

    t.inorderTraversal();

    return 0;
}
