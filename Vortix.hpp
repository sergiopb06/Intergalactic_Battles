#pragma once
#include "IStarshipCore.hpp"

template <typename T>
class Vortix : public IStarShipCore{
    class Node {
        public:
            T data;
            Node* left;
            Node* right;

    };
    
private:
    Node* root = NULL;
    int size_ =0;

    Node* getMin(Node* current){
        while(current->left != NULL){
            current = current->left;
        }
        return current;
    }


    Node* removeRecursive(Node* current, int value){
        
        if(current == NULL){
            return NULL;
        }

        if(value < current->data){ //LEFT
            current->left = removeRecursive(current->left, value);
        }

        else if(value > current->data){ //RIGHT
            current->right = removeRecursive(current->right, value);
        }

        else{ // if (value == current->data)

            //Node with no children
            if(current->left == NULL && current->right == NULL){
                delete current;
                size_--;
                return NULL;
            }

            //Node with only right child 
            else if(current->left == NULL){
                Node* temp = current->right;
                delete current;
                size_--;
                return temp;
            }

            //Node with only left child 
            else if(current->right == NULL) {
                Node* temp = current->left;
                delete current;
                size_--;
                return temp;
            }

            //Node with two children
            else {
                //Find smallest # on right side of current node. This will become the newParent node.
                Node* newParent = getMin(current->right);
                current->data = newParent->data;
                current->right = removeRecursive(current->right, newParent->data); //Removes the newParent node value.
            }
        }

        return current;
    }


public:

    void insert(int value) override {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->left = NULL;
        newNode->right = NULL;

        if(root == NULL){
            root = newNode;
            size_++;
            return;
        }

        Node* current = root;
        while (true){
            //INSERT LEFT
            if(value < current->data) {
                if(current->left == NULL){
                    current->left == newNode;
                    size_++;
                    return;
                }
                current = current->left;
            }


            //INSERT RIGHT
            else if(value > current->data) {
                if(current->right == NULL) {
                    current->right = newNode;
                    size_++;
                    return;
                }
                current = current->left;
            }


            //Value already exist, exit.
            else {
                return;
            }
        }
    }

    
    void remove(int value) override {
        root = removeRecursive(root, value);
    }


    int search(int target) override {
        Node* current = root;
        int iterations = 0;

        while(current != NULL){
            iterations++;

            if(current->data == target) {
                return iterations;
            }

            //LEFT
            else if(target < current->data){
                current = current->left;
            }

            //RIGHT
            else {
                current = current->right;
            }
        }

        return -1; //Not found
    }


    int size() const override {
        return size_;
    }


    std::string algorithmName() const override{
        return "BST (UNBALANCED)";
    }


    int findMax() override {
        if(root == NULL){
            return -1;
        }

        Node* current = root;
        while(current->right != NULL){
            current = current->right;
        }

        return current->data;
    }
};