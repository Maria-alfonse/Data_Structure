#include <bits/stdc++.h>
#include "Item.h"
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
    ifstream input("items.txt"); // Open the file
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
                maxheap.heapSortMaxName();
                maxheap.print_heap();
            }
            else if (choice == 5) {
                cout << "Items sorted by name descending (MaxHeap):" << endl;
                minheap.heapSortMinName();
                minheap.print_heap();
            }
            else if (choice == 6) {
                cout << "Items sorted by price ascending (MinHeap):" << endl;
                maxheap.heapSortMaxPrice();
                maxheap.print_heap();
            }
            else if (choice == 7) {
                cout << "Items sorted by price descending (MaxHeap):" << endl;

                minheap.heapSortMinPrice();
                minheap.print_heap();
            }
        } while (choice != 0);
    }

    return 0;
}
