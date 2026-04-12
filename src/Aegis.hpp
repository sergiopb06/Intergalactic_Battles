#pragma once
#include "IStarShipCore.hpp"
#include <set>
#include <string>

class Aegis : public IStarShipCore {
private:
    std::set<int> data_;

public:
    Aegis() {}
    
    void insert(int value) override {
        data_.insert(value);
    }

    void remove(int value) override {
        data_.erase(value);
    }

    int search(int target) override {
        if (data_.count(target)) {
            return 1;  // found in 1 iteration
        }
        return -1;     // not found
    }

    int size() const override {
        return static_cast<int>(data_.size());
    }

    std::string algorithmName() const override {
        return "Aegis (Set - simulated 1 iteration lookup)";
    }

    int findMax() override {
        if (data_.empty()) {
            return -1;
        }
        return *data_.rbegin();
    }
};