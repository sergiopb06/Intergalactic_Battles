#pragma once
#include <string>

class IStarShipCore {
    public:
        virtual void insert(int value) = 0;
        virtual void remove(int value) = 0;
        virtual int search(int target) = 0; //Returns the # of iterations needed to find target, returns -1 if target doesn't exist.
        virtual int size() const = 0;
        virtual std::string algorithmName() const = 0;
};