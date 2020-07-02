#include <SFML/Graphics.hpp>
#include "MandleBrot.h"
#include <thread>

int main()
{
	const int width = 1200;
	const int height = 700;

	//The number of threads
	const int segmentNumber = 40;

	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Fractals");// , sf::Style::Fullscreen);
	
	MandleBrot* m_brot = new MandleBrot(width, height);

	std::thread threads[segmentNumber];

	for (int c = 0; c < segmentNumber; c++)
		threads[c] = std::thread(&MandleBrot::DrawSection, m_brot, (width / segmentNumber) * (c), 0, (width / segmentNumber) * (c + 1), height);

	for (int c = 0; c < segmentNumber; c++)
		threads[c].join();

	m_brot->Bake();

	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window->close();
		}

		window->clear();
		window->draw(m_brot->Render());
		window->display();

		if (event.key.code == sf::Keyboard::Escape)
			window->close();
	}

}