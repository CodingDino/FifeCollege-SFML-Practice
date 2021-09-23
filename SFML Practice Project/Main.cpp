#include <SFML/Graphics.hpp>

int main()
{
    // Window Setup
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    sf::RenderWindow window(desktop, "SFML Practice", sf::Style::None);

    // Load texture
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Assets/Graphics/Player.png");

    // Setup Sprite
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);



    while (window.isOpen())
    {
        // INPUT
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }
        }


        // LOGIC / PROCESS / UPDATE



        // DRAW
        window.clear();

        // Draw everything
        window.draw(playerSprite);

        window.display();
    }

    return 0;
}