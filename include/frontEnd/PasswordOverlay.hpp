#include <SFML/Graphics.hpp>
#include <string>

class PasswordOverlay {
private:
    std::string correctPassword = "godmode123"; // Changez ce mot de passe
    std::string inputPassword;
    sf::RenderWindow _window;
    sf::Font font;
    bool authenticated;
    
public:
    PasswordOverlay() : authenticated(false) {
        // Chargez votre police ici si nécessaire
        // font.loadFromFile("arial.ttf");
    }
    
    void setPassword(const std::string& password) {
        correctPassword = password;
    }
    
    bool openAndCheck() {
        _window.create(sf::VideoMode(500, 300), 
                      "Authentification God Mode",
                      sf::Style::Titlebar | sf::Style::Close);
        
        inputPassword = "";
        authenticated = false;
        bool showError = false;
        
        // Créer les textes
        sf::Text titleText;
        sf::Text promptText;
        sf::Text inputText;
        sf::Text errorText;
        sf::Text instructionText;
        
        if (font.getInfo().family.empty()) {
            if (!font.loadFromFile("arial.ttf")) {
                // Si échec, essayer d'autres chemins communs
                font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf");
            }
        }
        
        // Titre
        titleText.setFont(font);
        titleText.setString("GOD MODE");
        titleText.setCharacterSize(28);
        titleText.setFillColor(sf::Color(255, 215, 0)); // Or
        titleText.setStyle(sf::Text::Bold);
        sf::FloatRect titleBounds = titleText.getLocalBounds();
        titleText.setPosition((500 - titleBounds.width) / 2, 30);
        
        // Prompt
        promptText.setFont(font);
        promptText.setString("Entrez le mot de passe:");
        promptText.setCharacterSize(20);
        promptText.setFillColor(sf::Color::White);
        sf::FloatRect promptBounds = promptText.getLocalBounds();
        promptText.setPosition((500 - promptBounds.width) / 2, 100);
        
        // Input (avec fond)
        inputText.setFont(font);
        inputText.setCharacterSize(22);
        inputText.setFillColor(sf::Color::Green);
        inputText.setStyle(sf::Text::Bold);
        
        // Message d'erreur
        errorText.setFont(font);
        errorText.setString("Mot de passe incorrect!");
        errorText.setCharacterSize(16);
        errorText.setFillColor(sf::Color::Red);
        sf::FloatRect errorBounds = errorText.getLocalBounds();
        errorText.setPosition((500 - errorBounds.width) / 2, 190);
        
        // Instructions
        instructionText.setFont(font);
        instructionText.setString("ENTREE pour valider | ESC pour annuler");
        instructionText.setCharacterSize(14);
        instructionText.setFillColor(sf::Color(150, 150, 150));
        sf::FloatRect instrBounds = instructionText.getLocalBounds();
        instructionText.setPosition((500 - instrBounds.width) / 2, 250);
        
        // Rectangle pour l'input
        sf::RectangleShape inputBox(sf::Vector2f(300, 40));
        inputBox.setPosition(100, 140);
        inputBox.setFillColor(sf::Color(40, 40, 40));
        inputBox.setOutlineColor(sf::Color(100, 255, 100));
        inputBox.setOutlineThickness(2);
        
        while (_window.isOpen()) {
            sf::Event event;
            while (_window.pollEvent(event)) {
                switch (event.type) {
                    case sf::Event::Closed:
                        _window.close();
                        return false;
                        
                    case sf::Event::KeyPressed:
                        if (event.key.code == sf::Keyboard::Escape) {
                            _window.close();
                            return false;
                        }
                        else if (event.key.code == sf::Keyboard::Return) {
                            // Vérifier le mot de passe
                            if (inputPassword == correctPassword) {
                                authenticated = true;
                                _window.close();
                                return true;
                            }
                            else {
                                showError = true;
                                inputPassword = "";
                            }
                        }
                        else if (event.key.code == sf::Keyboard::BackSpace) {
                            if (!inputPassword.empty()) {
                                inputPassword.pop_back();
                                showError = false;
                            }
                        }
                        break;
                        
                    case sf::Event::TextEntered:
                        if (event.text.unicode < 128 && 
                            event.text.unicode != 13 && 
                            event.text.unicode != 8 &&
                            event.text.unicode >= 32) {
                            inputPassword += static_cast<char>(event.text.unicode);
                            showError = false;
                        }
                        break;
                        
                    default:
                        break;
                }
            }
            
            // Afficher les astérisques au lieu du mot de passe
            std::string displayPassword(inputPassword.length(), '*');
            inputText.setString(displayPassword);
            sf::FloatRect inputBounds = inputText.getLocalBounds();
            inputText.setPosition((500 - inputBounds.width) / 2, 148);
            
            // Rendu
            _window.clear(sf::Color(30, 30, 30));
            
            _window.draw(titleText);
            _window.draw(promptText);
            _window.draw(inputBox);
            _window.draw(inputText);
            _window.draw(instructionText);
            
            if (showError) {
                _window.draw(errorText);
            }
            
            _window.display();
        }
        
        return authenticated;
    }
};
