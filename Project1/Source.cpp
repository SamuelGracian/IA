#include <iostream>
#include <SFML/Graphics.hpp>

#include "Boid.h"
#include "VectorFloat.h"

Path path;

int main()
{
	path.waypoints = {
		{ 100.0f, 100.0f },
		{ 200.0f, 200.0f },
		{ 300.0f, 100.0f },
		{ 400.0f, 300.0f },
		{ 500.0f, 200.0f }
	};

	srand(time(nullptr));

	sf::RenderWindow window(sf::VideoMode({ 1280,720 }), "Steering behaviors");

	std::vector<Boid> BoidsVector;
	BoidsVector.resize(3);

	Boid& SeekerBoid = BoidsVector[0];
	Boid& FleeingBoid = BoidsVector[1];
	Boid& Pathboid = BoidsVector[2];

	//Set colors for the boids
	SeekerBoid.SetColor(sf::Color::Red);

	FleeingBoid.SetColor(sf::Color::Blue);

	Pathboid.SetColor(sf::Color::Yellow);

	//Set starting positions for the boids
	SeekerBoid.SetPosition({ 500.0f, 500.0f });

	FleeingBoid.SetPosition({ 300.0f, 300.0f });

	Pathboid.SetPosition({ 100.0f, 100.0f });

	//set mass for the boids 
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

	Pathboid.m_currentWaypoint = 0;

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

			sf::Vector2f flowwoforce = Pathboid.FollowPath(Pathboid.getShape().getPosition(), path, Pathboid.m_currentWaypoint, 10.0f);
			Pathboid.SetPosition(Pathboid.getShape().getPosition() + flowwoforce);

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
