#include <iostream>
#include "Aegis.cpp"  // asegúrate de tener tu clase en este header

int main() {
    Aegis ship;

    std::cout << "=== TEST AEGIS ===" << std::endl;

    // Insertar datos
    std::cout << "\nInsertando elementos..." << std::endl;
    ship.insert(10);
    ship.insert(20);
    ship.insert(30);
    ship.insert(40);
    ship.insert(50);
    ship.insert(60);
    ship.insert(70);
    ship.insert(80);
    ship.insert(90);
    ship.insert(55);
    ship.insert(23);
    ship.insert(12);
    ship.insert(56);
    ship.insert(67);
    ship.insert(69);
    ship.insert(110);

    // Mostrar tamaño
    std::cout << "Tamano actual: " << ship.size() << std::endl;

    // Buscar elementos
    std::cout << "\nBuscando elementos..." << std::endl;

    int result;

    result = ship.search(80);
    std::cout << "Buscar 80 -> Iteraciones: " << result << std::endl;

    result = ship.search(67);
    std::cout << "Buscar 67 -> Iteraciones: " << result << std::endl;

    // Eliminar elemento
    std::cout << "\nEliminando 70..." << std::endl;
    ship.remove(70);

    // Buscar nuevamente
    result = ship.search(23);
    std::cout << "Buscar 23 despues de eliminar -> Iteraciones: " << result << std::endl;

    // Tamaño final
    std::cout << "\nTamano final: " << ship.size() << std::endl;

    // Nombre del algoritmo
    std::cout << "\nAlgoritmo: " << ship.algorithmName() << std::endl;

    return 0;
}