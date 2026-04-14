#include <SFML/Graphics.hpp>

// Game screens
enum class GameState{
    MENU,
    NAMES,
    PLAYING,
};

int main() {
    sf::RenderWindow window(sf::VideoMode({1200, 800}), "Intergalactic Battles");    window.setFramerateLimit(60);

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
    background.setScale(sf::Vector2f(1200.f / backgroundTexture.getSize().x,800.f / backgroundTexture.getSize().y));

    // ***********************
    //     MENU SCREEN
    // ***********************

    //Main Title
    sf::Text title(font, "Intergalactic Battles", 48);
    title.setFillColor(sf::Color::White);
    title.setOutlineColor(sf::Color::Black);
    title.setOutlineThickness(3.f);
    title.setPosition(sf::Vector2f((1200 - title.getLocalBounds().size.x) / 2, 150));

    //SubText 
    sf::Text subText(font, "Click \"GO\" to play", 24);
    subText.setFillColor(sf::Color::White);
    subText.setOutlineColor(sf::Color::Black);
    subText.setOutlineThickness(3.f);
     subText.setPosition(sf::Vector2f((1200 - subText.getLocalBounds().size.x) / 2, 280));


    // GO button 
    sf::RectangleShape button(sf::Vector2f(160,60));
    button.setFillColor(sf::Color(30,100,200));
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(2.f);
    button.setPosition(sf::Vector2f((1200 - 160) / 2, 380));


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
    //     NAME SCREEN
    // ***********************

    std::string player1Name = "";
    std::string player2Name = "";
    int activePlayer = 1;

    sf::Text setupTitle(font, "Enter player name", 36);
    setupTitle.setFillColor(sf::Color::White);
    setupTitle.setOutlineColor(sf::Color::Black);
    setupTitle.setOutlineThickness(2.f);
    setupTitle.setPosition(sf::Vector2f((1200 - setupTitle.getLocalBounds().size.x) / 2, 80));


    //Player 1 -------------------------
    sf::Text p1Label(font, "Player 1: ", 22);
    p1Label.setFillColor(sf::Color(150,200,255));
    p1Label.setOutlineColor(sf::Color::Black);
    p1Label.setOutlineThickness(2.f);
    p1Label.setPosition(sf::Vector2f(430,200));

    sf::RectangleShape p1Box(sf::Vector2f(340, 50));
    p1Box.setFillColor(sf::Color(20,20,60));
    p1Box.setOutlineColor(sf::Color::Yellow);
    p1Box.setOutlineThickness(2.f);
    p1Box.setPosition(sf::Vector2f(430,235));

    sf::Text p1Text(font, "", 22);
    p1Text.setFillColor(sf::Color::White);
    p1Text.setPosition(sf::Vector2f(442,248));

    //Player 2 ---------------------
    sf::Text p2Label(font, "Player 2:", 22);
    p2Label.setFillColor(sf::Color(150, 200, 255));
    p2Label.setOutlineColor(sf::Color::Black);
    p2Label.setOutlineThickness(2.f);
    p2Label.setPosition(sf::Vector2f(430, 330));

    sf::RectangleShape p2Box(sf::Vector2f(340, 50));
    p2Box.setFillColor(sf::Color(20, 20, 60));
    p2Box.setOutlineColor(sf::Color::Yellow);
    p2Box.setOutlineThickness(2.f);
    p2Box.setPosition(sf::Vector2f(430, 365));

    sf::Text p2Text(font, "", 22);
    p2Text.setFillColor(sf::Color::White);
    p2Text.setPosition(sf::Vector2f(442, 378));

    sf::Text hintText(font, "Click a box to select it, then type", 16);
    hintText.setFillColor(sf::Color(180,180,180));
    hintText.setPosition(sf::Vector2f((1200 - hintText.getLocalBounds().size.x) /2 ,440));

    // START 

    sf::RectangleShape startButton(sf::Vector2f(200,55));
    startButton.setFillColor(sf::Color(30,100,200));
    startButton.setOutlineColor(sf::Color::White);
    startButton.setOutlineThickness(2.f);
    startButton.setPosition(sf::Vector2f((1200-200)/2, 490));

    sf::Text startText(font, "START", 26);
    startText.setFillColor(sf::Color::White);
    startText.setOutlineColor(sf::Color::Black);
    startText.setOutlineThickness(2.f);
    startText.setPosition(sf::Vector2f(startButton.getPosition().x + (200 - startText.getLocalBounds().size.x) / 2,
        startButton.getPosition().y + (55 - startText.getLocalBounds().size.y) / 2));

    sf::Color statNormal(30,100,200);
    sf::Color startHover(60,140,255);

    // ***********************
    //     PLAYING SCREEN
    // ***********************

    //Dimensions
    const int cols = 10;
    const int rows = 10;
    const float cellSize = 50.f;
    const float gridX = 350.f + (850.f - cols * cellSize) / 2;
    const float gridY = (800.f - rows * cellSize) / 2;

    sf::Texture manzana;
    if (!manzana.loadFromFile("manzana.jpg")) {
        return -1;
    }

    //Radar Interference (Black Screen)
    sf::RectangleShape blackScreen(sf::Vector2f(cols * cellSize, 5 * cellSize));
    blackScreen.setPosition(sf::Vector2f(gridX - 1, gridY - 1));
    blackScreen.setTexture(&manzana);

    sf::RectangleShape cell(sf::Vector2f(cellSize - 2, cellSize - 2));
    cell.setOutlineColor(sf::Color::White);
    cell.setOutlineThickness(1.f);

    sf::RectangleShape hudDivision(sf::Vector2f(2.f, 800.f));
    hudDivision.setFillColor(sf::Color(80, 80, 80));
    hudDivision.setPosition(sf::Vector2f(350.f, 0.f));

    const float bottonX = 50.f;
    const float bottonY = 240.f;
    const float bottonH = 55.f;

    sf::RectangleShape buyBotton(sf::Vector2f(bottonY, bottonH));
    buyBotton.setFillColor(sf::Color(30, 100, 200));
    buyBotton.setOutlineColor(sf::Color::White);
    buyBotton.setOutlineThickness(2.f);
    buyBotton.setPosition(sf::Vector2f(bottonX, 60.f));

    sf::RectangleShape upgradeBotton(sf::Vector2f(bottonY, bottonH));
    upgradeBotton.setFillColor(sf::Color(30, 100, 200));
    upgradeBotton.setOutlineColor(sf::Color::White);
    upgradeBotton.setOutlineThickness(2.f);
    upgradeBotton.setPosition(sf::Vector2f(bottonX, 210.f));

    sf::RectangleShape moveBotton(sf::Vector2f(bottonY, bottonH));
    moveBotton.setFillColor(sf::Color(30, 100, 200));
    moveBotton.setOutlineColor(sf::Color::White);
    moveBotton.setOutlineThickness(2.f);
    moveBotton.setPosition(sf::Vector2f(bottonX, 135.f));

    sf::RectangleShape attackBotton(sf::Vector2f(bottonY, bottonH));
    attackBotton.setFillColor(sf::Color(180, 30, 30));
    attackBotton.setOutlineColor(sf::Color::White);
    attackBotton.setOutlineThickness(2.f);
    attackBotton.setPosition(sf::Vector2f(bottonX, 285.f));

    sf::Text buyText(font, "BUY", 22);
    buyText.setFillColor(sf::Color::White);
    buyText.setPosition(sf::Vector2f(bottonX + (bottonY - buyText.getLocalBounds().size.x) / 2,
        buyBotton.getPosition().y + (bottonH - buyText.getLocalBounds().size.y) / 2));

    sf::Text upgradeText(font, "UPGRADE", 22);
    upgradeText.setFillColor(sf::Color::White);
    upgradeText.setPosition(sf::Vector2f(bottonX + (bottonY - upgradeText.getLocalBounds().size.x) / 2,
        upgradeBotton.getPosition().y + (bottonH - upgradeText.getLocalBounds().size.y) / 2));

    sf::Text moveText(font, "MOVE", 22);
    moveText.setFillColor(sf::Color::White);
    moveText.setPosition(sf::Vector2f(bottonX + (bottonY - moveText.getLocalBounds().size.x) / 2,
        moveBotton.getPosition().y + (bottonH - moveText.getLocalBounds().size.y) / 2));

    sf::Text attackText(font, "ATTACK", 22);
    attackText.setFillColor(sf::Color::White);
    attackText.setPosition(sf::Vector2f(bottonX + (bottonY - attackText.getLocalBounds().size.x) / 2,
        attackBotton.getPosition().y + (bottonH - attackText.getLocalBounds().size.y) / 2));
    
    sf::RectangleShape apBox(sf::Vector2f(bottonY, bottonH));
    apBox.setFillColor(sf::Color(20, 20, 60));
    apBox.setOutlineColor(sf::Color::Yellow);
    apBox.setOutlineThickness(2.f);
    apBox.setPosition(sf::Vector2f(bottonX, 390.f));

    sf::Text apText(font, "AP: 3", 22);
    apText.setFillColor(sf::Color::Yellow);
    apText.setPosition(sf::Vector2f(bottonX + (bottonY - apText.getLocalBounds().size.x) / 2,
        apBox.getPosition().y + (bottonH - apText.getLocalBounds().size.y) / 2));

    sf::RectangleShape moneyBox(sf::Vector2f(bottonY, bottonH));
    moneyBox.setFillColor(sf::Color(20, 20, 60));
    moneyBox.setOutlineColor(sf::Color::Yellow);
    moneyBox.setOutlineThickness(2.f);
    moneyBox.setPosition(sf::Vector2f(bottonX, 465.f));

    sf::Text moneyText(font, "$: 1500", 22);
    moneyText.setFillColor(sf::Color(100, 255, 100));
    moneyText.setPosition(sf::Vector2f(bottonX + (bottonY - moneyText.getLocalBounds().size.x) / 2,
        moneyBox.getPosition().y + (bottonH - moneyText.getLocalBounds().size.y) / 2));
    

    // ***********************
    //     GAME LOOP
    // ***********************

while (window.isOpen()) {
        while (const std::optional<sf::Event> event = window.pollEvent()) {


            // Closed
             if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            // Menu 
            if (state == GameState::MENU) {
                if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mousePressed->button == sf::Mouse::Button::Left) {
                        sf::Vector2f mousePos(mousePressed->position);
                        if (button.getGlobalBounds().contains(mousePos)) {
                            state = GameState::NAMES;
                        }
                    }
                }
            }

            // Names
            if (state == GameState::NAMES) {
                
                if(const auto* mousePress = event->getIf<sf::Event::MouseButtonPressed>()){
                    if(mousePress->button == sf::Mouse::Button::Left){
                        sf::Vector2f mousePos(mousePress->position.x, mousePress->position.y);
                        if(p1Box.getGlobalBounds(). contains(mousePos)){
                            activePlayer = 1;
                        }else if(p2Box.getGlobalBounds(). contains(mousePos)){
                            activePlayer = 2;
                        }

                        if(startButton.getGlobalBounds().contains(mousePos)){
                            if(!player1Name.empty() && !player2Name.empty()){
                                state = GameState::PLAYING;
                            }
                        }
                    }
                }

                if(const auto* textEntered = event->getIf<sf::Event::TextEntered>()){
                    uint32_t ch = textEntered->unicode;

                    if (ch == 8) {
                        if (activePlayer == 1 && !player1Name.empty())
                            player1Name.pop_back();
                        else if (activePlayer == 2 && !player2Name.empty())
                            player2Name.pop_back();
                    } else if (ch == 9) {
                        activePlayer = (activePlayer == 1) ? 2 : 1;
                    } else if (ch >= 32 && ch < 128) {
                        if (activePlayer == 1 && player1Name.size() < 15)
                            player1Name += static_cast<char>(ch);
                        else if (activePlayer == 2 && player2Name.size() < 15)
                            player2Name += static_cast<char>(ch);
                    }

                    p1Text.setString(player1Name);
                    p2Text.setString(player2Name);
                }

                if(const auto* keyPress = event->getIf<sf::Event::KeyPressed>()){
                    if(keyPress->code == sf::Keyboard::Key::Escape){
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

        if (state == GameState::NAMES) {
            sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));
            if (startButton.getGlobalBounds().contains(mousePos))
                startButton.setFillColor(hoverColor);
            else
                startButton.setFillColor(normalColor);
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

        if (state == GameState::NAMES) {
            window.draw(setupTitle);
            window.draw(p1Label);
            window.draw(p1Box);
            window.draw(p1Text);
            window.draw(p2Label);
            window.draw(p2Box);
            window.draw(p2Text);
            window.draw(hintText);
            window.draw(startButton);
            window.draw(startText);
        }

        if (state == GameState::PLAYING) {
            for (int row = 0; row < rows; row++) {
                for (int col = 0; col < cols; col++) {
                    float x = gridX + col * cellSize;
                    float y = gridY + row * cellSize;
                    cell.setPosition(sf::Vector2f(x, y));
                    if (row < 5)
                        cell.setFillColor(sf::Color(15, 15, 40));
                    else
                        cell.setFillColor(sf::Color(30, 100, 200));
                    window.draw(cell);
                }
            }
            window.draw(blackScreen);
            window.draw(hudDivision);

            window.draw(buyBotton);    window.draw(buyText);
            window.draw(moveBotton);   window.draw(moveText);
            window.draw(upgradeBotton);window.draw(upgradeText);
            window.draw(attackBotton); window.draw(attackText);

            window.draw(apBox);     window.draw(apText);
            window.draw(moneyBox);  window.draw(moneyText);
        }
        window.display();
    }
    return 0;
}