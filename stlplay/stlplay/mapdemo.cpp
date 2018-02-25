//
//  mapdemo.cpp
//  stlplay
//
//  Created by Anwar, Kaleem on 2/25/18.
//  Copyright © 2018 det. All rights reserved.
//

#include "demo.h"
#include <map>
#include <algorithm>
#include <array>

//Besides palying with map, which stores key, value pairs in sorted order, the demo explores <array> DS, types of object creation (on stack vs on heap). It also uses 'auto' as defined in c++ 11;
class myMap{
public:
    myMap();
    ~myMap();
    
    void add_to_map(int x, int y);
    void add_to_map(int id, string name);
    void populate_map();
    void swap();
    void remove_value_from_map(string name);
    void remove_key_from_map(int key);
    void clear_map();
    void print_map();

private:
    map<int, int> aMap;                 //declared and defined and the object is created on stack. This object is managed and doesn't require explicit deletion.
    map<int, string> *idMapping;        //Declared a reference to the object. The object is not creatd. it can be later created using new and then it will be allocated on heap. This will require explicit deletion in destructor.
};

myMap::myMap(){
    idMapping = new map<int, string>;
}

myMap::~myMap(){
    delete idMapping;
}

void myMap::add_to_map(int x, int y ){
    pair<int, int> p(x,y);
    aMap.insert(p);
}

void myMap::add_to_map(int id, string name){
    pair<int, string> p;
    p.first = id;
    p.second = name;
    idMapping->insert(p);
}

void myMap::remove_value_from_map(string name){
    
    auto it = idMapping->begin();       //auto is new to C++11 and it means that it will find the type from the assigned vaue automatically. Not need to explicity say map<int, string>::iterator here.
    
    while (it!=idMapping->end()) {
        if(it->second == name)
            break;
        it++;
    }

    if (it != idMapping->end()) {
        idMapping->erase(it);
    }
    else{
        cout << name << " not found in the map " << endl;
    }
}

void myMap::remove_key_from_map(int key){
    auto it = aMap.find(key);
    if(it!=aMap.end()){     //it is a reference and so can't be compared against NULL so isntead check if reached the end but found nothing
        aMap.erase(it);
    }
    else
    {
        cout << key << " not found in the map" << endl;
    }
}

void myMap::swap(){
    map<int, string> kFamily = {{7, "Abbu Ji"}, {1, "K"}, {2, "M"}, {3, "G"}, {4, "S"}, {5, "Q"}, {6, "B"}};
    idMapping->swap(kFamily);
}

void myMap::populate_map(){
    array<string, 6> names={"Naveed", "Nadeem", "Kaleem", "Naeem", "Waseem", "Adeel"};
    
    srand(time(NULL));
    pair <int, int> p;
    for (int i=0; i<rand()%10; i++) {
        p.first = i;
        p.second = -i;
        aMap.insert(p);
    }
    
    pair<int, string> p2;
    for (int i=0; i<names.size(); i++) {
        p2.first = i+1;
        p2.second = names[i];
        idMapping->insert(p2);
    }
}

void myMap::clear_map(){
    aMap.clear();
    idMapping->clear();
}

void myMap::print_map(){
    if (aMap.size()!=0 || idMapping->size() !=0) {
        map<int, int>::iterator it=aMap.begin();
        while (it!=aMap.end()) {
            cout << "(" << it->first << ", " << it->second << ")" << " , " ;
            it++;
        }
        cout << endl;
        
        for (map<int, string>::iterator it=idMapping->begin(); it!=idMapping->end(); it++) {
            cout << "(" << it->first << ", " << it->second << ")" << " , " ;
        }
        cout << endl;
    }
    else{
        cout << "No entry in the map " << endl;
    }
}

void map_demo(){

    myMap myMap;
    
    cout << "Map Demo" << endl;
    
    myMap.populate_map();
    myMap.print_map();
    
    int key=99, val=47;
    string name = "Abbu Ji";
    cout << "Adding " << "(" << key << "," << val <<") to map" << endl;
    myMap.add_to_map(key, val);
    cout << "adding " << name << " to map also " << endl;
    myMap.add_to_map(0, name);
    myMap.print_map();

    cout << "Swapping family map" << endl;
    myMap.swap();
    myMap.print_map();
    
    cout << "SHowing that a map can't have a duplicate but a multimap can have it" << endl;
    key=99; val=47;
    name = "Abbu Ji";
    cout << "Adding " << "(" << key << "," << val <<") to map" << endl;
    myMap.add_to_map(key, val);
    cout << "adding " << name << " to map again " << endl;
    myMap.add_to_map(0, name);
    myMap.print_map();
    
    cout << "Removing " << name << "from map" << endl;
    myMap.remove_value_from_map(name);
    myMap.print_map();
    name = "a Guy";
    cout << "Removing " << name << "from map" << endl;
    myMap.remove_value_from_map(name);

    cout << "Removing " << key << "from map" << endl;
    myMap.remove_key_from_map(key);
    myMap.print_map();
    key = -1;
    cout << "Removing " << key << "from map" << endl;
    myMap.remove_key_from_map(key);

    cout << "Clearing map" << endl;
    myMap.clear_map();
    myMap.print_map();
    

    
}

