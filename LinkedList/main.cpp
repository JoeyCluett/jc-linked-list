#include <iostream>
#include "LinkedList.h"

using namespace std;

LinkedList<int>   LL_int;   //create a linked list of integers
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
    //cout << "size of integer LL: " << LL_int.getSize() << endl;
    for(int i = 0; i < 20; i++) {
        LL_int.addToEnd(new int(i));
        //cout << "size of integer LL: " << LL_int.getSize() << endl;
    }

    for(int i = 41; i < 60; i++) {
        LL_int.addToBegin(new int(i));
    }

    LL_int.addToBegin(new int(-999));
    LL_int.addToBegin(new int(-2345));
    LL_int.addToEnd(new int(-2000000000));

    LL_int.makeCallBack();
    cout << "Smallest element: " << lowest_value << endl;

    LL_int.removeEnd();
    first_data = true;
    LL_int.makeCallBack();
    cout << "Smallest element after removing last element: " << lowest_value << endl;

    LL_int.removeBegin();
    first_data = true;
    LL_int.makeCallBack();
    cout << "Smallest element after removing first element: " << lowest_value << endl;

    return 0;
}
