#pragma once 
#include "IStarShipCore.hpp"

template <typename T>

class Pulsar : public IStarShipCore{

    int _size;

    public: 

        int search(int target, int list[], int size){
            int left = 0; 
            int right = size - 1;

            while (left < right){
                int mid = (left + right) / 2;

                if(list[mid] == target){
                    return mid;
                }else if(target < list[mid]){
                    right = mid + 1;
                }else{
                    left = mid - 1;
                }
            }
        }

        int insert(int newElement, int list[], int size) {
            int i = 0;
            while (i < size && list[i] < newElement) i++;

            for (int j = size; j > i; j--) {
                list[j] = list[j - 1];
            }

            list[i] = newElement;
            size_++
            return size + 1;
        }

        void remove(int value) override {
        int index = search(value);
        if (index == -1) return;
        shiftLeft(index);
        size_--;
    }

    int size() comst override{
        return size_;
    }

    std::string algorithmName() const override{
        retgurn "Binary Search"
    }
};