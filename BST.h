//
// Created by Lenovo on 5/18/2024.
//

#ifndef UNTITLED_BST_H
#define UNTITLED_BST_H
#include "Item.h"

#include <bits/stdc++.h>

using namespace std;
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
    vector<T>list;
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
        list.push_back(item);
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
    void Remove_item(T& r) {
        auto it = find(list.begin(), list.end(), r);
        if (it != list.end()) {
            list.erase(it);
        }

        //Search for Name tree
        BST_Node<T> *now = rootname;
        BST_Node<T> *parent = NULL;

        while (now != NULL) {
            if (now->value == r) {
                // Item found, perform removal
                //...
                break; // Exit loop once removal is done
            } else if (compareByName(r, now->value)) {
                now = now->right;
            } else {
                now = now->left;
            }
        }
        //if not found
        if (now == NULL) {
            cout << "Item not found\n";
            return;
        }
        //...
    }

    void Display_Normally(){
        for(auto i : list){
            i.print();
        }
    };
};

#endif //UNTITLED_BST_H
