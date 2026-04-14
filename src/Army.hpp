#pragma once
#include "Constants.hpp"
#include "StarShip.hpp"
#include <vector>
#include <string>

class Army {
private:
    std::string playerName;
    int credits;
    std::vector<Starship*> ships;
    Starship* grid[GRID_SIZE][GRID_SIZE];

    bool isOccupied(int row, int col){
        return grid[row][col] != NULL;
    }

 
public:
    Army(std::string name){
        this->playerName = name;
        this->credits = CREDITS_CNST;

        for(int i = 0; i < GRID_SIZE; i++){
            for(int j = 0; j < GRID_SIZE; j++){
                grid[i][j] = NULL;
            }
        }
    }

    ~Army() {
        for (Starship* ship : ships) {
            delete ship;
        }
    }

    std::string getName() const {
        return playerName;
    }

    int getCredits() const{
        return credits;
    }

    void addIncome() {
        credits += INCOME_CNST;
    }

    Starship* getShip(int row, int col) {
        if(grid[row][col] != NULL && grid[row][col]->isAlive()){
            return grid[row][col];
        }
        return NULL;
    }

    const std::vector<Starship*>& getAllShips() const {
        return ships;
    }

    bool lostCheck() {
        for(Starship* ship : ships) {
            if(ship->isAlive()){
                return false;
            }
        }

        return true;
    }



    bool deploy(int type, int row, int col){
        if(row < 0 || row >= GRID_SIZE || col < 0 || col >= GRID_SIZE){
            return false;
        }

        if(isOccupied(row, col)){
            return false;
        }

        int price = 0;
        IStarShipCore* core = NULL;

        switch (type) {
            case 1:
                core = new Nova();
                price = NOVA_PRICE;
                break;
            case 2:
                core = new Pulsar();
                price = PULSAR_PRICE;
                break;
            case 3:
                core = new Aegis();
                price = AEGIS_PRICE;
                break;
            case 4:
                core = new Quasar();
                price = QUASAR_PRICE;
                break;
            case 5:
                core = new Nebula();
                price = NEBULA_PRICE;
                break;
            case 6:
                core = new Vortix();
                price = VORTIX_PRICE;
                break;
            default:
                return false;
            }
        
        if(credits < price) {
            return false;
        }

        Starship* newShip = new Starship(core, row, col, price);
        ships.push_back(newShip);
        grid[row][col] = newShip;
        credits-=price;
        return true;
    }


    bool move(int fromR, int fromC, int toR, int toC){
        if(toR < 0 || toR >= GRID_SIZE || toC < 0 || toC >= GRID_SIZE){
            return false;
        }

        //If the cells are NOT adjacent
        if(abs(toR - fromR) > 1 || abs(toC - fromC) > 1){
            return false;
        }


        Starship* ship = getShip(fromR, fromC);
        if(ship == NULL) {
            return false;
        }

        if(isOccupied(toR, toC)){
            return false;
        }


        grid[toR][toC] = ship;
        grid[fromR][fromC] = NULL;
        ship->setRow(toR);
        ship->setCol(toC);
        return true;
    }


    bool upgrade(int row, int col){
        Starship* ship = getShip(row, col);
        if(ship == NULL){
            return false;
        }

        if(credits < UPGRADE_COST){
            return false;
        }

        credits-= UPGRADE_COST;
        ship->upgrade();
        return true;
    }


    int attack(int fromR, int fromC, int toR, int toC, Army& enemy) {
        if(toR < 0 || toR >= GRID_SIZE || toC < 0 || toC >= GRID_SIZE){
            return -1;
        }

        Starship* attacker = getShip(fromR, fromC);
        if(attacker == NULL) {
            return -1;
        }

        Starship* opponent = enemy.getShip(toR, toC);
        if(opponent == NULL){
            return 0;
        }

        int dmg = attacker->atk();
        opponent->getHit(dmg);
        return 1;
    }

};