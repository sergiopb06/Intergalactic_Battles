#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Game.hpp"

// Game screens
enum class GameState {
    MENU,
    NAMES,
    PLAYING,
    WAITING,
    GAMEOVER
};

class GUI {
private:

    std::string logMessage;
    sf::Text* logText;
    sf::Clock waitingClock; 
    bool waitingStarted;

    // Ship selector 
    bool showShipMenu;
    sf::RectangleShape shipMenuBox;
    sf::Text* shipOptions[6];

    sf::Text* turnText;
    sf::RectangleShape endTurnButton;
    sf::Text* endTurnText;

    sf::Text* waitingText;

    sf::Text* gameOverText;
    sf::Text* winnerText;
    sf::RectangleShape restartButton;
    sf::Text* restartText;


    sf::RenderWindow window;
    GameState state;


    sf::Font font;
    sf::Texture backgroundTexture;
    sf::Sprite background;


    Game* game;

    // -------------------------
    //      MENU SCREEN
    // -------------------------
    sf::Text title;
    sf::Text subText;
    sf::RectangleShape button;
    sf::Text buttonText;
    sf::Color normalColor;
    sf::Color hoverColor;

    // -------------------------
    //      NAME SCREEN
    // -------------------------
    std::string player1Name;
    std::string player2Name;
    int activePlayer;

    sf::Text setupTitle;
    sf::Text p1Label;
    sf::RectangleShape p1Box;
    sf::Text p1Text;
    sf::Text p2Label;
    sf::RectangleShape p2Box;
    sf::Text p2Text;
    sf::Text hintText;
    sf::RectangleShape startButton;
    sf::Text startText;
    sf::Color statNormal;
    sf::Color startHover;

    // -------------------------
    //      PLAYING SCREEN
    // -------------------------
    const int cols = 10;
    const int rows = 10;
    const float cellSize = 50.f;
    float gridX;
    float gridY;

    sf::Texture manzana;
    sf::RectangleShape blackScreen;
    sf::RectangleShape cell;
    sf::RectangleShape hudDivision;

    sf::RectangleShape buyBotton;
    sf::RectangleShape upgradeBotton;
    sf::RectangleShape moveBotton;
    sf::RectangleShape attackBotton;

    sf::Text buyText;
    sf::Text upgradeText;
    sf::Text moveText;
    sf::Text attackText;

    sf::RectangleShape apBox;
    sf::Text apText;
    sf::RectangleShape moneyBox;
    sf::Text moneyText;




    void initMenu() {
        title = sf::Text(font, "Intergalactic Battles", 48);
        title.setFillColor(sf::Color::White);
        title.setOutlineColor(sf::Color::Black);
        title.setOutlineThickness(3.f);
        title.setPosition(sf::Vector2f((1200 - title.getLocalBounds().size.x) / 2, 150));

        subText = sf::Text(font, "Click \"GO\" to play", 24);
        subText.setFillColor(sf::Color::White);
        subText.setOutlineColor(sf::Color::Black);
        subText.setOutlineThickness(3.f);
        subText.setPosition(sf::Vector2f((1200 - subText.getLocalBounds().size.x) / 2, 280));

        button = sf::RectangleShape(sf::Vector2f(160, 60));
        button.setFillColor(sf::Color(30, 100, 200));
        button.setOutlineColor(sf::Color::White);
        button.setOutlineThickness(2.f);
        button.setPosition(sf::Vector2f((1200 - 160) / 2, 380));

        buttonText = sf::Text(font, "GO", 30);
        buttonText.setFillColor(sf::Color::White);
        buttonText.setOutlineColor(sf::Color::Black);
        buttonText.setOutlineThickness(2.f);
        buttonText.setPosition(sf::Vector2f(button.getPosition().x + (160 - buttonText.getLocalBounds().size.x) / 2, button.getPosition().y + (50  - buttonText.getLocalBounds().size.y) / 2));

        normalColor = sf::Color(30, 100, 200);
        hoverColor  = sf::Color(60, 140, 255);
    }



    void initNames() {
        player1Name = "";
        player2Name = "";
        activePlayer = 1;

        setupTitle = sf::Text(font, "Enter player name", 36);
        setupTitle.setFillColor(sf::Color::White);
        setupTitle.setOutlineColor(sf::Color::Black);
        setupTitle.setOutlineThickness(2.f);
        setupTitle.setPosition(sf::Vector2f((1200 - setupTitle.getLocalBounds().size.x) / 2, 80));

        p1Label = sf::Text(font, "Player 1: ", 22);
        p1Label.setFillColor(sf::Color(150, 200, 255));
        p1Label.setOutlineColor(sf::Color::Black);
        p1Label.setOutlineThickness(2.f);
        p1Label.setPosition(sf::Vector2f(430, 200));

        p1Box = sf::RectangleShape(sf::Vector2f(340, 50));
        p1Box.setFillColor(sf::Color(20, 20, 60));
        p1Box.setOutlineColor(sf::Color::Yellow);
        p1Box.setOutlineThickness(2.f);
        p1Box.setPosition(sf::Vector2f(430, 235));

        p1Text = sf::Text(font, "", 22);
        p1Text.setFillColor(sf::Color::White);
        p1Text.setPosition(sf::Vector2f(442, 248));

        p2Label = sf::Text(font, "Player 2:", 22);
        p2Label.setFillColor(sf::Color(150, 200, 255));
        p2Label.setOutlineColor(sf::Color::Black);
        p2Label.setOutlineThickness(2.f);
        p2Label.setPosition(sf::Vector2f(430, 330));

        p2Box = sf::RectangleShape(sf::Vector2f(340, 50));
        p2Box.setFillColor(sf::Color(20, 20, 60));
        p2Box.setOutlineColor(sf::Color::Yellow);
        p2Box.setOutlineThickness(2.f);
        p2Box.setPosition(sf::Vector2f(430, 365));

        p2Text = sf::Text(font, "", 22);
        p2Text.setFillColor(sf::Color::White);
        p2Text.setPosition(sf::Vector2f(442, 378));

        hintText = sf::Text(font, "Click a box to select it, then type", 16);
        hintText.setFillColor(sf::Color(180, 180, 180));
        hintText.setPosition(sf::Vector2f((1200 - hintText.getLocalBounds().size.x) / 2, 440));

        startButton = sf::RectangleShape(sf::Vector2f(200, 55));
        startButton.setFillColor(sf::Color(30, 100, 200));
        startButton.setOutlineColor(sf::Color::White);
        startButton.setOutlineThickness(2.f);
        startButton.setPosition(sf::Vector2f((1200 - 200) / 2, 490));

        startText = sf::Text(font, "START", 26);
        startText.setFillColor(sf::Color::White);
        startText.setOutlineColor(sf::Color::Black);
        startText.setOutlineThickness(2.f);
        startText.setPosition(sf::Vector2f(startButton.getPosition().x + (200 - startText.getLocalBounds().size.x) / 2,startButton.getPosition().y + (55  - startText.getLocalBounds().size.y) / 2));

        statNormal  = sf::Color(30, 100, 200);
        startHover  = sf::Color(60, 140, 255);
    }



    void initPlaying() {
        gridX = 350.f + (850.f - cols * cellSize) / 2;
        gridY = (800.f - rows * cellSize) / 2;

        blackScreen = sf::RectangleShape(sf::Vector2f(cols * cellSize, 5 * cellSize));
        blackScreen.setPosition(sf::Vector2f(gridX - 1, gridY - 1));
        blackScreen.setTexture(&manzana);

        cell = sf::RectangleShape(sf::Vector2f(cellSize - 2, cellSize - 2));
        cell.setOutlineColor(sf::Color::White);
        cell.setOutlineThickness(1.f);

        hudDivision = sf::RectangleShape(sf::Vector2f(2.f, 800.f));
        hudDivision.setFillColor(sf::Color(80, 80, 80));
        hudDivision.setPosition(sf::Vector2f(350.f, 0.f));

        const float bottonX = 50.f;
        const float bottonY = 240.f;
        const float bottonH = 55.f;

        buyBotton = sf::RectangleShape(sf::Vector2f(bottonY, bottonH));
        buyBotton.setFillColor(sf::Color(30, 100, 200));
        buyBotton.setOutlineColor(sf::Color::White);
        buyBotton.setOutlineThickness(2.f);
        buyBotton.setPosition(sf::Vector2f(bottonX, 60.f));

        upgradeBotton = sf::RectangleShape(sf::Vector2f(bottonY, bottonH));
        upgradeBotton.setFillColor(sf::Color(30, 100, 200));
        upgradeBotton.setOutlineColor(sf::Color::White);
        upgradeBotton.setOutlineThickness(2.f);
        upgradeBotton.setPosition(sf::Vector2f(bottonX, 210.f));

        moveBotton = sf::RectangleShape(sf::Vector2f(bottonY, bottonH));
        moveBotton.setFillColor(sf::Color(30, 100, 200));
        moveBotton.setOutlineColor(sf::Color::White);
        moveBotton.setOutlineThickness(2.f);
        moveBotton.setPosition(sf::Vector2f(bottonX, 135.f));

        attackBotton = sf::RectangleShape(sf::Vector2f(bottonY, bottonH));
        attackBotton.setFillColor(sf::Color(180, 30, 30));
        attackBotton.setOutlineColor(sf::Color::White);
        attackBotton.setOutlineThickness(2.f);
        attackBotton.setPosition(sf::Vector2f(bottonX, 285.f));

        buyText = sf::Text(font, "BUY", 22);
        buyText.setFillColor(sf::Color::White);
        buyText.setPosition(sf::Vector2f(bottonX + (bottonY - buyText.getLocalBounds().size.x) / 2,buyBotton.getPosition().y + (bottonH - buyText.getLocalBounds().size.y) / 2));

        upgradeText = sf::Text(font, "UPGRADE", 22);
        upgradeText.setFillColor(sf::Color::White);
        upgradeText.setPosition(sf::Vector2f(bottonX + (bottonY - upgradeText.getLocalBounds().size.x) / 2,upgradeBotton.getPosition().y + (bottonH - upgradeText.getLocalBounds().size.y) / 2));

        moveText = sf::Text(font, "MOVE", 22);
        moveText.setFillColor(sf::Color::White);
        moveText.setPosition(sf::Vector2f(bottonX + (bottonY - moveText.getLocalBounds().size.x) / 2,moveBotton.getPosition().y + (bottonH - moveText.getLocalBounds().size.y) / 2));

        attackText = sf::Text(font, "ATTACK", 22);
        attackText.setFillColor(sf::Color::White);
        attackText.setPosition(sf::Vector2f(bottonX + (bottonY - attackText.getLocalBounds().size.x) / 2, attackBotton.getPosition().y + (bottonH - attackText.getLocalBounds().size.y) / 2));

        apBox = sf::RectangleShape(sf::Vector2f(bottonY, bottonH));
        apBox.setFillColor(sf::Color(20, 20, 60));
        apBox.setOutlineColor(sf::Color::Yellow);
        apBox.setOutlineThickness(2.f);
        apBox.setPosition(sf::Vector2f(bottonX, 390.f));

        apText = sf::Text(font, "AP: ", 22);
        apText.setFillColor(sf::Color::Yellow);
        apText.setPosition(sf::Vector2f(bottonX + (bottonY - apText.getLocalBounds().size.x) / 2, apBox.getPosition().y + (bottonH - apText.getLocalBounds().size.y) / 2));

        moneyBox = sf::RectangleShape(sf::Vector2f(bottonY, bottonH));
        moneyBox.setFillColor(sf::Color(20, 20, 60));
        moneyBox.setOutlineColor(sf::Color::Yellow);
        moneyBox.setOutlineThickness(2.f);
        moneyBox.setPosition(sf::Vector2f(bottonX, 465.f));

        moneyText = sf::Text(font, "$: ", 22);
        moneyText.setFillColor(sf::Color(100, 255, 100));
        moneyText.setPosition(sf::Vector2f(bottonX + (bottonY - moneyText.getLocalBounds().size.x) / 2, moneyBox.getPosition().y + (bottonH - moneyText.getLocalBounds().size.y) / 2));

        logMessage = "Select an action";
        logText = new sf::Text(font, logMessage, 18);
        logText->setFillColor(sf::Color(255,255,150));
        logText->setPosition(sf::Vector2f(10.f, 560.f));

        turnText = new sf::Text(font, "", 20);
        turnText->setFillColor(sf::Color::White);
        turnText->setOutlineColor(sf::Color::Black);
        turnText->setOutlineThickness(2.f);
        turnText->setPosition(sf::Vector2f(10.f, 630.f));

        endTurnButton = sf::RectangleShape(sf::Vector2f(240.f , 55.f));
        endTurnButton.setFillColor(sf::Color(80, 160, 80));
        endTurnButton.setOutlineColor(sf::Color::White);
        endTurnButton.setOutlineThickness(2.f);
        endTurnButton.setPosition(sf::Vector2f(50.f, 700.f));

        endTurnText = new sf::Text(font, "END TURN", 22);
        endTurnText->setFillColor(sf::Color::White);
        endTurnText->setOutlineColor(sf::Color::Black);
        endTurnText->setOutlineThickness(2.f);
        endTurnText->setPosition(sf::Vector2f(
        endTurnButton.getPosition().x + (240 - endTurnText->getLocalBounds().size.x) / 2,
        endTurnButton.getPosition().y + (55  - endTurnText->getLocalBounds().size.y) / 2));
     

        showShipMenu = false;
        shipMenuBox = sf::RectangleShape(sf::Vector2f(240.f, 220.f));
        shipMenuBox.setFillColor(sf::Color(20, 20, 60));
        shipMenuBox.setOutlineColor(sf::Color::White);
        shipMenuBox.setOutlineThickness(2.f);
        shipMenuBox.setPosition(sf::Vector2f(50.f, 60.f));

        std::string shipNames[6] = {"1. Nova (200)", "2. Pulsar (375)", "3. Aegis (400)","4. Quasar (400)", "5. Nebula (225)", "6. Vortix (280)"};

        for (int i = 0; i < 6; i++) {
            shipOptions[i] = new sf::Text(font, shipNames[i], 15);
            shipOptions[i]->setFillColor(sf::Color::White);
            shipOptions[i]->setPosition(sf::Vector2f(60.f, 70.f + i * 32.f));
        }


        waitingStarted = false;
        waitingText = new sf::Text(font, "", 36);
        waitingText->setFillColor(sf::Color::White);
        waitingText->setOutlineColor(sf::Color::Black);
        waitingText->setOutlineThickness(3.f);

        gameOverText = new sf::Text(font, "GAME OVER", 64);
        gameOverText->setFillColor(sf::Color::White);
        gameOverText->setOutlineColor(sf::Color::Black);
        gameOverText->setOutlineThickness(3.f);
        gameOverText->setPosition(sf::Vector2f(
            (1200 - gameOverText->getLocalBounds().size.x) / 2, 200));

        winnerText = new sf::Text(font, "", 36);
        winnerText->setFillColor(sf::Color(255, 215, 0));
        winnerText->setOutlineColor(sf::Color::Black);
        winnerText->setOutlineThickness(2.f);

        restartButton = sf::RectangleShape(sf::Vector2f(260.f, 60.f));
        restartButton.setFillColor(sf::Color(30, 100, 200));
        restartButton.setOutlineColor(sf::Color::White);
        restartButton.setOutlineThickness(2.f);
        restartButton.setPosition(sf::Vector2f((1200 - 260) / 2, 480.f));

        restartText = new sf::Text(font, "PLAY AGAIN", 26);
        restartText->setFillColor(sf::Color::White);
        restartText->setOutlineColor(sf::Color::Black);
        restartText->setOutlineThickness(2.f);
        restartText->setPosition(sf::Vector2f(
            restartButton.getPosition().x + (260 - restartText->getLocalBounds().size.x) / 2,
            restartButton.getPosition().y + (60  - restartText->getLocalBounds().size.y) / 2));
        
    }




    void menuEvent(const sf::Event& event) {
        if (const auto* mousePressed = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos(mousePressed->position);
                if (button.getGlobalBounds().contains(mousePos)) {
                    state = GameState::NAMES;
                }
            }
        }
    }


    void namesEvent(const sf::Event& event) {
        if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePress->button == sf::Mouse::Button::Left) {
                sf::Vector2f mousePos(mousePress->position.x, mousePress->position.y);
                if (p1Box.getGlobalBounds().contains(mousePos)) {
                    activePlayer = 1;
                } else if (p2Box.getGlobalBounds().contains(mousePos)) {
                    activePlayer = 2;
                }

                if (startButton.getGlobalBounds().contains(mousePos)) {
                    if (!player1Name.empty() && !player2Name.empty()) {
                        game = new Game(player1Name, player2Name);
                        state = GameState::PLAYING;
                    }
                }
            }
        }

        if (const auto* textEntered = event.getIf<sf::Event::TextEntered>()) {
            uint32_t ch = textEntered->unicode;

            if (ch == 8) {
                if (activePlayer == 1 && !player1Name.empty())
                    player1Name.pop_back();

                else if (activePlayer == 2 && !player2Name.empty())
                    player2Name.pop_back();
            } 
            
            else if (ch == 9) {
                activePlayer = (activePlayer == 1) ? 2 : 1;
            } 
            
            else if (ch >= 32 && ch < 128) {
                if (activePlayer == 1 && player1Name.size() < 15)
                    player1Name += static_cast<char>(ch);

                else if (activePlayer == 2 && player2Name.size() < 15)
                    player2Name += static_cast<char>(ch);
            }

            p1Text.setString(player1Name);
            p2Text.setString(player2Name);
        }

        if (const auto* keyPress = event.getIf<sf::Event::KeyPressed>()) {
            if (keyPress->code == sf::Keyboard::Key::Escape) {
                state = GameState::MENU;
            }
        }
    }




    void updateHover() {
        sf::Vector2f mousePos = sf::Vector2f(sf::Mouse::getPosition(window));

        if (state == GameState::MENU) {
            button.setFillColor(button.getGlobalBounds().contains(mousePos) ? hoverColor : normalColor);
        }

        if (state == GameState::NAMES) {
            p1Box.setOutlineColor(activePlayer == 1 ? sf::Color::Yellow : sf::Color::White);
            p2Box.setOutlineColor(activePlayer == 2 ? sf::Color::Yellow : sf::Color::White);
            startButton.setFillColor(startButton.getGlobalBounds().contains(mousePos) ? startHover : statNormal);
        }

        if (state == GameState::PLAYING) {
            sf::Color buyNormal(30, 100, 200);
            sf::Color buyHover(60, 140, 255);
            sf::Color attackNormal(180, 30, 30);
            sf::Color attackHover(220, 60, 60);

            buyBotton.setFillColor(buyBotton.getGlobalBounds().contains(mousePos)     ? buyHover    : buyNormal);
            moveBotton.setFillColor(moveBotton.getGlobalBounds().contains(mousePos)   ? buyHover    : buyNormal);
            upgradeBotton.setFillColor(upgradeBotton.getGlobalBounds().contains(mousePos) ? buyHover : buyNormal);
            attackBotton.setFillColor(attackBotton.getGlobalBounds().contains(mousePos) ? attackHover : attackNormal);
        }
    }


    // -------------------------
    //      DRAW
    // -------------------------

    void drawMenu() {
        window.draw(title);
        window.draw(subText);
        window.draw(button);
        window.draw(buttonText);
    }

    void drawNames() {
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

    void drawPlaying() {
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

        window.draw(buyBotton);     
        window.draw(buyText);
        window.draw(moveBotton);    
        window.draw(moveText);
        window.draw(upgradeBotton); 
        window.draw(upgradeText);
        window.draw(attackBotton);  
        window.draw(attackText);

        window.draw(apBox);         
        window.draw(apText);
        window.draw(moneyBox);      
        window.draw(moneyText);
    }

    void playingEvent(const sf::Event& event){
        if(const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>()){
            if (mousePress->button == sf::Mouse::Button::Left){
                sf::Vector2f mousePos(mousePress->position.x, mousePress->position.y);

                if(buyBotton.getGlobalBounds().contains(mousePos)){
                    showShipMenu = !showShipMenu;
                    game->cancelAction();
                    logMessage = "Select ship type";
                }

                if(moveBotton.getGlobalBounds().contains(mousePos)){
                    showShipMenu = false;
                    game->selectedMove();
                    logMessage = "Click ship to move";
                }

                if(attackBotton.getGlobalBounds().contains(mousePos)){
                    showShipMenu = false;
                    game->selectAttack();
                    logMessage = "Click attacking ship";
                }

                if(showShipMenu){
                    for(int i = 0; i < 6; i++){
                        if(shipOptions[i]->getGlobalBounds().contains(mousePos)){
                            game->selectDeploy(i+1);
                            showShipMenu = false;
                            logMessage = "Click cell to deploy";
                        }
                    }
                }

                if(endTurnButton.getGlobalBounds().contains(mousePos)){
                    game->cancelAction();
                    showShipMenu = false;

                    if(game->isGameOver()){
                        winnerText->setString(game->getWinner() + " wins!");
                        winnerText->setPosition(sf::Vector2f((1200 - winnerText->getLocalBounds().size.x) / 2, 350.f));
                        state = GameState::GAMEOVER;
                        return;
                    }

                    std::string nextPlayer;
                    if(game->getCurrentTurn() == 1){
                        nextPlayer = player2Name;
                    }else{
                        nextPlayer = player1Name;
                    }

                    waitingText->setString("Get ready " + nextPlayer + "...");
                    waitingText->setPosition(sf::Vector2f((1200 - waitingText->getLocalBounds().size.x) / 2, 350.f));
                    waitingClock.restart();
                    waitingStarted = true;
                    state = GameState::WAITING;

                    game->endTurn();
                    game->startTurn();

                }

                float gx = gridX;
                float gy = gridY;
                float gs = cellSize;

                if(mousePos.x >= gx && mousePos.x <= gx + cols * gs && mousePos.y >= gy && mousePos.y <= gy + rows * gs){
                    int clickedCol = (int)((mousePos.x -gx) / gs);
                    int clickedRow = (int)((mousePos.y -gy) / gs);

                    if(game->getMode() == ActionMode::NONE && upgradeBotton.getGlobalBounds().contains(mousePos)){
                        
                    }

                    logMessage = game->gridClick(clickedRow, clickedCol);

                    if(game->isGameOver()){
                        winnerText->setString(game->getWinner() + " wins!");
                        winnerText->setPosition(sf::Vector2f((1200 - winnerText->getLocalBounds().size.x) / 2,350.f));
                        state = GameState::GAMEOVER;
                    }
                }
            }
        }

        if(const auto* keyPress = event.getIf<sf::Event::KeyPressed>()){
            if(keyPress->code == sf::Keyboard::Key::Escape){
                game->cancelAction();
                showShipMenu = false;
                logMessage = "Cancelled";
            }
        }
    }

    void gameOverEvent(const sf::Event& event){

        if (const auto* mousePress = event.getIf<sf::Event::MouseButtonPressed>()) {

            if (mousePress->button == sf::Mouse::Button::Left) {

                sf::Vector2f mousePos(mousePress->position.x, mousePress->position.y);

                if (restartButton.getGlobalBounds().contains(mousePos)) {

                    delete game;
                    game = nullptr;
                    player1Name = "";
                    player2Name = "";
                    state = GameState::MENU;

                }
            }
        }
    }


    void drawPlaying(){
        Army& current = game->getCurrentArmy();
        Army& enemy = game->getEnemyArmy();

        for(int row = 0; row < rows; row++){
            for(int col = 0; col < cols; col++){
                
                float x = gridX + (col * cellSize);
                float y = grudY + (row * cellSize);
                cell.setPosition(sf::Vector2f(x,y));

                Starship* ship = current.getShip(row,col);
                if(ship!= nullptr){
                    cell.setFillColor(sf::Color::Green);
                }else if (row < 5 ){
                    cell.setFillColor(sf::Color(15, 15, 40));
                }else{
                    cell.setFillColor(sf::Color::Cyan);
                }

                window.draw(cell);
            }
        }
        window.draw(hudDivision);

        if (showShipMenu) {
            
            window.draw(shipMenuBox);
            for (int i = 0; i < 6; i++){
                window.draw(shipOptions[i]);
            }
                
        } else {
            window.draw(buyBotton);     window.draw(buyText);
            window.draw(moveBotton);    window.draw(moveText);
            window.draw(upgradeBotton); window.draw(upgradeText);
            window.draw(attackBotton);  window.draw(attackText);
        }


        apText.setString("AP: " + std::to_string(game->getAP()));
        moneyText.setString("$: " + std::to_string(current.getCredits()));
        turnText->setString("Turn: " + current.getName());

        window.draw(apBox);      
        window.draw(apText);

        window.draw(moneyBox);   
        window.draw(moneyText);

        window.draw(endTurnButton); 
        window.draw(endTurnText);
        window.draw(turnText);

        logText->setString(logMessage);
        window.draw(logText);
    }
public:

    GUI() :
        window(sf::VideoMode({1200, 800}), "Intergalactic Battles"),
        state(GameState::MENU),
        background(sf::Sprite(backgroundTexture)),
        game(nullptr),
        title(font, "", 0),
        subText(font, "", 0),
        buttonText(font, "", 0),
        setupTitle(font, "", 0),
        p1Label(font, "", 0),
        p1Text(font, "", 0),
        p2Label(font, "", 0),
        p2Text(font, "", 0),
        hintText(font, "", 0),
        startText(font, "", 0),
        buyText(font, "", 0),
        upgradeText(font, "", 0),
        moveText(font, "", 0),
        attackText(font, "", 0),
        apText(font, "", 0),
        moneyText(font, "", 0),
        normalColor(30, 100, 200),
        hoverColor(60, 140, 255),
        activePlayer(1),
        gridX(0), gridY(0),
        cols(10), rows(10), cellSize(50.f),
        cell(sf::Vector2f(0,0)),
        statNormal(30,100,200),
        startHover(60,140,255)
    {
        window.setFramerateLimit(60);

        if (!font.openFromFile("Orbitron-VariableFont_wght.ttf")) {
            return;
        }

        if (!backgroundTexture.loadFromFile("background.jpg")) {
            return;
        }


        background = sf::Sprite(backgroundTexture);
        background.setScale(sf::Vector2f(1200.f / backgroundTexture.getSize().x, 800.f  / backgroundTexture.getSize().y));

        if (!manzana.loadFromFile("manzana.jpg")) {
            return;
        }

        initMenu();
        initNames();
        initPlaying();
    }

    ~GUI() {
        delete game;
    }

    void run() {
        while (window.isOpen()) {
            while (const std::optional<sf::Event> event = window.pollEvent()) {

                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                if (state == GameState::MENU)  
                    menuEvent(*event);


                if (state == GameState::NAMES) 
                    namesEvent(*event);

                if(state == GameState::PLAYING){
                    playingEvent(*event);
                }

                if(state == GameState::GAMEOVER){
                    gameOverEvent(*event);
                }   
            }

            if (state == GameState::WAITING && waitingStarted) {
                if (waitingClock.getElapsedTime().asSeconds() >= 3.f) {

                    waitingStarted = false;
                    logMessage = "Select an action";
                    state = GameState::PLAYING;

                }
            }

            updateHover();

            window.clear();
            window.draw(background);

            if (state == GameState::MENU)
                drawMenu();

            if (state == GameState::NAMES)   
                drawNames();

            if (state == GameState::PLAYING) 
                drawPlaying();

            // if (state == GameState::WAITING){
            //     drawWatiging();
            // }
            // if (state== GameState::GAMEOVER){
            //     drawGameOer();
            // }

            window.display();
        }
    }
};