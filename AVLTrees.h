// Created by habibaayman on 5/13/2024.

#ifndef CLIONPROJECTS_AVLTREES_H
#define CLIONPROJECTS_AVLTREES_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>

using namespace std;

class Item {
private:
    string itemname;
    string category;
    int price;

public:
    Item(string name, string cat, int pr) : itemname(name), category(cat), price(pr) {}

    string getitemname() const {
        return itemname;
    }
    int getPrice() const {
        return price;
    }
    bool operator<(const Item& other) const {
        return itemname < other.itemname;
    }
    bool operator>(const Item& other) const {
        return itemname > other.itemname;
    }
};
template<typename T>
class AVLTreeNode {
public:
    T key;
    int height;
    AVLTreeNode<T>* left;
    AVLTreeNode<T>* right;

    AVLTreeNode(T key, AVLTreeNode<T>* left = nullptr, AVLTreeNode<T>* right = nullptr)
            : key(key), height(1), left(left), right(right) {}
};
template<typename T>
class AVLTree {
private:
    AVLTreeNode<T>* root;

    int height(AVLTreeNode<T>* node) {
        if (node == nullptr) return 0;
        int lefth = height(node->left);
        int righth = height(node->right);
        return max(lefth, righth) + 1;
    }
    int getBalance(AVLTreeNode<T>* node) {
        if (node == nullptr) return 0;
        return height(node->left) - height(node->right);
    }
    AVLTreeNode<T>* rotateRight(AVLTreeNode<T>* x) {
        AVLTreeNode<T>* leftX = x->left;//left child of x
        AVLTreeNode<T>* RleftX = leftX->right;//right child of leftX

        leftX->right = x;
        x->left = RleftX;

        x->height = max(height(x->left), height(x->right)) + 1;
        leftX->height = max(height(leftX->left), height(leftX->right)) + 1;

        return x;
    }
    AVLTreeNode<T>* rotateLeft(AVLTreeNode<T>* x) {
        AVLTreeNode<T>* rightX = x->right;//right child of x
        AVLTreeNode<T>* LrightX = rightX->left;//left child of rightX

        rightX->left = x;
        x->right = LrightX;

        x->height = max(height(x->left), height(x->right)) + 1;
        rightX->height = max(height(rightX->left), height(rightX->right)) + 1;

        return rightX;
    }

    AVLTreeNode<T>* insertNode(AVLTreeNode<T>* node, const T& key) {
        if (node == nullptr)
            return new AVLTreeNode<T>(key);
        if (key < node->key)
            node->left = insertNode(node->left, key);
        else if (key > node->key)
            node->right = insertNode(node->right, key);
        else
            return node;

        node->height = 1 + max(height(node->left), height(node->right));
        int balance = getBalance(node);

        // rotate left
        if (balance > 1 && key < node->left->key)
            return rotateRight(node);

        // rotate LR
        if (balance > 1 && key > node->left->key) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        // rotate right
        if (balance < -1 && key > node->right->key)
            return rotateLeft(node);

        // RL rotate
        if (balance < -1 && key < node->right->key) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }
        return node;
    }
    AVLTreeNode<T>* minValueNode(AVLTreeNode<T>* node) {
        AVLTreeNode<T>* current = node;

        while (current && current->left != nullptr)
            current = current->left;

        return current;
    }
    AVLTreeNode<T>* deleteNode(AVLTreeNode<T>* root, const T& key) {
        if (root == nullptr) {
            cout<<"item not found\n";
            return root;
        }
        if (key < root->key)
            root->left = deleteNode(root->left, key);
        else if (key > root->key)
            root->right = deleteNode(root->right, key);
        else {
            // Node with only one child or no child
            if ((root->left == nullptr) || (root->right == nullptr)) {
                AVLTreeNode<T>* temp = root->left ? root->left : root->right;

                // No child
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                } else
                    // One child
                    *root = *temp;

                delete temp;
            } else {
                AVLTreeNode<T>* temp = minValueNode(root->right);
                root->key = temp->key;
                root->right = deleteNode(root->right, temp->key);
            }
        }
        if (root == nullptr) return root;

        root->height = 1 + max(height(root->left), height(root->right));
        int balance = getBalance(root);

        // right rotation
        if (balance > 1 && getBalance(root->left) >= 0)
            return rotateRight(root);

        // Left Right rotation
        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }

        // left rotation
        if (balance < -1 && getBalance(root->right) <= 0)
            return rotateLeft(root);

        // Right Left rotation
        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }
        return root;
    }

    void inorder(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << root->key.getitemname() << " " << root->key.getPrice() << endl;
            inorder(root->right);
        }
    }


    void reverseorder(AVLTreeNode<T>* root) {
        if (root != nullptr) {
            reverseorder(root->right);
            cout << root->key.getitemname() << " " << root->key.getPrice() << endl;
            reverseorder(root->left);
        }
    }
    //puts them in vector
    void collectItemsinorder(AVLTreeNode<T>* root, vector<T>& items) {
        if (root != nullptr) {
            collectItemsinorder(root->left, items);
            items.push_back(root->key);
            collectItemsinorder(root->right, items);
        }
    }

public:
    AVLTree() : root(nullptr) {}
    void insert(const T& key) {
        root = insertNode(root, key);
    }
    void remove(const T& key) {
        root = deleteNode(root, key);
    }
    void displaynormal() {
        inorder(root);
    }
    void AscendingName() {
        inorder(root);
    }
    void DescendingName() {
        reverseorder(root);
    }
    void AscendingPrice() {
        vector<T> items;
        collectItemsinorder(root, items);
        sort(items.begin(), items.end(), [](const T& a, const T& b) {
            return a.getPrice() < b.getPrice();
        });
        for (const auto& item : items) {
            cout << item.getitemname() << " " << item.getPrice() << endl;
        }
    }
    void DescendingPrice() {
        vector<T> items;
        collectItemsinorder(root, items);
        sort(items.begin(), items.end(), [](const T& a, const T& b) {
            return a.getPrice() > b.getPrice();
        });
        for (const auto& item : items) {
            cout << item.getitemname() << " " << item.getPrice() << endl;
        }
    }
};

template<class T>
void readItems(istream& input, AVLTree<T>& tree) {
    int numItems;
    input >> numItems;

    for (int i = 0; i < numItems; ++i) {
        string itemname, category;
        int price;

        input.ignore();
        getline(input, itemname);
        getline(input, category);
        input >> price;

        tree.insert(Item(itemname, category, price));
    }
}
#endif //CLIONPROJECTS_AVLTREES_H
