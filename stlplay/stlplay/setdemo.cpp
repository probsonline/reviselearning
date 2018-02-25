//
//  setdemo.cpp
//  stlplay
//
//  Created by Anwar, Kaleem on 2/25/18.
//  Copyright © 2018 det. All rights reserved.
//

#include "demo.h"
#include <set>
#include <algorithm>

//Set provides unique values in sorted order (stored internally in a binary search tree

class mySet{
public:
    mySet(){};
    ~mySet(){};
    
    void populate_set();
    void add_to_set(string city);
    void remove_from_set(string str);
    void add_city(string city);
    void clean();
    void print_set();
private:
    //We cannot have the size of array determinzed from static initializer inside a class as it can be overwridden/overwrittedn in a class method/constructor
    //In order to get that done, we need to specifically set the size (or alternatively use static constexpr if it's a basic data type as int)
    string state_letters[50]={"AL","AK",
        "AZ",
        "AR",
        "CA",
        "CO",
        "CT",
        "DE",
        "FL",
        "GA",
        "HI",
        "ID",
        "IL",
        "IN",
        "IA",
        "KS",
        "KY",
        "LA",
        "ME",
        "MD",
        "MA",
        "MI",
        "MN",
        "MS",
        "MO",
        "MT",
        "NE",
        "NV",
        "NH",
        "NJ",
        "NM",
        "NY",
        "NC",
        "ND",
        "OH",
        "OK",
        "OR",
        "PA",
        "RI",
        "SC",
        "SD",
        "TN",
        "TX",
        "UT",
        "VT",
        "VA",
        "WA",
        "WV",
        "WI",
        "WY"
    };
    set<string> states;
    multiset<string> cities;
    
    
};

void mySet::populate_set(){
    cout << "Creating sets" << endl;

    for (int i=0; i<sizeof(state_letters)/sizeof(state_letters[0]); i++) {
        states.insert(state_letters[i]);
    }
    
    cities.insert("Santa Clara");
    cities.insert("Santa Jose");
    cities.insert("Santa Francisco");
    cities.insert("New York");
    print_set();
}

void mySet::add_to_set(string str){
    cout << "Adding " << str << "to set" << endl;
    states.insert(str);
    print_set();
}

void mySet::remove_from_set(string str){
    cout << "Removing " << str << "from set" << endl;
    states.erase(str);
    print_set();
}

void mySet::add_city(string city){
    cout << "Adding " << city << " to set" << endl;
    cities.insert(city);
    print_set();
}
void mySet::clean(){
    cout << "Clearing sets" << endl;
    states.clear();
    cities.clear();
    print_set();
}
void mySet::print_set(){
    
    if (states.size() >0 && cities.size() > 0) {
        set<string>::iterator it = states.begin();
        cout << "{ ";
        for (; it!=states.end(); it++) {
            cout << *it << " , ";
        }
        cout << " }" << endl;
        
        cout << "{ ";
        it = cities.begin();
        for (; it!=cities.end(); it++) {
            cout << *it << " , ";
        }
        cout << " }" << endl;
    }
    else{
        cout << "Nothing in the sets\n";
    }
    
}

void set_demo(){
    mySet aSet;
    
    aSet.populate_set();

    cout << "======Showing that set has unique members" << endl;
    aSet.add_to_set("TX");
    aSet.remove_from_set("TX");
    aSet.add_to_set("TX");
    aSet.add_city("Boston");
    cout << "====Adding Boston again to show it cab be added in a multiset" << endl;
    aSet.add_city("Boston");
    aSet.add_city("Chicago");
    aSet.clean();
    cout << "Once set is cleared, nothing can be added to it " <<endl;
    aSet.add_city("Boulder");

}

