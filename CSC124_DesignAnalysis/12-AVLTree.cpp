#include <iostream>
#include <algorithm>

class Node {
public:
    int key;
    Node* left;
    Node* right;
    int height;

    Node(int value) {
        key = value;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};

class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        if (node == nullptr)
            return 0;
        return node->height;
    }

    int getBalanceFactor(Node* node) {
        if (node == nullptr)
            return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* newRootLeft = newRoot->left;

        newRoot->left = node;
        node->right = newRootLeft;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* newRootRight = newRoot->right;

        newRoot->right = node;
        node->left = newRootRight;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        newRoot->height = 1 + std::max(getHeight(newRoot->left), getHeight(newRoot->right));

        return newRoot;
    }

    Node* insertNode(Node* root, int key) {
        if (root == nullptr)
            return new Node(key);

        if (key < root->key)
            root->left = insertNode(root->left, key);
        else if (key > root->key)
            root->right = insertNode(root->right, key);
        else
            return root; // Duplicate keys are not allowed in AVL tree

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        int balance = getBalanceFactor(root);

        // Left Left case
        if (balance > 1 && key < root->left->key)
            return rotateRight(root);

        // Right Right case
        if (balance < -1 && key > root->right->key)
            return rotateLeft(root);

        // Left Right case
        if (balance > 1 && key > root->left->key) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Left case
        if (balance < -1 && key < root->right->key) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    Node* findMinNode(Node* root) {
        while (root->left != nullptr)
            root = root->left;

        return root;
    }

    Node* deleteNode(Node* root, int key) {
        if (root == nullptr)
            return root;

        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            // Node to be deleted found
            if (root->left == nullptr || root->right == nullptr) {
                Node* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {
                Node* minNode = findMinNode(root->right);
                root->key = minNode->key;
                root->right = deleteNode(root->right, minNode->key);
            }
        }

        if (root == nullptr)
            return root;

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

        int balance = getBalanceFactor(root);

        // Left Left case
        if (balance > 1 && getBalanceFactor(root->left) >= 0)
            return rotateRight(root);

        // Left Right case
        if (balance > 1 && getBalanceFactor(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // Right Right case
        if (balance < -1 && getBalanceFactor(root->right) <= 0)
            return rotateLeft(root);

        // Right Left case
        if (balance < -1 && getBalanceFactor(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void inorderTraversal(Node* root, int depth = 0) {
        if (root != nullptr) {
            inorderTraversal(root->right, depth + 1);
            std::cout << std::string(depth * 4, ' ') << root->key << std::endl;
            inorderTraversal(root->left, depth + 1);
        }
    }

public:
    AVLTree() {
        root = nullptr;
    }

    void insert(int key) {
        root = insertNode(root, key);
    }

    bool search(int key) {
        return searchNode(root, key);
    }

    void inorder() {
        inorderTraversal(root);
    }

    void remove(int key) {
        root = deleteNode(root, key);
    }
};

int main() {
    AVLTree avl;

    // Insert nodes
    avl.insert(50);
    avl.insert(30);
    avl.insert(20);
    avl.insert(40);
    avl.insert(70);
    avl.insert(60);
    avl.insert(80);

    // Print AVL tree
    std::cout << "AVL Tree:" << std::endl;
    avl.inorder();

    // Search for a key
    int key = 40;
    if (avl.search(key))
        std::cout << key << " is found in the AVL tree." << std::endl;
    else
        std::cout << key << " is not found in the AVL tree." << std::endl;

    // Delete a key
    key = 30;
    avl.remove(key);

    // Print AVL tree after deletion
    std::cout << "AVL Tree after deletion:" << std::endl;
    avl.inorder();

    return 0;
}
