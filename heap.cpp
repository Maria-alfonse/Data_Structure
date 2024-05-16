#include <bits/stdc++.h>

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
    bool operator>(const Item& t){
        return this->itemname > t.itemname;
    }
    bool operator==(const Item& t){
        return (this->itemname == t.itemname && this->category == t.category && this->price == t.price);
    }
    void print (){
        cout<<"Name: "<<itemname<<", Category: "<<category<<", Price: "<<price<<'\n';
    }
};
class Heap{
protected:
    vector<Item> heap;
public:
    void insert(Item item){
        heap.push_back(item);
    }

    void pop(){
        heap.pop_back();
    }

    void print_heap(){
        for(Item item:heap){
            cout<<item.itemname<<endl;
            cout<<item.category<<endl;
            cout<<item.price<<endl;
        }
    }
    int size(){
        return heap.size();
    }

    bool empty(){
        return size()==0;
    }
};
class minHeap:public Heap{

    void heapifyDown_price(int i){
        int left=2*i+1;
        int right= 2*i+2;
        int smallest=i;

        if(left<size()&& heap[left].price<heap[i].price){
            smallest=left;
        }

        if(right<size()&& heap[right].price<heap[smallest].price){
            smallest=right;
        }
        if(smallest!=i){
            swap(heap[i],heap[smallest]);
            heapifyDown_price(smallest);
        }
    }

    void heapifyDown_name(int i){
        int left=2*i+1;
        int right= 2*i+2;
        int smallest=i;

        if(left<size()&& heap[left].itemname<heap[i].itemname){
            smallest=left;
        }

        if(right<size()&& heap[right].itemname<heap[smallest].itemname){
            smallest=right;
        }
        if(smallest!=i){
            swap(heap[i],heap[smallest]);
            heapifyDown_name(smallest);
        }
    }

    void heapifyUp_price(int i){
        if(i && heap[(i-1)/2].price>heap[i].price){
            swap(heap[i],heap[(i-1)/2]);
            heapifyUp_price((i-1)/2);
        }
    }

    void heapifyUp_name(int i){
        if( heap[(i-1)/2]>heap[i]){
            swap(heap[i],heap[(i-1)/2]);
            heapifyUp_name((i-1)/2);
        }
    }

public:
    void insert_name(Item item){
        heap.push_back(item);
        int index=size()-1;
        heapifyUp_name(index);
    }
    void insert_price(Item item){
        heap.push_back(item);
        int index=size()-1;
        heapifyUp_price(index);
    };

    void pop_name(){
        if(size()==0)
            cout<<"Empty heap";
        else{
            heap[0]=heap.back();
            heap.pop_back();
            heapifyDown_name(0);
        }
    }
    void pop_price(){
        if(size()==0)
            cout<<"Empty heap";
        else{
            heap[0]=heap.back();
            heap.pop_back();
            heapifyDown_price(0);
        }
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
void print_heap(vector<Item>& heap){
    for(Item item:heap){
        cout<<item.itemname<<endl;
        cout<<item.category<<endl;
        cout<<item.price<<endl;
    }
}

int main() {
    vector<Item>heap;
    ifstream input("D:\\untitled\\items.txt"); // Open the file
    if (!input.is_open()) {
        cout << "Failed to open the file." << endl;
        return 1;
    }
//    cout<<"1-Binary Search Tree (BST)"<<endl;
//    cout<<"2-Heaps"<<endl;
//    cout<<"3-AVL Trees"<<endl;
//    cout<<"Please choose the number of the tree data structure you want: "<<endl;
//    int ans;
//    cin>>ans;
    readItems(input,heap);
    minHeap heap1,heap2;

    //min heap by name
    for(int i=0;i<heap.size();i++){
        heap1.insert_name(heap[i]);
    }
//    heap1.print_heap();

    //min heap by price
    for(int i=0;i<heap.size();i++){
        heap2.insert_price(heap[i]);
    }
    heap2.print_heap();


    return 0;
}



