//
//  dequeuedemo.cpp
//  stlplay
//
//  Created by Anwar, Kaleem on 2/22/18.
//  Copyright © 2018 det. All rights reserved.
//

#include "demo.h"
#include <deque>
#include <algorithm>


//Dequue is a vector kind of DS but it can grown on both ends. Vector can grow only on the back
//Will use some class way of writing code to get some practice

class dequeDemo{
    
public:
    dequeDemo(int elementCount);
//    deque<int>& get_dequeu();
    void print_que();
    
    ~dequeDemo(){}
    
    deque<int>& get_dequeu(){
        return this->dq;
    }
private:
    deque<int> dq;
};

dequeDemo::dequeDemo(int elementCount){
    for (int i=0; i<elementCount; i++) {
        //Push even at the front and odd at the back
        if(i%2){
            this->dq.push_back(i);
        }
        else{
            this->dq.push_front(i);
        }
    }
}

void dequeDemo::print_que(){
    deque<int>::iterator it = dq.begin();
    cout << "Size: " << dq.size() << "\t" << "Elements: " ;  //Capacity method doesn't exit for queue
    while (it!=dq.end()) {
        cout << *it << " ";
        it++;
    }
    cout << endl;
}

/*
deque<int>& dequeDemo::get_dequeu(){
    return this->dq;
}
*/

void queu_demo(){
    dequeDemo q1(10);
    
    cout << "Creating a Deque" << endl;
    q1.print_que();
    
    cout << "Sorting deque" << endl;
    sort(q1.get_dequeu().begin(), q1.get_dequeu().end());
    q1.print_que();

    deque<int> q2(5, -21);//Create a que with 5 elements and each with value specified
    cout << "Swapping deque" << endl;
    q1.get_dequeu().swap(q2);
    q1.print_que();
    
    cout << "Clearing deque" << endl;
    q1.get_dequeu().clear();
    q1.print_que();
    
}

