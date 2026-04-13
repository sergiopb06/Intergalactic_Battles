#pragma once 
#include <cstdlib>
#include <ctime>
#include <vector>

#include "IStarShipCore.hpp"
#include "Constants.hpp"
#include "Nova.hpp"
#include "Aegis.hpp"
#include "Vortix.hpp"
#include "Pulsar.hpp"
#include "Quasar.hpp"
#include "Nebula.hpp"

class Starship {
private:
    IStarShipCore* core;
    int hp;
    int row;
    int col;
    int price;

    int totalSearches = 0;
    int totalIterations =0;
    double cpuTime = 0;
    std::vector<int> upgrdLog;

public:
    Starship(IStarShipCore* core, int row, int col, int price){
        this->core = core;
        this->hp = HP_CNST;
        this->row = row;
        this->col = col;
        this->price = price;

        int elements[NUM_OF_ELEMENTS];
        for (int i = 0; i < NUM_OF_ELEMENTS; i++){
            elements[i] = i;
        }


        for (int i = NUM_OF_ELEMENTS - 1; i > 0; i--){
            int j = rand() % (i + 1);
            int temp  = elements[i];
            elements[i] = elements[j];
            elements[j] = temp;
        }


        for (int i = 0; i < NUM_OF_ELEMENTS; i++){
            core->insert(elements[i]);
        }

    }

    ~Starship() {
        delete core;
    }

    void upgrade() {
        int max = core->findMax();
        core->remove(max);
        upgrdLog.push_back(core->findMax());
    }

    int atk() {
        int target = rand() % core->findMax();

        clock_t start = clock();
        int iterations = core->search(target);
        clock_t end = clock();

        totalSearches++;
        if(iterations != -1){
            totalIterations += iterations;
            cpuTime += (double)(end - start) / CLOCKS_PER_SEC;
        }

        int dmg = 0;
        if(iterations != -1){
            dmg = DAMAGE_CNST / iterations;
        }

        return dmg;
    }

    int getHP() const {
        return hp;
    }

    int getRow() const { 
        return row;
    }

    int getCol() const {
        return col;
    }

    int getPrice() const {
        return price;
    }

    void getHit(int dmg){
        hp -= dmg;
    }

    bool isAlive(){
        if(hp > 0){
            return true;
        }

        return false;
    }

    void setRow(int row) {
        this->row = row;
    }

    void setCol(int col) {
        this->col = col;
    }

    int getTotalSearches() const {
        return totalSearches;
    }

    int getTotalIterations() const {
        return totalIterations;
    }

    double getCPUTime() const {
        return cpuTime;
    }

    std::string getAlgorithm() const {
        return core->algorithmName();
    }

    const std::vector<int>& getUprdLog() const {
        return upgrdLog;
    }

};