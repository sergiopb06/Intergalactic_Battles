#pragma once 
#include "IStarShipCore.hpp"
#include <vector>
#include <stdexcept>

class Pulsar : public IStarShipCore{

   std::vector<int> list_;
   int size_ = 0;

    public:

        int search(int target){
            return search(target, list_, size_);
        }   

        void insert(int target){
            insert(target, list_, size_);
        }

        void remove(int target){
            remove(target, list_, size_);
        }

        int findMax(){
            return findMax(list_);
        }
        
    private: 

        int search(int target, const std::vector<int>& list, int size){
            int left = 0; 
            int right = size - 1;
            int iterations = 0;

            while (left <= right){
                int mid = (left + right) / 2;
                iterations++;
                if(list[mid] == target){
                    return iterations;
                }else if(target < list[mid]){
                    right = mid - 1;
                }else{
                    left = mid + 1;
                }
            }
            return -1;
        }

        int insert(int newElement, std::vector<int>& list, int size) {
            int i = 0;
            while (i < size && list[i] < newElement) i++;

            list.push_back(0);
            for (int j = size; j > i; j--) {
                list[j] = list[j - 1];
            }

            list[i] = newElement;
            size_++;
            return size + 1;
        }

        void remove(int target, std::vector<int>& list, int size) {
            if (size_ == 0){ 
                return;
            }

            int left = 0;
            int right = size - 1;
            int index = -1;

            while (left <= right) {
                int mid = (left + right) / 2;
                if (list[mid] == target) {
                    index = mid;
                    break;
                } else if (target < list[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }

            if (index == -1){
                return;
            } 

            list.erase(list.begin() + index);
            size_--;
         }

        int findMax(const std::vector<int>& list){
            if(size_ == 0){
                throw std::runtime_error("Cannot findMax on empty list");
            }
            return list[size_ - 1];
        }    

        int size() const override{
            return size_;
        }

        std::string algorithmName() const override{
            return "Binary Search";
        }
};