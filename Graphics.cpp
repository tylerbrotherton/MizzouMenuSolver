// main.cpp
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

static std::vector<std::string> Plaza900;//resteraunt 1
static std::vector<std::string> MarkTwain;//resteraunt 2
static std::vector<std::string> GreekTown;//resteraunt 3

void setDisplay(int resteraunt, std::vector<std::string> inVector){
    if(resteraunt==1){
        Plaza900.clear();
        for(auto i:inVector){
             Plaza900.push_back(i);
        }    
    }
    else if(resteraunt==2){
        MarkTwain.clear();
        for(auto i: inVector){
            MarkTwain.push_back(i);
        }
    }
    else if(resteraunt==3){
        GreekTown.clear();
        for(auto i: inVector0){
            GreekTown.push_back(i);
        }
    }

}

void displayGraphics() {
    // -------------------------------------------------
    // Window setup
    // -------------------------------------------------
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Menu");
    window.setFramerateLimit(60);

    // -------------------------------------------------
    // Font (load any .ttf you have, e.g., OpenSans)
    // -------------------------------------------------
    sf::Font font;
    if (!font.loadFromFile("Courrier_New.ttf")) {
        return EXIT_FAILURE; // font not found
    }

    // -------------------------------------------------
    // Menu items
    // -------------------------------------------------
    std::vector<std::string> items = {"________", "Options", "Quit"};
    std::vector<sf::Text> texts;
    const float startY = 250.f;
    const float spacing = 50.f;

    for (size_t i = 0; i < items.size(); ++i) {
        sf::Text txt;
        txt.setFont(font);
        txt.setString(items[i]);
        txt.setCharacterSize(36);
        txt.setFillColor(sf::Color::White);
        // Center horizontally
        sf::FloatRect bounds = txt.getLocalBounds();
        txt.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
        txt.setPosition(400.f, startY + i * spacing);
        texts.push_back(txt);
    }

    // -------------------------------------------------
    // Selection handling
    // -------------------------------------------------
    int selected = 0;
    texts[selected].setFillColor(sf::Color::Yellow);

    // -------------------------------------------------
    // Main loop
    // -------------------------------------------------
    while (window.isOpen()) {
        sf::Event ev;
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed)
                window.close();

            // Keyboard navigation
            if (ev.type == sf::Event::KeyPressed) {
                if (ev.key.code == sf::Keyboard::Up) {
                    texts[selected].setFillColor(sf::Color::White);
                    selected = (selected - 1 + items.size()) % items.size();
                    texts[selected].setFillColor(sf::Color::Yellow);
                }
                if (ev.key.code == sf::Keyboard::Down) {
                    texts[selected].setFillColor(sf::Color::White);
                    selected = (selected + 1) % items.size();
                    texts[selected].setFillColor(sf::Color::Yellow);
                }
                if (ev.key.code == sf::Keyboard::Enter) {
                    // Simple actions for demo
                    if (items[selected] == "________")   { /* start game */ }
                    if (items[selected] == "Options") { /* show options */ }
                    if (items[selected] == "Quit")   { window.close(); }
                }
            }
        }

        // -------------------------------------------------
        // Rendering
        // -------------------------------------------------
        window.clear(sf::Color::Black);
        for (const auto& txt : plaza900)
            window.draw(txt);
        window.display();
    }
}
