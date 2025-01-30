#pragma once

#include "Singleton.h"
#include "MainMenu.h"
#


class MenuManager : public Singleton<MenuManager>
{
private:
    string Name;
    Font font;
    Text titleText;
    Text playText;
    Text quitText;

public:
    MenuManager();
    ~MenuManager();

    void Launch(RenderWindow& window);
    void QuitMenu();
    void DrawMainMenu(RenderWindow& window);
    void HandleEvents(RenderWindow& window);
};


