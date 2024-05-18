//
// Created by Lenovo on 5/18/2024.
//

#ifndef UNTITLED_ITEM_H
#define UNTITLED_ITEM_H
#include <bits/stdc++.h>

using namespace std;
class Item {
public:
    string itemname;
    string category;
    int price;
    Item(string Name="", string Category="", int Price=0) {
        itemname = Name;
        category = Category;
        price = Price;
    }
    bool operator<(const Item& t) {
        return this->itemname < t.itemname;
    }
    bool operator>(const Item& t) {
        return this->itemname > t.itemname;
    }
    bool operator==(const Item& t) {
        return (this->itemname == t.itemname && this->category == t.category && this->price == t.price);
    }
    void print() {
        cout << "Name: " << itemname << ", Category: " << category << ", Price: " << price << '\n';
    }
    bool compareByName(Item& i1, Item& i2) {
        return i1.itemname > i2.itemname;
    }
    bool compareByPrice(Item& i1, Item& i2) {
        return i1.price > i2.price;
    }
    string getitemname() const {
        return itemname;
    }
    int getPrice() const {
        return price;
    }
};
#endif //UNTITLED_ITEM_H
