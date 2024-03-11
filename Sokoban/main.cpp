#include <SFML/Graphics.hpp>

#include "Sokoban.hpp"

int main(void) {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Sokoban");

    Sokoban sokoban("map.txt");

    window.clear();
    //window.draw(sokoban);
    sokoban.draw(window, sf::RenderStates());
    window.display();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }


    }

    return 0;
}