#include <SFML/Graphics.hpp>
#include <math.h>

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080

int main() {
  bool windowFocused = false;

  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "2D Game", sf::Style::Close);
  float distance = 0.0f;
  float speed = 100.0f;

  sf::Clock clock;
  sf::Time elapsedTime;

  while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::GainedFocus:
				windowFocused = true;
				break;
			case sf::Event::LostFocus:
				windowFocused = false;
				break;
			}
		}

		elapsedTime = clock.restart();

		if (windowFocused) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
				// up key is pressed: move screen
				distance += elapsedTime.asSeconds() * speed;
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
				// down key is pressed: move screen
				distance -= elapsedTime.asSeconds() * speed;
			}
		}

		/* DRAWING  */
		window.clear();

		sf::Color skyTopColor = sf::Color::White;
		sf::Color skyBottomColor = sf::Color::Blue;

		sf::Vertex sky[] = {
			sf::Vertex(sf::Vector2f(0, 0), skyTopColor), // TL
			sf::Vertex(sf::Vector2f(SCREEN_WIDTH, 0), skyTopColor), // TR
			sf::Vertex(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT * 0.75), skyBottomColor), // BR
			sf::Vertex(sf::Vector2f(0, SCREEN_HEIGHT * 0.75), skyBottomColor) // BL
		};

		window.draw(sky, 4, sf::Quads);

		// Draw Background (Path/Ground)
		for (int y = 0; y < SCREEN_HEIGHT / 2; y++) {
		  float perspective = (float)y / (SCREEN_HEIGHT / 2.0f);

		  float midPoint = 0.5f;
		  float roadWidth = 0.3f + perspective * 0.8;

		  roadWidth *= 0.5f;
		  int nLeftGround = (midPoint - roadWidth) * SCREEN_WIDTH;
		  int nRightGround = (midPoint + roadWidth) * SCREEN_WIDTH;
		  int nRow = y + SCREEN_HEIGHT / 2.0f;

		  sf::Color groundColor = sinf(20.0f * powf(1.0f - perspective, 3) + distance * 0.1f) > 0.0f ? sf::Color(65, 152, 10, 255) : sf::Color(19, 133, 16, 255);
		  sf::Color pathColor = sf::Color(102, 68, 0, 255);

		  sf::Vertex leftGround[] = {
			  sf::Vertex(sf::Vector2f(0, nRow), groundColor),
			  sf::Vertex(sf::Vector2f(nLeftGround, nRow), groundColor),
		  };
		  sf::Vertex rightGround[] = {
			  sf::Vertex(sf::Vector2f(nRightGround, nRow), groundColor),
			  sf::Vertex(sf::Vector2f(SCREEN_WIDTH, nRow), groundColor),
		  };
		  sf::Vertex path[] = {
			  sf::Vertex(sf::Vector2f(nLeftGround, nRow), pathColor),
			  sf::Vertex(sf::Vector2f(nRightGround, nRow), pathColor),
		  };
		  window.draw(leftGround, 2, sf::Lines);
		  window.draw(path, 2, sf::Lines);
		  window.draw(rightGround, 2, sf::Lines);
		}
		//	//	//	//

		window.display();
		}
  return 0;
}