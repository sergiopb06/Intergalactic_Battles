#include <iostream>
class Pulsar{

    int binarySearch(int target, int list[], int size){
        int left = 0;
        int right = size - 1;

        while(left <= right){
            int mid = (left + right) / 2;
            if(list[mid] == target){
                return mid;
            }else if(target < mid){
                right = mid + 1;
            }else{
                left = mid - 1;
            }
        }
        return -1;
    }
};