#include <SFML/Graphics.hpp>

// Game screens
enum class GameState{
    MENU,
    PLAYING
};

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Intergalactic Battles");    window.setFramerateLimit(60);

    GameState state = GameState::MENU;

    //Load Font 
    sf::Font font;  
    if (!font.openFromFile("Orbitron-VariableFont_wght.ttf")) {
        return -1;
    }

    //Load background png
    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("background.jpg")){
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    //Scale Image to fit window 
    background.setScale(sf::Vector2f(800.f / backgroundTexture.getSize().x,600.f / backgroundTexture.getSize().y));

    // ***********************
    //     MENU SCREEN
    // ***********************

    //Main Title
    sf::Text title(font, "Intergalactic Battles", 48);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(3.f);
    title.setPosition(sf::Vector2f((800 - title.getLocalBounds().size.x) / 2, 150));

    //SubText 
    sf::Text subText(font, "Click \"GO\" to play", 24);
    subText.setFillColor(sf::Color::White);
    subText.setOutlineColor(sf::Color::Black);
    subText.setOutlineThickness(3.f);
     subText.setPosition(sf::Vector2f((800 - subText.getLocalBounds().size.x) / 2, 280));


    // GO button 
    sf::RectangleShape button(sf::Vector2f(160,60));
    button.setFillColor(sf::Color(30,100,200));
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(2.f);
    button.setPosition(sf::Vector2f((800 - 160) / 2, 380));


    // Button text
    sf::Text buttonText(font, "GO", 30);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setOutlineColor(sf::Color::Black);
    buttonText.setOutlineThickness(2.f);

    //Center text
    buttonText.setPosition(sf::Vector2f(
        button.getPosition().x + (160 - buttonText.getLocalBounds().size.x) / 2,
        button.getPosition().y + (50  - buttonText.getLocalBounds().size.y) / 2
    ));

    sf::Color normalColor(30,100,200);
    sf::Color hoverColor(60,140,255);

    
    // ***********************
    //     GAME SCREEN
    // ***********************

    sf::Text gameText(font, "Coming Soon!", 48);
    gameText.setFillColor(sf::Color::White);
    gameText.setOutlineColor(sf::Color::Black);
    gameText.setOutlineThickness(2.f);
     gameText.setPosition(sf::Vector2f((800 - gameText.getLocalBounds().size.x) / 2, 150));

     sf::Text backText(font, "Press ESC to go back", 20);
    backText.setFillColor(sf::Color(150, 200, 255));
    backText.setOutlineColor(sf::Color::Black);
    backText.setOutlineThickness(2.f);
    backText.setPosition(sf::Vector2f((800 - backText.getLocalBounds().size.x) / 2, 320));

    // ***********************
    //     GAME LOOP
    // ***********************

while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {


            // Closed
             if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Menu events
            if (state == GameState::MENU) {
                if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mousePressed->button == sf::Mouse::Button::Left) {
                        sf::Vector2f mousePos(mousePressed->position);
                        if (button.getGlobalBounds().contains(mousePos)) {
                            state = GameState::PLAYING;
                        }
                    }
                }
            }

            // Game events
            if (state == GameState::PLAYING) {
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                    if (keyPressed->code == sf::Keyboard::Key::Escape) {
                        state = GameState::MENU;
                    }
                }
            }
        }

        // Hover effect (menu)
        if (state == GameState::MENU) {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            if (button.getGlobalBounds().contains(mousePos))
                button.setFillColor(hoverColor);
            else
                button.setFillColor(normalColor);
        }

    // ***********************
    //     DRAW
    // ***********************

        window.clear();
        window.draw(background);

        if (state == GameState::MENU) {
            window.draw(title);
            window.draw(subText);
            window.draw(button);
            window.draw(buttonText);
        }

        if (state == GameState::PLAYING) {
            window.draw(gameText);
            window.draw(backText);
        }

        window.display();
    }
    return 0;
}