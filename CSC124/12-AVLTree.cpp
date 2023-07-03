#include <iostream>
#include <algorithm>
#include <time.h>
#include <bits/stdc++.h>
#include <stdlib.h>


using namespace std;
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

    bool searchNode(Node* root, int key) {
        if (root == nullptr)
            return false;

        if (key == root->key)
            return true;

        if (key < root->key)
            return searchNode(root->left, key);
        else
            return searchNode(root->right, key);
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

    int max_size = 500000;
    int search_key, search_index;
    int delete_key, delete_index;
    srand(time(NULL));

    for(int j = 0; j < 5; j++){
        search_index = rand() % max_size;
        delete_index = rand() % max_size;

        clock_t start1, finish1, start2, finish2, start3, finish3;

        // Insert nodes
        start1 = clock();
        for (int i = 0; i < max_size; i++) {
            int data = rand();
            avl.insert(data);
            if (i == search_index) {
                search_key = data;
            }
            if (i == delete_index) {
                delete_key = data;
            }
        }
        finish1 = clock();

        double time_taken1 = (double(finish1 - start1) / double(CLOCKS_PER_SEC)) * 1000;
        cout << "Time taken by Inserting is: " << fixed << time_taken1 << setprecision(5) << " milliseconds" << endl;
        cout << "Size: " << max_size << endl;

        // Print AVL tree
        // std::cout << "AVL Tree:" << std::endl;
        // avl.inorder();

        // Search for a key
        start2 = clock();
        if (avl.search(search_key))
            std::cout << search_key << " is found in the AVL tree." << std::endl;
        else
            std::cout << search_key << " is not found in the AVL tree." << std::endl;
        finish2 = clock();

        double time_taken2 = (double(finish2 - start2) / double(CLOCKS_PER_SEC)) * 1000;
        cout << "Time taken by Searching is: " << fixed << time_taken2 << setprecision(5) << " milliseconds" << endl;

        // Delete a key
        start3 = clock();
        avl.remove(delete_key);
        finish3 = clock();

        double time_taken3 = (double(finish3 - start3) / double(CLOCKS_PER_SEC)) * 1000;
        cout << "Time taken by Deleting is: " << fixed << time_taken3 << setprecision(5) << " milliseconds" << endl;

        // Print AVL tree after deletion
        // std::cout << "AVL Tree after deletion:" << std::endl;
        // avl.inorder();
    }
    return 0;
}
