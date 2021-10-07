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
    sf::Vector2f playerPositionPrev = playerPosition;

    // Setup Sprite
    sf::Sprite enemySprite;
    enemySprite.setTexture(playerTexture);
    enemySprite.setColor(sf::Color::Red);
    sf::Vector2f enemyPosition = sf::Vector2f(50.0f, 500.0f);
    sf::Vector2f enemyPositionPrev = enemyPosition;
    enemySprite.setPosition(enemyPosition);

    sf::Vector2f spriteSize;
    spriteSize.x = playerTexture.getSize().x;
    spriteSize.y = playerTexture.getSize().y;

    // Bounding circles
    float playerCircleRadius = playerTexture.getSize().x / 2;
    sf::Vector2f playerCircleCentre = playerPosition + 0.5f * spriteSize;
    sf::CircleShape playerCircle;
    playerCircle.setRadius(playerCircleRadius);
    playerCircle.setPosition(playerPosition);
    playerCircle.setFillColor(sf::Color::Green);


    float enemyCircleRadius = playerTexture.getSize().x / 2;
    sf::Vector2f enemyCircleCentre = enemyPosition + 0.5f * spriteSize;
    sf::CircleShape enemyCircle;
    enemyCircle.setRadius(enemyCircleRadius);
    enemyCircle.setPosition(enemyPosition);
    enemyCircle.setFillColor(sf::Color::Green);

    // Bounding Boxes
    sf::Vector2f playerBoundsOffset(3,0);
    sf::Vector2f playerBoundsScale(0.75f, 1);

    sf::Vector2f enemyBoundsOffset(-7, -7);
    sf::Vector2f enemyBoundsScale(1.5f, 1.5f);

    // Visual part of bounding boxes
    // No need to set these up as they are updated each frame
    sf::RectangleShape playerAABBDisplay;
    sf::RectangleShape enemyAABBDisplay;

    // Velocity / Speed
    sf::Vector2f playerVelocity = sf::Vector2f(0.0f, 0.0f);
    float speed = 500.0f;
    float accelerationRate = 2000.0f;
    float drag = 0.01f; // percentage of velocity to remove each frame
    float jumpSpeed = 100.0f;
    float gravity = 500.0f;
    sf::Vector2f playerAcceleration = sf::Vector2f(0.0f, 0.0f);
    playerAcceleration.y = gravity;

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            // jump!
            playerVelocity.y = -jumpSpeed;
        }

        // LOGIC / PROCESS / UPDATE
        sf::Vector2f deltaVelocity = playerAcceleration * deltaTime;
        playerVelocity = playerVelocity + deltaVelocity;

        // Change in velocity due to drag
        playerVelocity.x = playerVelocity.x - playerVelocity.x * drag;

        // Before changing position, record previous position
        playerPositionPrev = playerPosition;
        sf::Vector2f deltaPosition = playerVelocity * deltaTime;
        playerPosition = playerPosition + deltaPosition;

        playerSprite.setPosition(playerPosition);

        // Update collision geometry
        playerCircleCentre = playerPosition + 0.5f * spriteSize;

        // Get current position and size from sprites
        sf::FloatRect playerAABB = playerSprite.getGlobalBounds();
        sf::FloatRect enemyAABB = enemySprite.getGlobalBounds();

        // Update this geometry using our custom offsets and scales
        playerAABB.left += playerBoundsOffset.x;
        playerAABB.top += playerBoundsOffset.y;
        playerAABB.width *= playerBoundsScale.x;
        playerAABB.height *= playerBoundsScale.y;

        enemyAABB.left += enemyBoundsOffset.x;
        enemyAABB.top += enemyBoundsOffset.y;
        enemyAABB.width *= enemyBoundsScale.x;
        enemyAABB.height *= enemyBoundsScale.y;

        // Update collision visuals
        playerCircle.setPosition(playerPosition);

        playerAABBDisplay.setPosition(playerAABB.left, playerAABB.top);
        enemyAABBDisplay.setPosition(enemyAABB.left, enemyAABB.top);

        playerAABBDisplay.setSize(sf::Vector2f(playerAABB.width, playerAABB.height));
        enemyAABBDisplay.setSize(sf::Vector2f(enemyAABB.width, enemyAABB.height));

        // Check for collision
        //sf::Vector2f circleDisplacement = playerCircleCentre - enemyCircleCentre;
        //float squareDistance =    circleDisplacement.x * circleDisplacement.x
        //                        + circleDisplacement.y * circleDisplacement.y;
        //
        //float squareRadii = (playerCircleRadius + enemyCircleRadius) * (playerCircleRadius + enemyCircleRadius);
        //bool colliding = squareDistance < squareRadii;
        bool colliding = playerAABB.intersects(enemyAABB);

        if (colliding)
        {
            sf::Color fillcolor = sf::Color::Red;
            fillcolor.a = 125;

            playerCircle.setFillColor(fillcolor);
            enemyCircle.setFillColor(fillcolor);

            playerAABBDisplay.setFillColor(fillcolor);
            enemyAABBDisplay.setFillColor(fillcolor);

            // Collision Depth
            sf::Vector2f AWidthHeight = sf::Vector2f(playerAABB.width, playerAABB.height);
            sf::Vector2f BWidthHeight = sf::Vector2f(enemyAABB.width, enemyAABB.height);

            sf::Vector2f ACentre = sf::Vector2f(playerAABB.left, playerAABB.top); 
            ACentre += 0.5f * AWidthHeight;
            sf::Vector2f BCentre = sf::Vector2f(enemyAABB.left, enemyAABB.top);
            BCentre += 0.5f * BWidthHeight;

            sf::Vector2f distance = BCentre - ACentre;
            sf::Vector2f minDistance = 0.5f * AWidthHeight + 0.5f * BWidthHeight;
            if (distance.x < 0)
                minDistance.x = -minDistance.x;
            if (distance.y < 0)
                minDistance.y = -minDistance.y;

            sf::Vector2f depth = minDistance - distance;
            sf::Vector2f absDepth = sf::Vector2f(abs(depth.x), abs(depth.y));

            if (absDepth.x < absDepth.y)
            {
                // Move along x direction
                playerPosition.x -= depth.x;

                // Stop movement in x direction
                playerVelocity.x = 0;
            }
            else
            {
                // Move along y direction
                playerPosition.y -= depth.y;

                // Stop movement in y direction
                playerVelocity.y = 0;
            }
            playerSprite.setPosition(playerPosition);
        }
        else
        {
            sf::Color fillcolor = sf::Color::Green;
            fillcolor.a = 125;

            playerCircle.setFillColor(fillcolor);
            enemyCircle.setFillColor(fillcolor);

            playerAABBDisplay.setFillColor(fillcolor);
            enemyAABBDisplay.setFillColor(fillcolor);
        }


        // DRAW
        window.clear();

        // Draw everything
        //window.draw(titleText);
        window.draw(playerSprite);
        window.draw(enemySprite);
        //window.draw(playerCircle);
        //window.draw(enemyCircle);
        window.draw(playerAABBDisplay);
        window.draw(enemyAABBDisplay);

        window.display();
    }

    return 0;
}