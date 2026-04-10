#pragma once
#include "IStarshipCore.hpp"

template <typename T>

class Nova : public IStarShipCore{
    class Node {
        public:
            T data;
            Node* next;
    };
    
    Node* start = NULL;
    int size_ =0;

public:
    void insert(int value) override {
        Node* newNode = new Node();
        newNode->data = value;
        newNode->next = NULL;

        if (start == NULL) {
            start = newNode;

        } 
        
        else {
            Node* current = start;
            while (current->next != NULL) {
                current = current->next;
            }

            current->next = newNode;
        }

        size_++;
    }

    void remove(int value) override{
        Node* current = start;
        Node* previous = NULL;

        while(current != NULL) {
            if(current->data == value) {

                if(previous == NULL){
                    start = current->next; //FIRST ELEMENT
                }

                else {
                    previous->next = current->next;
                }

                delete current;
                size_--;
                return;
            }

            previous = current;
            current = current->next;
        }
    }


    int search(int target) override {
        Node* current = start;
        int iterations = 0;

        if(current == NULL) { //EMPTY LIST
            return -1;
        }


        while(current != NULL){
            iterations++;

            if(current->data == target){
                return iterations;
            }

            current = current->next;
        }

        return -1;
    }


    int size() const override {
        return size_;
    }

    std::string algorithmName() const override {
        return "Linear Search";
    }
};
