#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
    sf::Vector2f playerPosition = sf::Vector2f(0.0f, 0.0f);

    // Velocity / Speed
    sf::Vector2f playerVelocity = sf::Vector2f(0.0f, 0.0f);
    float speed = 100.0f;
    float accelerationRate = 1000.0f;
    float drag = 0.01f; // percentage of velocity to remove each frame
    sf::Vector2f playerAcceleration = sf::Vector2f(0.0f, 0.0f);

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

    // Load SoundBuffer from file
    sf::SoundBuffer jumpSoundBuffer;
    jumpSoundBuffer.loadFromFile("Assets/Audio/Jump.wav");

    // Play sound using Sound type
    sf::Sound jumpSound;
    jumpSound.setBuffer(jumpSoundBuffer);
    //jumpSound.play();

    // Load and play music
    sf::Music gameMusic;
    gameMusic.openFromFile("Assets/Audio/Music.ogg");
    //gameMusic.play();

    // Game clock
    sf::Clock gameClock;

    while (window.isOpen())
    {
        sf::Time gameTime = gameClock.restart();
        float deltaTime = gameTime.asSeconds();

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

        playerAcceleration.x = 0.0f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            // left key is pressed: move our character
            playerAcceleration.x = -accelerationRate;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // left key is pressed: move our character
            playerAcceleration.x = accelerationRate;
        }

        // LOGIC / PROCESS / UPDATE
        sf::Vector2f deltaVelocity = playerAcceleration * deltaTime;
        playerVelocity = playerVelocity + deltaVelocity;

        // Change in velocity due to drag
        playerVelocity.x = playerVelocity.x - playerVelocity.x * drag;

        sf::Vector2f deltaPosition = playerVelocity * deltaTime;
        playerPosition = playerPosition + deltaPosition;

        playerSprite.setPosition(playerPosition);


        // DRAW
        window.clear();

        // Draw everything
        //window.draw(titleText);
        window.draw(playerSprite);

        window.display();
    }

    return 0;
}