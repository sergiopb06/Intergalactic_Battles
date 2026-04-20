#pragma once
#include "Army.hpp"
#include <iostream>

enum class ActionMode{
    NONE,
    DEPLOY,
    MOVE_FROM,
    MOVE_TO,
    UPGRADE,
    ATTACK_FROM,
    ATTACK_TO
};


class Game {
private:
    Army player1;
    Army player2;
    int currentTurn;
    int ap;
    ActionMode mode;
    int selectedShipType;
    int fromRow, fromCol;
    bool gameStarted;

public:
    Game(std::string p1, std::string p2) :
            player1(p1), player2(p2), currentTurn(1),
            ap(AP_PER_TURN), mode(ActionMode::NONE),
            selectedShipType(0), fromRow(-1), fromCol(-1),
            gameStarted(false) {}

    // -------Getters---------

    Army& getCurrentArmy(){
        if(currentTurn == 1){
            return player1;
        }else{
            return player2;
        }
    }

    Army& getEnemyArmy(){
        if(currentTurn == 1){
            return player2;
        }else{
            return player1;
        }
    }

    int getCurrentTurn() const {
        return currentTurn;
    }

    int getAP() const{
        return ap;
    }

    ActionMode getMode() const{
        return mode;
    }

    int getSelectedShipType() const{
        return selectedShipType;
    }


    // Turns----------------------

    void startTurn(){
        getCurrentArmy().addIncome();
        ap = AP_PER_TURN;
        mode = ActionMode::NONE;
        fromRow = fromCol = -1;
    }

    void endTurn(){
        gameStarted = true;
        if(currentTurn == 1){
            currentTurn = 2;
        }else{
            currentTurn = 1;
        }
    }

    bool isGameOver(){
        if(!gameStarted) {
            return false;
        }
        return player1.lostCheck() || player2.lostCheck();
    }


    std::string getWinner(){
        if(player2.lostCheck()){
            return player1.getName();
        }
        if(player1.lostCheck()){
            return player2.getName();
        }
        return "";
    }


    // ----Action mode selection 

    void selectDeploy(int shipType){
        mode = ActionMode::DEPLOY;
        selectedShipType = shipType;
    }

    void selectedMove(){
        mode = ActionMode::MOVE_FROM;
        fromRow = fromCol = -1;
    }

    void selectAttack(){
        mode = ActionMode::ATTACK_FROM;
        fromRow = fromCol = -1;
    }

    void selectUpgrade(){
        mode = ActionMode::UPGRADE;
        fromRow = fromCol = -1;
    }

    void cancelAction(){
        mode = ActionMode::NONE;
        fromRow = fromCol = -1;
    }

    //Handel grid clicks 
    std::string gridClick(int row, int col){

        if(ap <= 0){
            return "No AP left!";
        }

        bool isEnemyZone;

        if (currentTurn == 1) {
            isEnemyZone = (row < 5);
        } else {
            isEnemyZone = (row >= 5);
        }

        switch (mode){

        case ActionMode::DEPLOY:{
            if (isEnemyZone)
                return "Can't deploy in enemy zone!";
            if (getCurrentArmy().deploy(selectedShipType, row, col)) {
                ap--;
                mode = ActionMode::NONE;
                return "Ship deployed";
            }
            return "Can't deploy there";   
        }
            

        case ActionMode::MOVE_FROM:{
            if (isEnemyZone) return "Select one of your ships";
            Starship* ship = getCurrentArmy().getShip(row, col);
            if(ship == nullptr){
                return "No ship in that cell";
            }
            fromRow = row;
            fromCol = col;
            mode = ActionMode::MOVE_TO;
            return "Now click destination cell";
        }
        
        case ActionMode::MOVE_TO:{
            if (isEnemyZone) { mode = ActionMode::NONE; return "Can't move into enemy zone"; }
            if(getCurrentArmy().move(fromRow, fromCol, row, col)){
                ap--;
                mode = ActionMode::NONE;
                return "Ship moved";
            }
            mode = ActionMode::NONE;
            return "Can't move there";
        }

        case ActionMode::UPGRADE:{
            if (isEnemyZone) { mode = ActionMode::NONE; return "Can't upgrade enemy ships"; }
            if (getCurrentArmy().upgrade(row, col)) {
                ap--;
                mode = ActionMode::NONE;
                return "Ship upgraded!";
            }
            mode = ActionMode::NONE;
            return "Can't upgrade";
        }

        case ActionMode::ATTACK_FROM:{
            if (isEnemyZone) return "Select one of your ships to attack with";
            Starship* ship = getCurrentArmy().getShip(row, col);
            if (!ship) return "No ship there";
            fromRow = row;
            fromCol = col;
            mode = ActionMode::ATTACK_TO;
            return "Now click enemy cell";
        }
        
        case ActionMode::ATTACK_TO:{
            if (!isEnemyZone) {
                mode = ActionMode::ATTACK_FROM;
                return "Click a cell in the enemy zone";
            }
            int result = getCurrentArmy().attack(fromRow, fromCol, row, col, getEnemyArmy());
            if (result == -1) { mode = ActionMode::ATTACK_FROM; return "Invalid attack"; }
            ap--;
            mode = ActionMode::NONE;
            if (result == 0) return "Miss";
            return "Hit!";

        }

        default:
            return "Select an action first";
        }
        
    }

};