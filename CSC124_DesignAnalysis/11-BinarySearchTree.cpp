#include <iostream>
#include <time.h>

class Node {
public:
    int key;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        left = nullptr;
        right = nullptr;
    }
};

class BinarySearchTree {
private:
    Node* root;

    Node* insertNode(Node* root, int key) {
        if (root == nullptr)
            return new Node(key);
        
        if (key < root->key)
            root->left = insertNode(root->left, key);
        else if (key > root->key)
            root->right = insertNode(root->right, key);
        
        return root;
    }

    bool searchNode(Node* root, int key) {
        if (root == nullptr)
            return false;

        if (root->key == key)
            return true;

        if (key < root->key)
            return searchNode(root->left, key);
        else
            return searchNode(root->right, key);
    }

    void inorderTraversal(Node* root) {
        if (root != nullptr) {
            inorderTraversal(root->left);
            std::cout << root->key << " ";
            inorderTraversal(root->right);
        }
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
            if (root->left == nullptr) {
                Node* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                Node* temp = root->left;
                delete root;
                return temp;
            }
            else {
                Node* minNode = findMinNode(root->right);
                root->key = minNode->key;
                root->right = deleteNode(root->right, minNode->key);
            }
        }
        return root;
    }

public:
    BinarySearchTree() {
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
    BinarySearchTree bst;

    // Insert nodes
    bst.insert(50);
    bst.insert(30);
    bst.insert(20);
    bst.insert(40);
    bst.insert(70);
    bst.insert(60);
    bst.insert(80);

    // Inorder traversal
    std::cout << "Inorder traversal: ";
    bst.inorder();
    std::cout << std::endl;

    // Search for a key
    int key = 40;
    if (bst.search(key))
        std::cout << key << " is found in the BST." << std::endl;
    else
        std::cout << key << " is not found in the BST." << std::endl;

    // Delete a key
    key = 30;
    bst.remove(key);

    // Inorder traversal after deletion
    std::cout << "Inorder traversal after deletion: ";
    bst.inorder();
    std::cout << std::endl;

    return 0;
}
