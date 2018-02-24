#include <iostream>

#include <vector>
#include <algorithm>

using namespace std;

void print_vector(vector<int> &v1){
#if 1
    cout << "Capacity: " << v1.capacity();
    cout << "\tSize: " << v1.size();
    cout << " , \tValues: " ;
    
    vector<int>::iterator vIterator;
    
    for (vIterator=v1.begin(); vIterator!=v1.end(); vIterator++) {
        cout << *vIterator  << " ";
    }
    cout << endl;
#else
    cout << "Size: " << v1.size();
    cout << " , \tValues: " ;
    
    for (int i=0; i<v1.size(); i++) {
        cout << v1[i]  << " ";
    }
    cout << endl;
#endif
}
void vector_demo(){
    const int size = 10;
    vector<int> v1; //Vector container in STL adds the values at the end
    
    for (int i=0; i<size; i++) {
        v1.push_back(i+1);    //Add values at the end
    }
    
    print_vector(v1);
    
    cout << "inserting more values" << endl;
    v1.push_back(13);
    print_vector(v1);
    
    cout << "trimming to 7 elements " << endl;
    v1.resize(7);
    print_vector(v1);
    
    cout << "Expanding to 17 elements " << endl;
    v1.resize(17);
    print_vector(v1);
    
    cout << "inserting values at specific locations " << endl;
    v1[11] = 11;
    v1[13] = 13;
    v1.at(1)=20;
    print_vector(v1);
    
    cout << "Find all zero values and fill with some values " << endl;
    for (int i=0; i<v1.size(); i++) {
        if (v1[i] == 0) {
            v1[i] = i*2;
        }
    }
    print_vector(v1);
    
    cout << "Shrinking vector to find the size of the data " << endl;
    v1.shrink_to_fit();
    print_vector(v1);
    
    
    cout << "Sorting vector " << endl;
    sort(v1.begin(), v1.end());
    print_vector(v1);
    
    cout << "Find a specific value (6) in the vector and erase it " << endl;
    //    vector<int>::iterator it=find(v1.begin(), v1.end(), 2);
    //    v1.erase(it);        //Finding a non existent value will throw exception
    v1.erase(find(v1.begin(), v1.end(), 6));        //Finding a non existent value will throw exception
    print_vector(v1);
    
    cout << "Replace 4 with 40 in the vector " << endl;
    v1.insert(find(v1.begin(), v1.end(), 4), 40);
    print_vector(v1);
    
    cout << "replacing the front value with -1" << endl;
    v1.front() = -1;    //front()/back() retruns a referne so it can be used to print the value or change the value
    print_vector(v1);
    
    cout << "Sorting vector in reverse" << endl;
    //    sort(v1.end(), v1.begin()); //Will give finally exception as it will be running into the wild memory due to incorrect parameters
    sort(v1.rbegin(), v1.rend());   //This will properly reverse sort
    print_vector(v1);
    
    cout << "replacing the back value with 0" << endl;
    v1.back() = -3;
    print_vector(v1);
    
    cout << "Cleara all the values in the vector " << endl;
    v1.clear();
    print_vector(v1);
    
    v1.front();
}
