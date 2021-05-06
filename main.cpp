#include <cmath>
#include <vector>

#include <SFML/Graphics.hpp>

#include "functions.hpp"
#include "system.hpp"

int main()
{
	sf::RenderWindow window(sf::VideoMode(800U, 600U), "Gravity Grid");

	sf::Vector2f min_point(  0.0f,   0.0f);
	sf::Vector2f max_point(775.0f, 575.0f);

	const auto N_length = 4U;

	const auto N_width = 5U;

	const auto keep_distance = length(max_point - min_point) * 0.1 / N_length;

	const auto r = 2.5f;

	auto start_point = (max_point - min_point) * 0.5;

	auto point = start_point;

	std::vector < System::particle_t > particles;

	for (auto i = 0U; i < N_length * N_width; ++i)
	{
		particles.push_back(std::make_shared < Particle >(point, point, sf::Vector2f(0.0f, 10.0f), r));

		if (i != 0 and (i + 1) % N_width == 0)
		{
			point.y -= keep_distance;
			point.x = start_point.x;
			particles.push_back(std::make_shared < Particle >(point, point, sf::Vector2f(0.0f, 10.0f), r));
		}

		point.x += keep_distance;
	}

	System system(min_point, max_point, particles);

	sf::Event event;

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}

		system.update();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			system.push(sf::Vector2f(0.0f, -2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			system.push(sf::Vector2f(0.0f, 2.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			system.push(sf::Vector2f(-2.0f, 0.0f));
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			system.push(sf::Vector2f(2.0f, 0.0f));
		}

		window.clear();
		
		for (auto i = 0U; i < system.particles().size(); ++i)
		{
			sf::CircleShape circle(2.0f * r);

			circle.setPosition(system.particle(i)->position() + sf::Vector2f(r, r));

			circle.setFillColor(sf::Color::Red);

			window.draw(circle);
		}
	
		window.display();
	}
	
	// system("pause");

	return EXIT_SUCCESS;
}
