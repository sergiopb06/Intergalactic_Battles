#pragma once 
#include "IStarShipCore.hpp"

template <typename T>

class Quasar : public IStarShipCore{
    class Node{ 
        public:
            T data: 
            Node* left;
            Node* right;
            int height;
    };

    Node* root = NULL;
    int size_ = 0;

public:
    int maxUltity(Node* current){  //find the max value of a subtree 
        if(current->right == NULL){
            return current->data;
        }else{
            return maxUltity(current->right);
        }
    }

    int height(Node* current){ 
        if(current == NULL){
            return 0;
        }
        return current->height;
    }

    Node* rightRotation(Node* current){
        Node* newNode = current->left;
        current->left = newNode->right;
        newNode->right = current;
        current->height = 1 + std::max(height(current->left) , height(current->right));
        newNode->height = 1 + std::max(height(newNode->left), height(newNode->right));
        return newNode;
    }
    Node* leftRotation(Node* current){
        Node* newNode = current->right;
        current->right = newNode->left;
        newNode->left = current;
        current->height = 1 + std::max(height(current->left), height(current->right));
        newNode->height = 1 + std::max(height(newNode->left), height(newNode->right));
        return newNode;
    }

    void inOrderUtility(Node* current){ 
        if(current == NULL){
            return;
        }
        inOrderUtility(current->left);
        std::cout << current->data << " ";
        inOrderUtility(current->right);
    }   

    Node* insert(Node* current, T value){
        if(current == NULL){

            Node* newNode = new Node;
            newNode->data = value;
            newNode->right = NULL;
            newNode->left = NULL;
            newNode->height = 1;
            current = newNode;
            size_++;
            return newNode;

        }

        if(value < current->data){
            current->left = insertUtility(current->left, value);
        }
        else if(value > current->data){
            current->right = insertUtility(current->right, value);
        }

        current->height = 1 + std::max(height(current->left) - height(current->right));
        int balance = height(current->left) - height(current->right);
        
        if(balance > 1){
            if(value > current->left.data){
                current->left = leftRotation(current->left);
                return rightRotation(current);
            }else{
                return leftRotation(current);
            }
        }
        else if(balance < -1){
            if(value < current->right.data){
                current->right = rightRotation(current->right);
                return leftRotation(current);
            }else{
                return leftRotation(current);
            }
        }
        siez_++;
        return current;
    }

    Node remove(Node* current, T value){
        if(current == NULL){
            std::cout << "Tree is empty" << std::endl;
            return NULL;
        }
        if(value < current->data){
            current->left = removeUtility(current->left, value);
        }else if(value > current->data){ 
            current->right = removeUtility(current->right, value);
        }
        else{ 
            if(current->left == NULL && current->right == NULL){
                delete current;
                current = NULL;
            }else if(current->left != NULL && current->right != NULL){
                int max = maxUltity(current->left);
                current->data = max;
                removeUtility(current->left, max);
            } else { 
                Node* child = current;
                if(current->right != NULL){
                    current = current->right;
                }else{
                    current = current->left;
                    child->left = NULL;
                    child->right = NULL;
                    delete child;
                    child = NULL;
                }
            }
        }

        if(current == NULL){
            return NULL;
        }
        current->height = 1 + std::max(height(current->left), height(current->right));
        int balance = height(current->left) - height(current->right);
        if(balance > 1){
            if(height(current->left) >= height(current->right)){
                return rightRotation(current);
            }else{
                current->left = leftRotation(current->left);
                return rightRotation(current);
            }
        } else if(balance < -1 ){
            if (height(current->right) >= height(current->left)){
                return leftRotation(current);
            }else{
                current->right = rightRotation(current->right);
                return leftRotation(current);
            }
        }
        size_--;
        return current;
    }

    int search(Node* current, T value, int& iterations) {

    if (current == NULL) {
        return nullptr;
    }

    iterations++;

    if (current->data == value){
        return iterations;
    } 
    if (value < current->data){
        return search(current->left, value);
    }else{ 
        return search(current->right, value);
        }
    }


    int size() const override{
        return size_;
    } 

    std::string algorithmName() const override{
        return "Tree AVL"
    }
};