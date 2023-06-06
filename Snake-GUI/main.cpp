#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Window");
	window.setFramerateLimit(60);

	const int gridSize = 10;
	const int squareSize = 50;

	// �������� ��������
	sf::RectangleShape square(sf::Vector2f(squareSize, squareSize));
	square.setFillColor(sf::Color::White);

	for (int row = 0; row < gridSize; ++row)
	{
		for (int col = 0; col < gridSize; ++col)
		{
			// ���������������� ��������
			square.setPosition(col * squareSize, row * squareSize);

			// ����������� ����� ��������
			if ((row + col) % 2 == 0) // �������� ��������/���������� ����� ���������
			{
				square.setFillColor(sf::Color::Green);
			}
			else
			{
				sf::Color lightGreen(144, 238, 144);
				square.setFillColor(lightGreen);
			}

			// ��������� ��������
			window.draw(square);
		}
	}
	

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		
		window.display();
	}

	return 0;
}