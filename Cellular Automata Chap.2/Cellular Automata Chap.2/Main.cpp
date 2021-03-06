#include <SFML/Graphics.hpp>
#include <iostream>
#include <thread>
#include "GridCell.h"
#include "Render.h"
#include "Tick.h"


int main()
{
    static const int size{ 60 };
    static const int resolution{ size * 10 };

    sf::RenderWindow window(sf::VideoMode(resolution, resolution), "Cellular Automata", sf::Style::Titlebar | sf::Style::Close);

    //window.setFramerateLimit(1);
    
    GridCell grid(CellType::Empty);   
    
    Render render(&window);  

    sf::Clock test;


    while (window.isOpen()) {

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) grid.ModifyCell(sf::Mouse::getPosition(window) / 10, CellType::Water);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle)) grid.ModifyCell(sf::Mouse::getPosition(window) / 10, CellType::Empty);
        if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) grid.ModifyCell(sf::Mouse::getPosition(window) / 10, CellType::Solid);

        if (test.getElapsedTime().asMilliseconds() >= 50) {
            grid.ProcessCell();
            test.restart();
        }
           
      
        render.GridToShape(grid.cellsBuffer[grid.buffer]);
        render.Draw();
        window.display();
        window.clear();
    }

    return EXIT_SUCCESS;
}

