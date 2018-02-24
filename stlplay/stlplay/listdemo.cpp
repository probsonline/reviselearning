//
//  listdemo.cpp
//  stlplay
//
//  Created by Anwar, Kaleem on 2/22/18.
//  Copyright © 2018 det. All rights reserved.
//

#include "demo.h"
#include <list>
#include <algorithm>

class listDemo{
public:
    listDemo(){}
    void print_list(list<string> &l);
    void print_list(list<int> &l);
    ~listDemo(){}
};

void listDemo::print_list(list<string> &l){
    cout << "Size: " << l.size() << "\t" << "Elements: " ;

    list<string>::iterator it = l.begin();
    
    while (it != l.end()) {
        cout << *it << " ";
        it++;
    }
    cout << endl;
}
void listDemo::print_list(list<int> &l){

    cout << "Size: " << l.size() << "\t" << "Elements: " ;
    
    list<int>::iterator it = l.begin();
    
    while (it != l.end()) {
        cout << *it << " ";
        it++;
    }
    cout << endl;
}


void list_demo(){
    listDemo ld;

    string names[] = {"Naveed", "Nadeem", "Kaleem", "Naeem", "Waseem", "Adeel"};
    int listSize=7;
    list<string> l1(listSize);
    l1.assign(names, names+6);
    ld.print_list(l1);

    list<int> l2(3, 1);
    
    ld.print_list(l2);
    
}
