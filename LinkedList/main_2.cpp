#include <iostream>
#include "LinkedList.h"
#include <vector>

using namespace std;

LinkedList<int>   LL_int(20);   //create a linked list of 20 integer pointers
//LinkedList<float> LL_float(0);  //create a linked list of floats

int lowest_value;
bool first_data = true;

//template to make LinkedList work with arbitrary data
template<class Z>
void function_to_call(Z* num_1) {
    //callback function will find smallest value in linked list of integers
    if(first_data) {
        lowest_value = *num_1;
        first_data = false;
    } else {
        if(*num_1 < lowest_value)
            lowest_value = *num_1;
    }
}

struct new_obj {
    int a, b, c;
};

int main(int argc, char* argv[]) {

    LL_int.callback_function = &function_to_call; //assigning the callback function
    cout << "Size of integer LL: " << LL_int.getSize() << endl;

    vector<int*>* v_ptr = LL_int.getAddresses(); //method returns pointer to vector of pointers
    cout << "Size of v_ptr: " << v_ptr->size() << endl; //vector is same size as linked list

    return 0;
}
