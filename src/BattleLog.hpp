#pragma once
#include "Army.hpp"
#include <fstream>
#include <iostream>

class BatteLog {
private:
    static void write(std::ofstream& file, Army& army) {
        file << "Commander: " << army.getName() << "\n";
        file << "=====================================\n";

        for(Starship* ship : army.getAllShips()) {
            file << "Ship at (" << ship->getRow() << "," << ship->getCol() << ")\n:";
            file << "Algorithm: " << ship->getAlgorithm() << "\n";
            file << "Total Searches: " << ship->getTotalSearches() << "\n";
            file << "Total Iterations: " << ship->getTotalIterations() << "\n";
            file << "Total Searches: " << ship->getCPUTime() << "\n";

            file << "Upgrade History (max extracted): ";
            if(ship->getUprdLog().empty()) {
                file << "no upgrades";
            } else {
                for(int n : ship->getUprdLog()) {
                    file << n << " ";
                }
            }

            file << "\n=====================================\n";

        }

        file << "\n\n";
    }

public:
    static void writeFile(Army& player1, Army& player2) {
        std::ofstream file("battleLog.txt");
        if(!file.is_open()) {
            std::cout << "Error opening file" << std::endl;
            return;
        }

        file << "=====================================\n";
        file << "   INTERGALACTIC BATTLES BATTLE LOG  \n";
        file << "=====================================\n";


        write(file, player1);
        write(file, player2);

        file.close();

    }
};