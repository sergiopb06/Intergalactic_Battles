#include <iostream>

template <typename T>

class Quasar{
    class Node{
        public:
            T data; 
            Node* left;
            Node* right;
            int height;
    }

    Node* root = NULL;

    Node* searchUtility(Node* current, T value){
        if(current == NULL){
            return false;
        }else if(current.data == value){
            return current;
        }else if(value < current.data){
            return searchUtility(currentleft, value);
        }else{
            return searchUtility(current.right, value);
        }
    }
};