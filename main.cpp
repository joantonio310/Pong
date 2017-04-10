#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>

int main()
{
	sf::Vector2f paddleSize(25, 100);

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1024, 765), "Pong");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("soccerField.jpeg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    // Create the left paddle
    sf::RectangleShape leftPaddle;
    leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    leftPaddle.setOutlineThickness(3);
    leftPaddle.setOutlineColor(sf::Color::Black);
    leftPaddle.setFillColor(sf::Color(255, 255, 51));
    leftPaddle.setOrigin(paddleSize / 2.f);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("music.wav"))
        return EXIT_FAILURE;
    // Play the music
    //music.play();

    leftPaddle.setPosition(100,660);

    // Start the game loop
    while (window.isOpen())
    {

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Move the player's paddle
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 
        	leftPaddle.getPosition().y > 110)
        {
            leftPaddle.move(0.f, -1.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        	leftPaddle.getPosition().y < 660)
        {
        	leftPaddle.move(0.f, 1.f);
        }

        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);

        window.draw(leftPaddle);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}