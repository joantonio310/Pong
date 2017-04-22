#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <cmath>
#include <string> 
#include <sstream>
#include <ctime>

namespace patch
{
    template < typename T > std::string to_string( const T& n )
    {
        std::ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
} 

int main()
{
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	sf::Vector2f paddleSize(25, 100);
	float ballAngle = 0.f; // to be changed later
	const float pi = 3.14159f;
	bool turnRight = true;
    bool isPlaying = true;
	int counterLeft = 0;
	int counterRight = 0;

	//put the letters for the scoreboard
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{
	    // error...
	}

    //scoreboard america
	sf::Text textLeft;
	// select the font
	textLeft.setFont(font); // font is a sf::Font
	// set the string to display
	textLeft.setString("Goles: 0");
	// set the character size
	textLeft.setCharacterSize(40); // in pixels, not points!
	// set the color
	textLeft.setColor(sf::Color::White);
	// set the text style
	textLeft.setStyle(sf::Text::Bold);

    //scoreboard chivas
	sf::Text textRight;
	textRight.setFont(font); // font is a sf::Font
	textRight.setString("Goles: 0");
	textRight.setCharacterSize(40); // in pixels, not points!
	textRight.setColor(sf::Color::White);
	textRight.setStyle(sf::Text::Bold);


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

    sf::Texture texturePause;
    if (!texturePause.loadFromFile("pausa.jpg"))
        return EXIT_FAILURE;
    sf::Sprite pause(texturePause);

    //set the America symbol
    sf::Texture textureAmerica;
    if (!textureAmerica.loadFromFile("america.png"))
        return EXIT_FAILURE;
    sf::Sprite america(textureAmerica);

    //set the Chivas symbol
    sf::Texture textureChivas;
    if (!textureChivas.loadFromFile("chivas.png"))
        return EXIT_FAILURE;
    sf::Sprite chivas(textureChivas);

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
    ball.setPosition(497,rand() % 630 + 60);
    america.setPosition(0,0);
    chivas.setPosition(950,0);
    textLeft.setPosition(80,0);
    textRight.setPosition(750,0);
    pause.setPosition(392,291);

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

            //put pause
            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Space))
            {   
                if(isPlaying == true)
                    isPlaying = false;
                else
                    isPlaying = true;
            }
        }

        if (isPlaying)
        {
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
        	ball.move(std::cos(ballAngle), std::sin(ballAngle));

                    //hit the ball with the right paddle
            if(ball.getPosition().x > 900 && turnRight){
            	turnRight = false;
    	        if(rightPaddle.getPosition().y - ball.getPosition().y  >= 10 && rightPaddle.getPosition().y - ball.getPosition().y  <= 30){
    	        	printf("En medio\n");
    	        	ballAngle = pi;
    	        }
    	    	else if(rightPaddle.getPosition().y - ball.getPosition().y  >= 31 && rightPaddle.getPosition().y - ball.getPosition().y  <= 50){
    	        	printf("Arriba\n");
    	        	ballAngle = (7*pi)/6;
    	    	}
    	        else if(rightPaddle.getPosition().y - ball.getPosition().y  >= -10 && rightPaddle.getPosition().y - ball.getPosition().y  <= 9){
    	        	printf("Abajo\n");
    	        	ballAngle = (5*pi)/6;
    	        }
    	        else if(rightPaddle.getPosition().y - ball.getPosition().y  >= 51 && rightPaddle.getPosition().y - ball.getPosition().y  <= 70){
    	        	printf("Hasta arriba\n");
    	        	ballAngle = (2*pi)/3;
    	        }
    	        else if(rightPaddle.getPosition().y - ball.getPosition().y  >= -30 && rightPaddle.getPosition().y - ball.getPosition().y  <= -11){
    	        	printf("Hasta abajo\n");
    	        	ballAngle = (4*pi)/3;
    	        }
    	        else{
    	        	counterLeft++;
    	        	ball.setPosition(899,rand() % 620 + 60);
    	        	ballAngle = pi;
    	        }
    	        textLeft.setString("Goles: " + patch::to_string(counterLeft));
            }

            //hit the ball with the left paddle
            if(ball.getPosition().x < 100 && !turnRight){
            	turnRight = true;
    	        if(leftPaddle.getPosition().y - ball.getPosition().y  >= 10 && leftPaddle.getPosition().y - ball.getPosition().y  <= 30){
    	        	printf("En medio\n");
    	        	ballAngle = 0.f;
    	        }
    	    	else if(leftPaddle.getPosition().y - ball.getPosition().y  >= 31 && leftPaddle.getPosition().y - ball.getPosition().y  <= 50){
    	        	printf("Arriba\n");
    	   			ballAngle = -(pi)/6;
    	    	}
    	        else if(leftPaddle.getPosition().y - ball.getPosition().y  >= -10 && leftPaddle.getPosition().y - ball.getPosition().y  <= 9){
    	        	printf("Abajo L\n");
    	        	ballAngle = -(11*pi)/6;
    	        }
    	        else if(leftPaddle.getPosition().y - ball.getPosition().y  >= 51 && leftPaddle.getPosition().y - ball.getPosition().y  <= 70){
    	        	printf("Hasta arriba\n");
    	        	ballAngle = -(pi)/3;
    	        }
    	        else if(leftPaddle.getPosition().y - ball.getPosition().y  >= -30 && leftPaddle.getPosition().y - ball.getPosition().y  <= -11){
    	        	printf("Hasta abajo\n");
    	        	ballAngle = -(5*pi)/3;
    	        }
    	        else{
    	        	counterRight++;
    	        	ball.setPosition(101,rand() % 640 + 60);
    	        	ballAngle = 0.f;
    	        }
    	        textRight.setString("Goles: " + patch::to_string(counterRight));
            }

            //hit the top of the table
            if(ball.getPosition().y < 55){
            	printf("fuera\n");
            	ballAngle *= -1;
            }

        	//hit the bottom of the table
            if(ball.getPosition().y > 675){
            	printf("fuera\n");
            	ballAngle *= -1;
            }
        }

        // Clear screen
        window.clear();
        // Draw the sprite
        window.draw(sprite);

        window.draw(ball);
        window.draw(america);
        window.draw(chivas);
        window.draw(leftPaddle);
        window.draw(rightPaddle);
        window.draw(textLeft);
        window.draw(textRight);

        if (!isPlaying)
            window.draw(pause);

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}