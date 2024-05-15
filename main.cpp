#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
using namespace std;

class Item {
public:
    string itemname;
    string category;
    int price;
    Item(string Name="", string Category="", int Price=0){
        itemname = Name;
        category = Category;
        price = Price;
    }
    bool operator<(const Item& t){
        return this->itemname < t.itemname;
    }
    bool operator==(const Item& t){
        return (this->itemname == t.itemname && this->category == t.category && this->price == t.price);
    }
    void print (){
        cout<<"Name: "<<itemname<<", Category: "<<category<<", Price: "<<price<<'\n';
    }
};
bool compareByName(Item& i1, Item& i2) {
    return i1.itemname > i2.itemname;
}
bool compareByPrice(Item& i1, Item& i2) {
    return i1.price > i2.price;
}


void printItemsList(vector<Item>& items) {
    for (auto& item : items) {
        item.print();
    }
}

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


void heapifyMin(vector<Item>& arr, int size, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && arr[left].price > arr[smallest].price)
        smallest = left;

    if (right < size && arr[right].price > arr[smallest].price)
        smallest = right;

    if (smallest != index) {
        swap(arr[index], arr[smallest]);
        heapifyMin(arr, size, smallest);
    }
}

// Function to heap sort items by price in ascending order
void heapSortMin(vector<Item>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMin(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyMin(arr, i, 0);
    }
}

// Function to heapify for max heap based on item price
void heapifyMax(vector<Item>& arr, int size, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < size && arr[left].price < arr[largest].price)
        largest = left;

    if (right < size && arr[right].price < arr[largest].price)
        largest = right;

    if (largest != index) {
        swap(arr[index], arr[largest]);
        heapifyMax(arr, size, largest);
    }
}

// Function to heap sort items by price in descending order
void heapSortMax(vector<Item>& arr) {
    int n = arr.size();

    for (int i = n / 2 - 1; i >= 0; i--)
        heapifyMax(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapifyMax(arr, i, 0);
    }
}

// Function to sort items alphabetically by name in ascending order
void sortByNameAscending(vector<Item>& arr) {
    sort(arr.begin(), arr.end(), [](const Item& a, const Item& b) {
        return a.itemname < b.itemname;
    });
}

// Function to sort items alphabetically by name in descending order
void sortByNameDescending(vector<Item>& arr) {
    sort(arr.begin(), arr.end(), [](const Item& a, const Item& b) {
        return a.itemname > b.itemname;
    });
}

// Function to print items
void printItems(const vector<Item>& items) {
    for (const auto& item : items) {
        cout << "Name: " << item.itemname << ", category: " << item.category << ", price: EGP" << item.price << endl;
    }
}


int main() {
    vector<Item> items;
    ifstream inputFile("items.txt");
    if (inputFile.is_open()) {
        readItems(inputFile, items);
        inputFile.close();
    } else {
        cout << "Unable to open file." << endl;
        return 1;
    }

    cout << "Items before sorting:" << endl;
    printItems(items);
    cout<<"-------------------------------------------\n";

    // Sorting items by price in ascending order
    heapSortMin(items);
    cout << "\nItems after sorting by price (ascending order - Min Heap):" << endl;
    printItems(items);
    cout<<"-------------------------------------------\n";

    // Sorting items by price in descending order
    heapSortMax(items);
    cout << "\nItems after sorting by price (descending order - Max Heap):" << endl;
    printItems(items);
    cout<<"-------------------------------------------\n";

    // Sorting items by name in ascending order
    sortByNameAscending(items);
    cout << "\nItems after sorting by name (ascending order - Min Heap):" << endl;
    printItems(items);
    cout<<"-------------------------------------------\n";

    // Sorting items by name in descending order
    sortByNameDescending(items);
    cout << "\nItems after sorting by name (descending order - Max Heap):" << endl;
    printItems(items);
    cout<<"-------------------------------------------\n";


    //name must be upercase
    BST<Item>tree;
    for(auto i: items){
        tree.add_item(i);
    }
    Item c = items[1];
    tree.Remove_item(c);


    cout<<"Sorted by their name ascending\n";
    tree.Ascending_Name();
    cout<<"-------------------------------------------\n";

    cout<<"Sorted by their price ascending\n";
    tree.Ascending_Price();
    cout<<"-------------------------------------------\n";

    cout<<"Sorted by their name descending\n";
    tree.Descending_Name();
    cout<<"-------------------------------------------\n";

    cout<<"Sorted by their price descending\n";
    tree.Descending_Price();
    cout<<"-------------------------------------------\n";

    return 0;
}
