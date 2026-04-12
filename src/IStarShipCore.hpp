#pragma once
#include <string>

class IStarShipCore {
public:
    virtual void insert(int value) = 0;
    virtual void remove(int value) = 0;
    virtual int search(int target) = 0; // returns iterations or -1
    virtual int size() const = 0;
    virtual std::string algorithmName() const = 0;
    virtual int findMax() = 0;
    virtual ~IStarShipCore() = default;
};