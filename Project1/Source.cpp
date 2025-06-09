#include <iostream>
#include <SFML/Graphics.hpp>

#include "Boid.h"
#include "VectorFloat.h"


int main()
{
	sf::RenderWindow window(sf::VideoMode({900,700}), "Steering behaviors");


	Boid SeekerBoid;
	Boid FleeingBoid;

	while (window.isOpen())
	{
		
		while ( std::optional <sf::Event> event =  window.pollEvent() )
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

		FleeObjective flee;
		SeekObjective seek;
		//Seeker
		seek.isActive = true;
		seek.target = flee.Position;
		seek.Position = Vector2f(50,50);
		seek.seekforce = 1.0f;
		SeekerBoid.SetSeekObjective(seek);
		SeekerBoid.SetColor(sf::Color::Red);

		//Flee
		flee.isActive = true;
		flee.Position = Vector2f(10.0f, 10.0f);
		flee.fleeForce = 1.0f;
		flee.target = seek.Position;
		FleeingBoid.SetFleeObjective(flee);
		FleeingBoid.SetColor(sf::Color::Blue);

		SeekerBoid.Update();
		FleeingBoid.Update();

		window.clear();
		window.draw(SeekerBoid.getShape());
		window.draw(FleeingBoid.getShape());
		window.display();
	}

	return 0;
}