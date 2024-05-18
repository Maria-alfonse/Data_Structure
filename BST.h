//
// Created by Lenovo on 5/18/2024.
//

#ifndef UNTITLED_BST_H
#define UNTITLED_BST_H
#include "Item.h"
#include <vector>
#include <iostream>

using namespace std;
bool compareByName(const Item& i1, const Item& i2) {
    return i1.itemname > i2.itemname;
}
bool compareByPrice(const Item& i1, const Item& i2) {
    return i1.price > i2.price;
}

template<class T>
class BST_Node{
public:
    T value;
    BST_Node* left;
    BST_Node* right;

    BST_Node(){
        left = NULL;
        right = NULL;
    }
    BST_Node(const T& type, BST_Node* l = NULL, BST_Node* r= NULL){
        value = type;
        left = l;
        right = r;
    }

};

template<class T>
class BST{
protected:
    BST_Node<T>* rootname;
    BST_Node<T>* rootprice;
public:
    BST(){
        rootname = NULL;
        rootprice = NULL;
    }
    BST(const BST_Node<T>& r){
        rootname = &r;
        rootprice = &r;
    }
    void clear(){
        rootname = NULL;
        rootprice = NULL;
    }
    bool isEmpty(){
        return rootname == NULL;
    }


    void add_item(T& item){

        // Add item based on name
        BST_Node<T>* now = rootname, *prev = NULL;
        while(now != NULL){
            prev = now;
            if(compareByName(now->value, item)){
                now = now->left;
            } else {
                now = now->right;
            }
        }
        if(rootname == NULL){
            rootname = new BST_Node<T>(item);
        } else if (compareByName(prev->value, item)){
            prev->left = new BST_Node<T>(item);
        } else {
            prev->right = new BST_Node<T>(item);
        }


        // Add item based on price
        now = rootprice;
        prev = NULL;
        while(now != NULL){
            prev = now;
            if(compareByPrice(now->value, item)){
                now = now->left;
            } else {
                now = now->right;
            }
        }
        if(rootprice == NULL){
            rootprice = new BST_Node<T>(item);
        } else if (compareByPrice(prev->value, item)){
            prev->left = new BST_Node<T>(item);
        } else {
            prev->right = new BST_Node<T>(item);
        }
    }

    void Ascending_Order(BST_Node<T>* node) {
        if (node != nullptr) {
            Ascending_Order(node->left);
            node->value.print();
            Ascending_Order(node->right);
        }
    }
    void Ascending_Price() {
        Ascending_Order(rootprice);
    }
    void Ascending_Name() {
        Ascending_Order(rootname);
    }


    void Descending_Order(BST_Node<T>* node) {
        if (node != nullptr) {
            Descending_Order(node->right);
            node->value.print();
            Descending_Order(node->left);
        }
    }
    void Descending_Price() {
        Descending_Order(rootprice);
    }
    void Descending_Name() {
        Descending_Order(rootname);
    }

    BST_Node<T>* removeNode(BST_Node<T>* root,const T& r, bool (*compare)(const Item&, const Item&)) {

        //Search in tree
        BST_Node<T> *now = root;
        BST_Node<T> *parent = NULL;

        while (now != NULL && !(now->value == r)) {
            parent = now;
            if (compare(r, now->value)) {
                now = now->right;

            }else {
                now = now->left;
            }

        }

        //if not found
        if (now == NULL) {
            cout << "Item not found\n";
            return root;
        }

        //case#1 no children to the node
        if (now->right == NULL && now->left == NULL) {
            if (parent == NULL) { //if now is the root
                root = NULL;
            } else if (parent->left == now) {
                parent->left = NULL;
            } else {
                parent->right = NULL;
            }
            delete now;

            return root;
        }

        //cas2 one child
        if (now->right != NULL && now->left == NULL) {
            if (parent == NULL) {
                root = now->right;
            } else if (parent->left == now) {
                parent->left = now->right;
            } else {
                parent->right = now->right;
            }
            delete now;
            return root;
        } else if (now->left != NULL && now->right == NULL) {
            if (parent == NULL) {
                root = now->left;
            } else if (parent->left == now) {
                parent->left = now->left;
            } else {
                parent->right = now->left;
            }
            delete now;
            return root;
        }

        //case3 two children
        //find the min item in the right subtree
        BST_Node<T> *minitem = now->right;
        BST_Node<T> *miniParent = now;
        while (minitem->left != NULL) {
            miniParent = minitem;
            minitem = minitem->left;
        }

        now->value = minitem->value;

        if (miniParent->left == minitem) {
            miniParent->left = minitem->right;
        } else {
            miniParent->right = minitem->right;
        }
        delete minitem;
        return root;
    }
    void Remove_item(const Item& item) {
        rootname = removeNode(rootname, item, compareByName);
        rootprice = removeNode(rootprice, item, compareByPrice);
    }


};

#endif //UNTITLED_BST_H
