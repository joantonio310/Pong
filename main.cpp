#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <cmath>

int main()
{
	sf::Vector2f paddleSize(25, 100);
	float ballAngle = 0.f; // to be changed later
	bool right = true;
	const float pi = 3.14159f;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1024, 765), "Pong");
    // Load a sprite to display
    sf::Texture texture;
    if (!texture.loadFromFile("soccerField.jpeg"))
        return EXIT_FAILURE;
    sf::Sprite sprite(texture);

    sf::Texture textureBall;
    if (!textureBall.loadFromFile("ball.png"))
        return EXIT_FAILURE;
    sf::Sprite ball(textureBall);

    // Create the left paddle
    sf::RectangleShape leftPaddle;
    leftPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    leftPaddle.setOutlineThickness(3);
    leftPaddle.setOutlineColor(sf::Color::Black);
    leftPaddle.setFillColor(sf::Color(255, 255, 51));
    leftPaddle.setOrigin(paddleSize / 2.f);

    // Create the right paddle
    sf::RectangleShape rightPaddle;
    rightPaddle.setSize(paddleSize - sf::Vector2f(3, 3));
    rightPaddle.setOutlineThickness(3);
    rightPaddle.setOutlineColor(sf::Color::Black);
    rightPaddle.setFillColor(sf::Color(255, 0, 0));
    rightPaddle.setOrigin(paddleSize / 2.f);

    // Load a music to play
    sf::Music music;
    if (!music.openFromFile("music.wav"))
        return EXIT_FAILURE;
    // Play the music
    //music.play();

    leftPaddle.setPosition(100,389);
    rightPaddle.setPosition(928,389);
    ball.setPosition(497,380);

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && 
        	leftPaddle.getPosition().y > 110)
        {
            leftPaddle.move(0.f, -1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) &&
        	leftPaddle.getPosition().y < 660)
        {
        	leftPaddle.move(0.f, 1.f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 
        	rightPaddle.getPosition().y > 110)
        {
            rightPaddle.move(0.f, -1.f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) &&
        	rightPaddle.getPosition().y < 660)
        {
        	rightPaddle.move(0.f, 1.f);
        }

        //move the ball
        if(right)
        	ball.move(std::cos(ballAngle), std::sin(ballAngle));
        else
        	ball.move(-std::cos(ballAngle), -std::sin(ballAngle));

        if(ball.getPosition().x > 900){
        	//right = false;
	        if(rightPaddle.getPosition().y - ball.getPosition().y  >= 10 && rightPaddle.getPosition().y - ball.getPosition().y  <= 30){
	        	printf("En medio\n");
	        	ballAngle = 0.f;
	        }
	    	else if(rightPaddle.getPosition().y - ball.getPosition().y  >= 31 && rightPaddle.getPosition().y - ball.getPosition().y  <= 50){
	        	printf("Arriba\n");
	        	ballAngle = -(5*pi)/6;
	    	}
	        else if(rightPaddle.getPosition().y - ball.getPosition().y  >= -10 && rightPaddle.getPosition().y - ball.getPosition().y  <= 9){
	        	printf("Abajo\n");
	        	ballAngle = (5*pi)/6;
	        }
	        else if(rightPaddle.getPosition().y - ball.getPosition().y  >= 51 && rightPaddle.getPosition().y - ball.getPosition().y  <= 70){
	        	printf("Hasta arriba\n");
	        	ballAngle = -(2*pi)/3;
	        }
	        else if(rightPaddle.getPosition().y - ball.getPosition().y  >= -30 && rightPaddle.getPosition().y - ball.getPosition().y  <= -11){
	        	printf("Hasta abajo\n");
	        	ballAngle = (2*pi)/3;
	        }
	        else{
	        	printf("Nop\n");
	        }
        }

        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);

        window.draw(ball);
        window.draw(leftPaddle);
        window.draw(rightPaddle);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}