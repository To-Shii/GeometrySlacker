#include "MenuManager.h"
#include "MainMenu.h"
#include "TextObject.h"


MenuManager::MenuManager() {

    if (!font.openFromFile("Arial.ttf")) {
        
        cerr << "Erreur lors du chargement de la police!" << endl;
    }

    titleText.setFont(font);
    titleText.setString("Bienvenue sur le Jeu !");
    titleText.setCharacterSize(50);
    titleText.setFillColor(Color::White);
    titleText.setPosition(Vector2f(200.f, 100.f));

    
    playText.setFont(font);
    playText.setString("Jouer");
    playText.setCharacterSize(30);
    playText.setFillColor(Color::White);
    playText.setPosition(Vector2f(300.f, 250.f));

    quitText.setFont(font);
    quitText.setString("Quitter");
    quitText.setCharacterSize(30);
    quitText.setFillColor(Color::White);
    quitText.setPosition(Vector2f(300.f, 300.f));
}


MenuManager::~MenuManager() {}

void MenuManager::Launch(RenderWindow& window) {
    while (window.isOpen()) {
        HandleEvents(window);
        window.clear(Color::Black);

        DrawMainMenu(window);

        window.display();
    }
}

void MenuManager::QuitMenu() {
    cout << "Au revoir !" << endl;
    exit(0);  
}

void MenuManager::DrawMainMenu(RenderWindow& window) {
    window.draw(titleText);
    window.draw(playText);
    window.draw(quitText);
}

void MenuManager::HandleEvents(RenderWindow& _window) {
   
   
    while (const std::optional _event = _window.pollEvent())
    {
        if (_event->is<Event::Closed>())
        {
            _window.close();
        }

        else if (const Event::MouseButtonPressed* _key = _event->getIf<Event::MouseButtonPressed>())
        {
            if (playText.getGlobalBounds().contains(_window.mapPixelToCoords(Mouse::getPosition(_window)))) {
                cout << "Lancement du jeu..." << endl;
                // Par exemple : Jeu::LancerJeu(window);
            }
            else if (quitText.getGlobalBounds().contains(_window.mapPixelToCoords(Mouse::getPosition(_window)))) {
                QuitMenu();
            }
        }
    }
}
