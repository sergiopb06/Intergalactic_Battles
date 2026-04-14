#pragma once
#include "Army.hpp"
#include <iostream>

enum class ActionMode{
    NONE,
    DEPLOY,
    MOVE_FROM,
    MOVE_TO,
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

public:
    Game(std::string p1, std::string p2) : player1(p1), player2(p2), currentTurn(1), 
        ap(AP_PER_TURN), mode(ActionMode::NONE), selectedShipType(0), fromRow(-1), fromCol(-1){}


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
        if(currentTurn == 1){
            currentTurn = 2;
        }else{
            currentTurn = 1;
        }
    }

    bool isGameOver(){
        return player1.lostCheck() || player2.lostCheck();
    }


    std::string getWinner(){
        if(player2.lostCheck()){
            return player1.getName();
        }else if(player1.lostCheck()){
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

    void selectUpgrade(int row, int col){
        if(ap <= 0){
            return;
        }
        if(getCurrentArmy().upgrade(row , col)){
            ap--;
        }
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

        switch (mode){

        case ActionMode::DEPLOY:{
            if(getCurrentArmy().deploy(selectedShipType, row, col)){
                ap--;
                mode = ActionMode::NONE;
                return "Ship deployed";
            }
            return "Error";
            
        }
            

        case ActionMode::MOVE_FROM:{
            Starship* ship = getCurrentArmy().getShip(row,col);

            if(ship == nullptr){
                return "No ship in that cell";
            }

            fromRow = row;
            fromCol = col;
            mode = ActionMode::MOVE_TO;
            return "Now click destination cell";
        }
        
        case ActionMode::MOVE_TO:{
            if(getCurrentArmy().move(fromRow, fromCol, row, col)){
                ap--;
                mode = ActionMode::NONE;
                return "Ship moved";
            }
        }

        case ActionMode::ATTACK_FROM:{
            Starship* ship = getCurrentArmy().getShip(row,col);
        
            if(ship == nullptr){
                return "No ship there";
            }

            fromRow = row;
            fromCol = col;
            mode = ActionMode::ATTACK_TO;
            return "Now click enemy cell";
        }
        
        case ActionMode::ATTACK_TO:{
            int result = getCurrentArmy().attack(fromRow, fromCol, row, col, getEnemyArmy());

            if(result == -1){
                mode = ActionMode::ATTACK_FROM;
                return "Invalid attack";

            }

            ap--;
            mode = ActionMode::NONE;

            if(result == 0){
                return "Miss";
            }
            return "Hit!";

        }
        default:
            return "Select an action first";
        }
    }

};