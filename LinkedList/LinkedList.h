/*
    Author: Joey Cluett

    Date Created: 1/6/2016

    Date Last Modified: 1/12/2016

    Purpose:
        This library serves to make the usage and management of linked lists easier.

    Misc. Information:
        The linked lists that this library produces are doubly linked lists (nodes
        that are next to each other have pointers to each other). This allows you to
        traverse the list in either direction.

        The callback function that the user is allowed to utilize takes a single pointer
        as an argument and returns void. Make sure your function also follows this format.
        The callback function is used in conjunction with the makeCallBack functions.
        It calls the callback function with each element in the linked list. Remember
        that the linked list only stores pointers to data (data itself is allocated
        elsewhere

        when calling atIndex or using the subscript operator, if the index is not valid,
        both will return a NULL pointer and display, "Non-fatal error: index out of bounds"

    Future revisions:
        support for reverse indexing
            ex.: LL[-1] returns pointer to last element

        support for user defined copy constructor callback function
            uses overloaded assignment operator

        support for inserting data anywhere in linked list
            ex.: LL.insert(index, T*)

        optimize alternate constructor

        DONE: make method to return vector with addresses of all nodes (sys_call to ensure sufficient storage)
*/

#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <vector>

template<class T>
class LinkedList {
    public:
        LinkedList(void);          //default
        LinkedList(int init_size); //creates a linked list with init_size elments. Elements are uninitialized.

        void addToEnd(T* data);   //simply copies data pointer. Usage: LL.addToEnd(new T)
        void addToBegin(T* data); //--                          Usage: LL.addToBegin(new T)

        int getSize(void);

        //user can optionally specify a callback function
        void (*callback_function)(T*);    //easier to make it return void then try to figure out if should return data or pointer
        void makeCallBack(void);          //works with setCallBack to make function call on each element of

        //for accessing individual T pointers
        T* atIndex(int index);

        //overloading the subscript operator, functionally identical to atIndex()
        T* operator[](int index); //

        void removeEnd(void);   //de-allocates memory associted with last element
        void removeBegin(void); //--                                 first element

        //returns a pointer to a vector of pointers to type T
        std::vector<T*>* getAddresses(void);

    private:
        struct node {
            node* prev; //pointer to last node
            node* next; //pointer to next node
            T* datum;   //pointer to data stored in this node
        };

        int num_elements;

        node* first_element = NULL; //pointer is cast to specific type in constructor
        node* last_element = NULL;  //--
};

template<class T> /* Default constructor */
LinkedList<T>::LinkedList(void) {
    num_elements = 0;
}

template<class T> /* Special Constructor */
LinkedList<T>::LinkedList(int init_size) {
    if(init_size == 0){
        num_elements = 0;
        std::cout << "adding zero elements to linked list" << std::endl;
    } else if(init_size > 0) {
        num_elements = 0;
        for(int i = 0; i < init_size; i++) {
            addToEnd(new T);
        }
    } else {
        std::cout << "init_size not valid" << std::endl;
        num_elements = 0;
    }
}

template<class T> /* Add an element to the end of the linked list */
void LinkedList<T>::addToEnd(T* data) {
    //std::cout << "adding to end of linked list" << std::endl; //debug info
    if(num_elements == 0) {
        //must initialize first element with *data
        first_element = new node;
        last_element = first_element;
        first_element->datum = data;

        //next, prev must be null
        first_element->next = NULL;
        first_element->prev = NULL;

        num_elements = 1; //update num_elements to reflect size of linked list

    } else if(num_elements > 0){
        node* temp_ptr = last_element;
        last_element->next = new node;
        last_element = last_element->next; //reassign pointer to last element
        last_element->next = NULL;
        last_element->prev = temp_ptr;
        last_element->datum = data; //assign T pointer in last node
        num_elements++; //update top reflect current size of linked list
    }

    return;
}

template<class T> /* Add an element to the beginning of the linked list */
void LinkedList<T>::addToBegin(T* data) {
    //std::cout << "adding to beginning of linked list" << std::endl;
    if(num_elements == 0) {
        addToEnd(data);
    } else if(num_elements > 0) {
        node* temp_ptr = first_element;
        first_element->prev = new node;
        first_element = first_element->prev; //now pointing to the actual first node
        first_element->next = temp_ptr;
        first_element->prev = NULL;
        first_element->datum = data;
        num_elements++;
    }

    return;
}

template<class T> /* Only using a template because LinkedList is a template class */
int LinkedList<T>::getSize(void) {
    return num_elements; //data type of num_elements remains the same regardless of what linked list holds
}

template<class T> /* Calls user-specified callback function on each element in the linked list */
void LinkedList<T>::makeCallBack(void) {

    if(callback_function == NULL) { //only call functions if the callback has actually been set
        std::cout << "Callback function has not been set" << std::endl;
    } else {
        //std::cout << "Function set" << std::endl;
        if(num_elements == 0) {
            std::cout << "No elements in linked list" << std::endl;
        } else if(num_elements > 0) {
            node* temp_ptr = first_element;
            while(temp_ptr != NULL) {
                callback_function(temp_ptr->datum);
                temp_ptr = temp_ptr->next;
            }
        }
    }

    return;
}

template<class T> /* Alternate method of access */
T* LinkedList<T>::atIndex(int index) {
    if(index >= num_elements || index <= 0) {
        std::cout << "Non-fatal error: index out of bounds" << std::endl;
        return 0;
    }
    //by this point, method has ended or index is valid for size of linked list
    node* temp_ptr = first_element;
    for(int i = 0; i < index; i++) {
        temp_ptr = temp_ptr->next;
    }

    return temp_ptr->datum;
}

template<class T> /* Overloading the subscript operator, returns a pointer to T */
T* LinkedList<T>::operator[](int index) {
    return atIndex(index);
}

template<class T> /* Remove an element from the end of the linked list */
void LinkedList<T>::removeEnd(void) {
    if(num_elements == 1) {
        delete first_element;
        first_element = NULL;
        last_element  = NULL;
        num_elements = 0;
    } else if(num_elements > 1) {
        node* temp_ptr = last_element->prev;
        delete last_element;
        last_element = temp_ptr;
        last_element->next = NULL;
        num_elements--;
    } else {
        std::cout << "Can't delete elements from empty LL" << std::endl;
    }
}

template<class T> /* Remove an element from the beginning of the linked list */
void LinkedList<T>::removeBegin(void) {
    if(num_elements == 1) {
        removeEnd();
    } else if(num_elements > 1) {
        node* temp_ptr = first_element->next;
        delete first_element;
        first_element = temp_ptr;
        first_element->prev = NULL;
        num_elements--;
    } else {
        std::cout << "Can't delete elements from empty LL" << std::endl;
    }
}

template<class T> /* Returns a vector of addresses of all the elements in the linked list */
std::vector<T*>* LinkedList<T>::getAddresses(void) {
    std::vector<T*>* v = new std::vector<T*>;
    if(num_elements > 0) {
        node* temp_ptr = first_element;
        while(temp_ptr != NULL) {
            v->push_back(temp_ptr->datum);
            temp_ptr = temp_ptr->next;
        }
    } else {
        return NULL;
    }
    return v;
}

#endif // LINKEDLIST_H

//beware of bugs in the above code. I have only proved it correct, not tested it
