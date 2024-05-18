#include <bits/stdc++.h>
#include "Items.h"
#include "Heap.h"
#include "AVLTrees.h"
#include "BST.h"
using namespace std;
void readItems(istream& input, vector<Item>& items) {
    string name, category, priceStr;
    int price;
    while (getline(input, name)) {
        getline(input, category);
        getline(input, priceStr);
        if (!name.empty() && !category.empty() && !priceStr.empty()) {
            stringstream ss(priceStr);
            ss >> price;
            items.push_back(Item(name, category, price));
        }
    }
}


template<class T>
void read(istream& input, AVLTree<T>& tree) {
    int numItems;
    input >> numItems;

    for (int i = 0; i < numItems; ++i) {
        string itemName, category;
        int price;

        input.ignore();
        getline(input, itemName);
        getline(input, category);
        input >> price;

        tree.insert(Item(itemName, category, price));
    }
}



void print_heap(vector<Item>& heap) {
    for (Item item : heap) {
        cout << item.itemname << endl;
        cout << item.category << endl;
        cout << item.price << endl;
    }
}

void showMenu() {
    cout << "1. Add item data" << endl;
    cout << "2. remove item data" << endl;
    cout << "3. Display the item data normally" << endl;
    cout << "4. Display all the items sorted by their name ascending" << endl;
    cout << "5. Display all the items sorted by their name descending" << endl;
    cout << "6. Display all the items sorted by their prices ascending" << endl;
    cout << "7. Display all the items sorted by their prices descending" << endl;
    cout << "0. Exit" << endl;
    cout << "Please enter your choice: ";
}

int main() {
    vector<Item> items;
    ifstream input("C:\\Users\\hhaym\\Documents\\clionprojects\\Data_Structures\\items.txt"); // Open the file

    readItems(input, items);
    if (!input.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    readItems(input, items);
    cout<<"1-Binary Search Tree (BST)"<<endl;
    cout<<"2-Heaps"<<endl;
    cout<<"3-AVL Trees"<<endl;
    cout<<"please enter the number of the data structure you want:";
    int ans;
    cin>>ans;
    if(ans==1){
        BST<Item>tree;
        for(auto i:items){
            tree.add_item(i);
        }
        bool a = 1;
        while(a){
            showMenu();
            int c; cin>>c;
            if(c==1){
                Item new_item ;
                cout<<"Enter Item name: ";
                cin>>new_item.itemname;
                cout<<"\nEnter Item category: ";
                cin>>new_item.category;
                cout<<"\nEnter Item price: ";
                cin>>new_item.price;
                tree.add_item(new_item);
                items.push_back(new_item);
            }else if(c==2){
                Item delete_item ;
                cout<<"Enter Item name: ";
                cin>>delete_item.itemname;
                cout<<"\nEnter Item category: ";
                cin>>delete_item.category;
                cout<<"\nEnter Item price: ";
                cin>>delete_item.price;
                tree.Remove_item(delete_item);

                auto it = std::find(items.begin(), items.end(), delete_item);
                if (it != items.end()) {
                    items.erase(it);
                }
            }else if(c==3) {
                for(auto i:items){
                    i.print();
                }
            }else if(c==4){
                tree.Ascending_Name();
            }else if(c==5) {
                tree.Descending_Name();
            }else if(c==6){
                tree.Ascending_Price();
            }else if(c==7){
                tree.Descending_Price();
            }else if(c==0){
                a = 0;
            }
        }

    }
    else if (ans == 2) {
        minHeap minheap;
        maxHeap maxheap;
        for (Item& item : items) {
            minheap.insertPrice(item);
            maxheap.insertPrice(item);
        }

        int choice;
        do {
            showMenu();
            cin >> choice;
            if (choice == 1) {
                string name, category;
                int price;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter category: ";
                cin >> category;
                cout << "Enter price: ";
                cin >> price;
                Item newItem(name, category, price);
                minheap.insertPrice(newItem);
                maxheap.insertPrice(newItem);
            }
            else if (choice == 2) {
                cout << "1. Remove by name (MinHeap)" << endl;
                cout << "2. Remove by name (MaxHeap)" << endl;
                cout << "3. Remove by price (MinHeap)" << endl;
                cout << "4. Remove by price (MaxHeap)" << endl;
                int removeChoice;
                cin >> removeChoice;
                if (removeChoice == 1) {
                    minheap.pop_name();
                }
                else if (removeChoice == 2) {
                    maxheap.pop_name();
                }
                else if (removeChoice == 3) {
                    minheap.pop_price();
                }
                else if (removeChoice == 4) {
                    maxheap.pop_price();
                }
            }
            else if (choice == 3) {
                cout << "Heap items (MinHeap):" << endl;
                minheap.print_heap();
                cout << "Heap items (MaxHeap):" << endl;
                maxheap.print_heap();
            }
            else if (choice == 4) {
                cout << "Items sorted by name ascending (MinHeap):" << endl;
                minheap.heapSortMinName();
                minheap.print_heap();
            }
            else if (choice == 5) {
                cout << "Items sorted by name descending (MaxHeap):" << endl;
                maxheap.heapSortMaxName();
                maxheap.print_heap();
            }
            else if (choice == 6) {
                cout << "Items sorted by price ascending (MinHeap):" << endl;
                minheap.heapSortMinPrice();
                minheap.print_heap();
            }
            else if (choice == 7) {
                cout << "Items sorted by price descending (MaxHeap):" << endl;

                maxheap.heapSortMaxPrice();
                maxheap.print_heap();
            }
        } while (choice != 0);
    }
    else {
        AVLTree<Item> avltree;
        ifstream inputFile("C:\\Users\\hhaym\\Documents\\clionprojects\\Data_Structures\\items.txt");
        if (!inputFile) {
            cerr << "Error: Unable to open the file." << endl;
            return 1;
        }
        read(inputFile, avltree);
        inputFile.close();
        int choice;
        do {
            showMenu();
            cin >> choice;
            if (choice == 1) {
                string name, category;
                int price;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter category: ";
                cin >> category;
                cout << "Enter price: ";
                cin >> price;
                Item newItem(name, category, price);
                avltree.insert(newItem);
            }
            else if (choice == 2) {
                string name, category;
                int price;
                cout << "Enter item name: ";
                cin >> name;
                cout << "Enter category: ";
                cin >> category;
                cout << "Enter price: ";
                cin >> price;
                avltree.remove(Item(name, category, price));
            }
            else if (choice == 3) {
                cout << "Display Normally:\n";
                avltree.displaynormal();
                cout << endl;
            }
            else if (choice == 4) {
                cout << "Sort name in ascending order:\n";
                avltree.AscendingName();
                cout << endl;
            }
            else if (choice == 5) {
                cout << "Sort name in descending order:\n";
                avltree.DescendingName();
                cout << endl;
            }
            else if (choice == 6) {
                cout << "Sort price in ascending order:\n";
                avltree.AscendingPrice();
                cout << endl;
            }
            else if (choice == 7) {
                cout << "Sort price in descending order:\n";
                avltree.DescendingPrice();
                cout << endl;
            }
        } while (choice != 0);
    }

    return 0;
}


