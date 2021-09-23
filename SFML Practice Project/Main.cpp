#include <SFML/Graphics.hpp>

int main()
{
    // Window Setup
    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "SFML Practice", sf::Style::Titlebar);

    // Load texture
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Assets/Graphics/Player.png");

    // Setup Sprite
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    // Load font
    sf::Font mainFont;
    mainFont.loadFromFile("Assets/Fonts/Dogica.ttf");

    // Setup Text
    sf::Text titleText;
    titleText.setFont(mainFont);
    titleText.setString("Hello world!");
    titleText.setPosition(window.getSize().x/2, window.getSize().y/2);
    titleText.setFillColor(sf::Color(255, 166, 0));
    titleText.setCharacterSize(100);
    titleText.setStyle(sf::Text::Italic | sf::Text::Underlined);

    sf::FloatRect textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.left + textRect.width/2, textRect.top + textRect.height/2);


    titleText.setString("Hello");
    textRect = titleText.getLocalBounds();
    titleText.setOrigin(textRect.left + textRect.width / 2, textRect.top + textRect.height / 2);


    while (window.isOpen())
    {
        // INPUT
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();


            // Is the event a key press event
            if (event.type == sf::Event::KeyPressed)
            {
                // Is the event specifically related to the escape key
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
        window.draw(titleText);
        window.draw(playerSprite);

        window.display();
    }

    return 0;
}