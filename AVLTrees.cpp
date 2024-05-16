// Created by habibaayman on 5/13/2024.

#include "AVLTrees.h"
int main() {
    AVLTree<Item> avl;
    ifstream inputFile("C:\\Users\\hhaym\\Documents\\clionprojects\\Data_Structures\\items.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open the file." << endl;
        return 1;
    }
    readItems(inputFile, avl);
    inputFile.close();
    cout<<"Display Normally:\n";
    avl.displaynormal();
    cout<<endl;
    cout<<"sort name in ascending order:\n";
    avl.AscendingName();
    cout<<endl;
    cout<<"sort name in descending order:\n";
    avl.DescendingName();
    cout<<endl;
    cout<<"sort price in ascending order:\n";
    avl.AscendingPrice();
    cout<<endl;
    cout<<"sort price in descending order:\n";
    avl.DescendingPrice();
    cout<<endl;

    avl.remove(Item("cheddar cheese", "dairy",49 ));
    cout<<"display normally after removing cheedar cheese:\n";
    avl.displaynormal();
    return 0;
}
