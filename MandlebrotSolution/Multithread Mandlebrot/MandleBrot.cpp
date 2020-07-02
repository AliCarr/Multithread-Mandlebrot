#include "MandleBrot.h"

MandleBrot::MandleBrot(int winX, int winY)
{
	width = winX;
	height = winY;

	m_pixels = new sf::Uint8[width * height * 4];

	m_colour = sf::Color::Cyan;

	for (int x = 0; x < width; x++)
		for (int y = 0; y < height; y++)
		{
			m_pixels[4 * (x + width * y)    ] = m_colour.r; // R?
			m_pixels[4 * (x + width * y) + 1] = m_colour.g; // G?
			m_pixels[4 * (x + width * y) + 2] = m_colour.b; // B?
			m_pixels[4 * (x + width * y) + 3] = m_colour.a; // A?
		}

}

void MandleBrot::DrawSection(int minX, int minY, int maxX, int maxY)
{

	for (std::size_t ix = minX; ix < maxX; ++ix)
		for (std::size_t iy = minY; iy < maxY; ++iy)
		{
			std::complex<double> c(-1 + ix / (width - 1.0) * (1 - (-1)), -1 + iy / (height - 1.0) * (1 - (-1)));
			std::complex<double> z = 0;
			unsigned int iterations;

			for (iterations = 0; iterations < 100 && std::abs(z) < 2.0; ++iterations)
				z = z * z + c;

			float test = std::abs(z);
			//pixels[ix + 800 * iy] = (iterations == (unsigned int)100) ? 0 : 255;

			m_pixels[4 * (ix + width * iy)    ] = (iterations >= (unsigned int)100) ? 0   :   0; // R?
			m_pixels[4 * (ix + width * iy) + 1] = (iterations >= (unsigned int)100) ? 255 :   0; // G?
			m_pixels[4 * (ix + width * iy) + 2] = (iterations >= (unsigned int)100) ? 0   : 255; // B?
			m_pixels[4 * (ix + width * iy) + 3] = 255; // A?
		}

}

void MandleBrot::Bake()
{
	m_mandlebrotImage.create(width, height, m_pixels);
	m_tex.loadFromImage(m_mandlebrotImage);
}

sf::Sprite MandleBrot::Render()
{
	sf::Sprite m_tempSprite(m_tex);
	return m_tempSprite;
}
