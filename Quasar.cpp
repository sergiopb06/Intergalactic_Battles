#include <iostream>

template <typename T>

class Quasar{
    class node{
        public:
            T data; 
            node* left;
            node* right;
            int height;
    }

    node* root = NULL;

    node* searchUtility(node* current, T value){
        if(current == NULL){
            return false;
        }else if(current.data == value){
            return current;
        }else if(value < current.data){
            return searchUtility(current.left, value);
        }else{
            return searchUtility(current.right, value);
        }
    }
};