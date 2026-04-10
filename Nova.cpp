#include <iostream>

template <typename T>
class Nova{
    class Node{
        T data;
        node* next;
    };

    node* start = NULL;

    node* linearSearch(int target){
        node* current = start; 
        int i = 0;
        if(current == NULL){
            return -1;
        }
        while (current != NULL){
            if(current.data == target){
                return i; 
            }
            current = current.next;
            i++;
        }
        return -1;
    }
};
