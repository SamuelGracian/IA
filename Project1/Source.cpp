#include <iostream>
#include <SFML/Graphics.hpp>

#include "Boid.h"
#include "VectorFloat.h"


int main()
{
	srand(time(nullptr));

	sf::RenderWindow window(sf::VideoMode({ 1280,720 }), "Steering behaviors");

	std::vector<Boid> BoidsVector;
	BoidsVector.resize(2);

	Boid& SeekerBoid = BoidsVector[0];
	Boid& FleeingBoid = BoidsVector[1];

	SeekerBoid.SetColor(sf::Color::Red);

	FleeingBoid.SetColor(sf::Color::Blue);

	SeekerBoid.SetPosition({ 500.0f, 500.0f });

	FleeingBoid.SetPosition({ 300.0f, 300.0f });

	SeekerBoid.SetMass(100);

	SeekObjective seek;
	seek.isActive = true;
	seek.seekforce = 10.0f;
	seek.target = SeekerBoid.ConvertToVector2f(FleeingBoid.getShape().getPosition());
	SeekerBoid.SetSeekObjective(seek);

	FleeObjective flee;
	flee.isActive = true;
	flee.fleeForce = 10.0f;
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

			window.clear();
			for (auto& boid : BoidsVector)
			{
				boid.Update();
				window.draw(boid.getShape());
			}

			window.display();
	}



	return 0;
}
