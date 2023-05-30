#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <bits/stdc++.h>

using namespace std;

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

    int max_size = 10000000;
    int search_key, search_index;
    int delete_key, delete_index;
    srand(time(NULL));

    for(int j = 0 ; j < 5; j++){
        search_index = rand() % max_size;
        delete_index = rand() % max_size;

        clock_t start1, finish1, start2, finish2, start3, finish3;

        start1 = clock();
        for (int i = 0; i < max_size; i++) {
            int data = rand();
            bst.insert(data);
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

        // Inorder traversal
        // std::cout << "Inorder traversal: ";
        // bst.inorder();
        // std::cout << std::endl;

        // Search for a key
        start2 = clock();
        if (bst.search(search_key))
            std::cout << search_key << " is found in the BST." << std::endl;
        else
            std::cout << search_key << " is not found in the BST." << std::endl;
        finish2 = clock();

        double time_taken2 = (double(finish2 - start2) / double(CLOCKS_PER_SEC)) * 1000;
        cout << "Time taken by Search is: " << fixed << time_taken2 << setprecision(5) << " milliseconds" << endl;

        // Delete a key
        start3 = clock();
        bst.remove(delete_key);
        finish3 = clock();

        double time_taken3 = (double(finish3 - start3) / double(CLOCKS_PER_SEC)) * 1000;
        cout << "Time taken by Delete is: " << fixed << time_taken3 << setprecision(5) << " milliseconds" << endl;

        // Inorder traversal after deletion
        // std::cout << "Inorder traversal after deletion: ";
        // bst.inorder();
        // std::cout << std::endl;
    }
    return 0;
}
