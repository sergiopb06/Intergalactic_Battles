#pragma once
#include "IStarShipCore.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>
#include <string>

class Nebula : public IStarShipCore {
private:
    std::vector<int> heap_; 

    int parent(int i) { 
        return (i - 1) / 2;
    }
    int leftChild(int i) {
        return 2 * i + 1;
    }
    int rightChild(int i) {
        return 2 * i + 2;
    }

    bool hasParent(int i) {
        return i > 0;
    }
    bool hasLeft(int i) {
        return leftChild(i) < (int)heap_.size();
    }
    bool hasRight(int i) {
        return rightChild(i) < (int)heap_.size();
    }

    void heapifyUp(int i) {
        while (hasParent(i) && heap_[i] < heap_[parent(i)]) {
            std::swap(heap_[i], heap_[parent(i)]);
            i = parent(i);
        }
    }

    void heapifyDown(int i) {
        while (hasLeft(i)) {
            int smallest = leftChild(i);

            if (hasRight(i) && heap_[rightChild(i)] < heap_[smallest]) {
                smallest = rightChild(i);
            }

            if (heap_[i] <= heap_[smallest]) break;

            std::swap(heap_[i], heap_[smallest]);
            i = smallest;
        }
    }

public:

    void insert(int value) override {
        heap_.push_back(value);
        heapifyUp((int)heap_.size() - 1);
    }

    void remove(int value) override {
 
        int idx = -1;
        for (int i = 0; i < (int)heap_.size(); ++i) {
            if (heap_[i] == value) { idx = i; break; }
        }
        if (idx == -1) return;

        heap_[idx] = heap_.back();
        heap_.pop_back();

        if (idx < (int)heap_.size()) {
            heapifyUp(idx);
            heapifyDown(idx);
        }
    }

    int search(int target) override {
        int iterations = 0;

        for (int i = 0; i < (int)heap_.size(); ++i) {
            ++iterations;
            if (heap_[i] == target) return iterations; // found it
        }

        return -1; // not found
    }

    int findMax() override {
        if (heap_.empty()) throw std::runtime_error("Heap is empty");
        return *std::max_element(heap_.begin(), heap_.end());
    }

    int size() const override {
        return (int)heap_.size();
    }

    std::string algorithmName() const override {
        return "Nebula (MinHeap - linear arbitrary search)";
    }

};