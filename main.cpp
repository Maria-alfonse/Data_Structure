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
};
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

class Heap {
protected:
    vector<Item> heap;
public:
    void insert(Item item) {
        heap.push_back(item);
    }

    void pop() {
        heap.pop_back();
    }

    void print_heap() {
        for (Item item : heap) {
            cout << item.itemname << endl;
            cout << item.category << endl;
            cout << item.price << endl;
        }
    }

    int size() {
        return heap.size();
    }

    bool empty() {
        return size() == 0;
    }

    virtual void heapifyDown_price(int i) = 0;
    virtual void heapifyDown_name(int i) = 0;
    virtual void heapifyUp_price(int i) = 0;
    virtual void heapifyUp_name(int i) = 0;

    void insertPrice(Item item) {
        heap.push_back(item);
        int index = size() - 1;
        heapifyUp_price(index);
    }

    void insertName(Item item) {
        heap.push_back(item);
        int index = size() - 1;
        heapifyUp_name(index);
    }

    void pop_name() {
        if (size() == 0)
            cout << "Empty heap";
        else {
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown_name(0);
        }
    }

    void pop_price() {
        if (size() == 0)
            cout << "Empty heap";
        else {
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown_price(0);
        }
    }

    void heapifyMinPrice(vector<Item>& arr, int size, int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && arr[left].price < arr[smallest].price)
            smallest = left;

        if (right < size && arr[right].price < arr[smallest].price)
            smallest = right;

        if (smallest != index) {
            swap(arr[index], arr[smallest]);
            heapifyMinPrice(arr, size, smallest);
        }
    }

    void heapifyMinName(vector<Item>& arr, int size, int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && arr[left].itemname < arr[smallest].itemname)
            smallest = left;

        if (right < size && arr[right].itemname < arr[smallest].itemname)
            smallest = right;

        if (smallest != index) {
            swap(arr[index], arr[smallest]);
            heapifyMinName(arr, size, smallest);
        }
    }

    void heapifyMaxPrice(vector<Item>& arr, int size, int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && arr[left].price > arr[largest].price)
            largest = left;

        if (right < size && arr[right].price > arr[largest].price)
            largest = right;

        if (largest != index) {
            swap(arr[index], arr[largest]);
            heapifyMaxPrice(arr, size, largest);
        }
    }

    void heapifyMaxName(vector<Item>& arr, int size, int index) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && arr[left].itemname > arr[largest].itemname)
            largest = left;

        if (right < size && arr[right].itemname > arr[largest].itemname)
            largest = right;

        if (largest != index) {
            swap(arr[index], arr[largest]);
            heapifyMaxName(arr, size, largest);
        }
    }

    // Function to heap sort items by price in descending order
    void heapSortMaxPrice() {
        int n = heap.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyMaxPrice(heap, n, i);
        for (int i = n - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            heapifyMaxPrice(heap, i, 0);
        }
    }

    void heapSortMaxName() {
        int n = heap.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyMaxName(heap, n, i);
        for (int i = n - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            heapifyMaxName(heap, i, 0);
        }
    }

    void heapSortMinPrice() {
        int n = heap.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyMinPrice(heap, n, i);
        for (int i = n - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            heapifyMinPrice(heap, i, 0);
        }
    }

    void heapSortMinName() {
        int n = heap.size();

        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyMinName(heap, n, i);
        for (int i = n - 1; i > 0; i--) {
            swap(heap[0], heap[i]);
            heapifyMinName(heap, i, 0);
        }
    }
};

class minHeap : public Heap {
    void heapifyDown_price(int i) override {
        heapifyMinPrice(heap, heap.size(), i);
    }

    void heapifyDown_name(int i) override {
        heapifyMinName(heap, heap.size(), i);
    }

    void heapifyUp_price(int i) override {
        if (i && heap[(i - 1) / 2].price > heap[i].price) {
            swap(heap[i], heap[(i - 1) / 2]);
            heapifyUp_price((i - 1) / 2);
        }
    }

    void heapifyUp_name(int i) override {
        if (i && heap[(i - 1) / 2] > heap[i]) {
            swap(heap[i], heap[(i - 1) / 2]);
            heapifyUp_name((i - 1) / 2);
        }
    }
};

class maxHeap : public Heap {
    void heapifyUp_price(int i) override {
        int parent = (i - 1) / 2;
        if (parent >= 0) {
            if (heap[i].price > heap[parent].price) {
                swap(heap[i], heap[parent]);
                heapifyUp_price(parent);
            }
        }
    }

    void heapifyUp_name(int i) override {
        int parent = (i - 1) / 2;
        if (parent >= 0) {
            if (heap[i].itemname > heap[parent].itemname) {
                swap(heap[i], heap[parent]);
                heapifyUp_name(parent);
            }
        }
    }

    void heapifyDown_price(int i) override {
        heapifyMaxPrice(heap, heap.size(), i);
    }

    void heapifyDown_name(int i) override {
        heapifyMaxName(heap, heap.size(), i);
    }
};

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
    vector<Item> heap;
    ifstream input("items.txt"); // Open the file
    if (!input.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }

    readItems(input, heap);
    cout<<"1-Binary Search Tree (BST)"<<endl;
    cout<<"2-Heaps"<<endl;
    cout<<"3-AVL Trees"<<endl;
    cout<<"please enter the numbeer of the data structure you want:";
    int ans;
    cin>>ans;
    if(ans==1){

    }
    if(ans==2){
        int choice;
        do{
            showMenu();
            cin>>choice;
            if(choice==1){

            }
            if(choice==2){

            }
            if(choice==3){
                
            }
            if(choice ==4){

            }
            if(choice==5){

            }
            if(choice==6){

            }
            if(choice==7){

            }
        } while (choice!=0);
    }

    return 0;
}
