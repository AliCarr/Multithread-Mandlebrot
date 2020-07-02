#pragma once
#include <SFML/Graphics.hpp>
#include <complex>

class MandleBrot
{
public:
	MandleBrot(int winX, int winY);
	//~MandleBrot();

	void DrawSection(int minX, int minY, int maxX, int maxY);

	void Bake();

	sf::Sprite Render();

private:

	int width, height;
	sf::Uint8* m_pixels;
	sf::Color m_colour;

	sf::Image m_mandlebrotImage;
	sf::Texture m_tex;
	sf::Sprite m_sprite;
};

