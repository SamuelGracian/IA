#include <iostream>
#include <SFML/Graphics.hpp>

#include "Boid.h"
#include "VectorFloat.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode({ 900,700 }), "Steering behaviors");

	Boid SeekerBoid;
	Boid FleeingBoid;

	SeekerBoid.SetColor(sf::Color::Red);

	FleeingBoid.SetColor(sf::Color::Blue);

	SeekerBoid.SetPosition({ -500.0f, 500.0f });

	FleeingBoid.SetPosition({ 30.0f, 30.0f });


	SeekObjective seek;
	seek.isActive = true;
	seek.seekforce = 0.1f;
	seek.target = SeekerBoid.ConvertToVector2f(FleeingBoid.getShape().getPosition());
	SeekerBoid.SetSeekObjective(seek);

	FleeObjective flee;
	flee.isActive = true;
	flee.fleeForce = 0.1f;
	flee.target = FleeingBoid.ConvertToVector2f(SeekerBoid.getShape().getPosition());
	FleeingBoid.SetFleeObjective(flee);



	while (window.isOpen())
	{

		while (std::optional <sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

			seek.target = SeekerBoid.ConvertToVector2f(FleeingBoid.getShape().getPosition());
			SeekerBoid.SetSeekObjective(seek);

			flee.target = FleeingBoid.ConvertToVector2f(SeekerBoid.getShape().getPosition());
			FleeingBoid.SetFleeObjective(flee);
		


			SeekerBoid.Update();
			FleeingBoid.Update();

			window.clear();
			window.draw(SeekerBoid.getShape());
			window.draw(FleeingBoid.getShape());
			window.display();
	}



	return 0;
}
