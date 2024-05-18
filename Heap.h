//
// Created by Lenovo on 5/18/2024.
//

#ifndef UNTITLED_HEAP_H
#define UNTITLED_HEAP_H
#include "Item.h"

#include <bits/stdc++.h>

using namespace std;
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

        if (left < size && arr[left].price > arr[smallest].price)
            smallest = left;

        if (right < size && arr[right].price > arr[smallest].price)
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

        if (left < size && arr[left].itemname > arr[smallest].itemname)
            smallest = left;

        if (right < size && arr[right].itemname > arr[smallest].itemname)
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

        if (left < size && arr[left].price < arr[largest].price)
            largest = left;

        if (right < size && arr[right].price < arr[largest].price)
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

        if (left < size && arr[left].itemname < arr[largest].itemname)
            largest = left;

        if (right < size && arr[right].itemname < arr[largest].itemname)
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
public:
    void pop_price() {
        if (size() == 0)
            cout << "Empty heap";
        else {
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown_price(0);
        }
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
public:
    void pop_price() {
        if (size() == 0)
            cout << "Empty heap";
        else {
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown_price(0);
        }
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
};

#endif //UNTITLED_HEAP_H
