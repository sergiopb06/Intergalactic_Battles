#pragma once 
#include "IStarShipCore.hpp"
#include "Constants.hpp"
#include "Nova.hpp"
#include "Aegis.hpp"
#include "Vortix.hpp"
//#include "Pulsar.hpp"
//#include "Quasar.hpp"
//#include "Nebula.hpp"

class Starship {
private:
    IStarShipCore* core;
    int hp;
    int row;
    int col;
    int price;

public:
    Starship(IStarShipCore* core, int row, int col, int price){
        this->core = core;
        this->hp = HP_CNST;
        this->row = row;
        this->col = col;
        this->price = price;
    }

    void upgrade() {
        int max = core->findMax();
        core->remove(max);
    }

    int atk() {
        int target = rand() % core->findMax();
        int iterations = core->search(target);
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

};