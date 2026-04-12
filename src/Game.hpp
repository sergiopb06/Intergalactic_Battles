#pragma once
#include "Army.hpp"
#include <iostream>

class Game {
private:
    Army player1;
    Army player2;

public:
    Game(std::string p1, std::string p2) : player1(p1) ,player2(p2) {}

    void start() {
        bool finishGame = false;

        while(!finishGame) {
            play(player1, player2);
            if(player2.lostCheck()) {
                finishGame = true;
                std::cout << player1.getName() << " wins!" << std::endl;
            }

            if(!finishGame){
                play(player2, player1);
                if(player1.lostCheck()) {
                    finishGame = true;
                    std::cout << player2.getName() << " wins!" << std::endl;
                }
            }
        }
    }



    void play(Army& currentP, Army& enemy) {
        currentP.addIncome();
        int ap = AP_PER_TURN;
        int type, row, col, fromR, fromC, toR, toC ;
        while(ap > 0){
            //SHOW GRID
            //SHOW MENU

            int option;
            std::cin >> option;
            
            switch (option){
            case 1: //DEPLOY
                std::cout << "Select Ship (1-6): ";
                std::cin >> type;
                std::cout << std::endl << "Row: ";
                std::cin >> row;
                std::cout << std::endl << "Column: ";
                std::cin >> col;
                std::cout << std::endl;

                if(!currentP.deploy(type, row, col)){
                    std::cout << "Invalid deployment" << std::endl;
                    continue;
                }

                break;
            case 2: //MOVE
                std::cout << "Ship to move Row: ";
                std::cin >> fromR;
                std::cout << std::endl << "Ship to move Column:";
                std::cin >> fromC;
                std::cout << std::endl << "Target Row: ";
                std::cin >> toR;
                std::cout << std::endl << "Target Column: ";
                std::cin >> toC;
                std::cout << std::endl;

                if(!currentP.move(fromR, fromC, toR, toC)){
                    std::cout << "Invalid move" << std::endl;
                    continue;
                }

                break;

            case 3: //UPGRADE
                std::cout << "Ship to upgrade Row: ";
                std::cin >> row;
                std::cout << std::endl << "Ship to upgrade Column:";
                std::cin >> col;
                std::cout << std::endl;

                if(!currentP.upgrade(row, col)){
                    std::cout << "Invalid ship to upgrade" << std::endl;
                    continue;
                }

                break;

            case 4: {//ATK
                std::cout << "Attacking ship Row: ";
                std::cin >> fromR;
                std::cout << std::endl << "Attacking ship Column:";
                std::cin >> fromC;
                std::cout << std::endl << "Target Row: ";
                std::cin >> toR;
                std::cout << std::endl << "Target Column: ";
                std::cin >> toC;
                std::cout << std::endl;

                int atkResult = currentP.attack(fromR, fromC, toR, toC, enemy);
                if(atkResult == -1) {
                    std::cout << "Invalid attack" << std::endl;
                    continue;
                }

                else if(atkResult == 0){
                    std::cout << "Attack missed, no enemy ship located..." << std::endl;
                    break;
                }

                else{
                    std::cout << "Attack hit enemy ship at selected coordinates..." << std::endl;
                    break;
                }

            }
            default:
                std::cout << "Invalid Option" << std::endl;
                continue;
            }

            ap--;

        }
    }
};