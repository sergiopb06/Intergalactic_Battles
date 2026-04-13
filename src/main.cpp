#include <SFML/Graphics.hpp>

// Game screens
enum class GameState{
    MENU,
    PLAYING
};

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Intergalactic Battles");
    window.setFramerateLimit(60);

    GameState state = GameState::MENU;

    //Load Font 
    sf::Font font;  
    if(!font.loadFromFile("Orbitron-VariableFont_wght.ttf")){
        return -1;
    }

    //Load background png
    sf::Texture backgroundTexture;
    if(!backgroundTexture.loadFromFile("background.jpg")){
        return -1;
    }
    sf::Sprite background(backgroundTexture);

    //Scale Image to fit window 
    background.setScale( 800.f / backgroundTexture.getSize().x , 600.f / backgroundTexture.getSize().y );

    // ***********************
    //     MENU SCREEN
    // ***********************

    //Main Title
    sf::Text title;
    title.setFont(font);
    title.setString("Intergalactic Battles");
    title.setCharacterSize(48);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(3.f);
    title.setPosition((800 - title.getLocalBounds().width) / 2, 150);


    //SubText 
    sf::Text subText;
    subText.setFont(font);
    subText.setString("Click \"GO\" to play");
    subText.setCharacterSize(24);
    subText.setFillColor(sf::Color::White);
    subText.setOutlineColor(sf::Color::Black);
    subText.setOutlineThickness(3.f);
    subText.setPosition((800 - subText.getLocalBounds().width) / 2, 280);


    // GO button 
    sf::RectangleShape button(sf::Vector2f(160,60));
    button.setFillColor(sf::Color(30,100,200));
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(2.f);
    button.setPosition((800 - 160) / 2, 380);


    // Button text
    sf::Text buttonText;
    buttonText.setFont(font);
    buttonText.setString("GO");
    buttonText.setCharacterSize(30);
    buttonText.setFillColor(sf::Color::White);
    buttonText.setOutlineColor(sf::Color::Black);
    buttonText.setOutlineThickness(2.f);

    //Center text
    buttonText.setPosition(
        button.getPosition().x + (160 - buttonText.getLocalBounds().width) / 2,
        button.getPosition().y + (50 - buttonText.getLocalBounds().height) / 2
    );

    sf::Color normalColor(30,100,200);
    sf::Color hoverColor(60,140,255);

    
    // ***********************
    //     GAME SCREEN
    // ***********************

    sf::Text gameText;
    gameText.setFont(font);
    gameText.setString("Coming Soon!");
    gameText.setCharacterSize(48);
    gameText.setFillColor(sf::Color::White);
    gameText.setOutlineColor(sf::Color::Black);
    gameText.setOutlineThickness(2.f);
    gameText.setPosition((800 - title.getLocalBounds().width) / 2, 150);

    sf::Text backText;
    backText.setFont(font);
    backText.setString("Press ESC to go back");
    backText.setCharacterSize(20);
    backText.setFillColor(sf::Color(150, 200, 255));
    backText.setOutlineColor(sf::Color::Black);
    backText.setOutlineThickness(2.f);
    backText.setPosition((800 - backText.getLocalBounds().width) / 2,320);


    // ***********************
    //     GAME LOOP
    // ***********************

while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {

            // Closed
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Menu events
            if (state == GameState::MENU) {
                if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    if (button.getGlobalBounds().contains(mousePos)) {
                        state = GameState::PLAYING;
                    }
                }
            }

            // Game events
            if (state == GameState::PLAYING) {
                if (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape) {
                    state = GameState::MENU;
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