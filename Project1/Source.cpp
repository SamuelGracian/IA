#include <iostream>
#include <SFML/Graphics.hpp>

#include "Boid.h"
#include "VectorFloat.h"


int main()
{
	srand(time(nullptr));

	sf::RenderWindow window(sf::VideoMode({ 1280,1000 }), "Steering behaviors");

	std::vector<Boid> BoidsVector;
	BoidsVector.resize(4);

	Boid& SeekerBoid = BoidsVector[0];
	Boid& FleeingBoid = BoidsVector[1];
	Boid& PathBoid = BoidsVector[2];
	Boid& LoopBoid = BoidsVector[3];



	//Set colors for the boids
	SeekerBoid.SetColor(sf::Color::Red);

	FleeingBoid.SetColor(sf::Color::Blue);

	PathBoid.SetColor(sf::Color::Yellow);

	LoopBoid.SetColor(sf::Color::Green);


	//Set starting positions for the boids
	SeekerBoid.SetPosition({ 500.0f, 500.0f });

	FleeingBoid.SetPosition({ 300.0f, 300.0f });

	PathBoid.SetPosition({ 600.0f, 100.0f });

	LoopBoid.SetPosition({ 300.0f, 200.0f });


	//
	for (auto& boid : BoidsVector)
	{
		boid.SetPointer(&BoidsVector);
	}

	//set mass for the boids 
	SeekerBoid.SetMass(10);

	SeekObjective seek;
	seek.isActive = true;
	seek.seekforce = 10.0f;
	seek.radius = 10.0f;
	seek.target = FleeingBoid.getShape().getPosition();
	SeekerBoid.SetSeekObjective(seek);

	FleeObjective flee;
	flee.isActive = true;
	flee.fleeForce = 10.0f;
	flee.radius = 10.0f;
	flee.target = SeekerBoid.getShape().getPosition();
	FleeingBoid.SetFleeObjective(flee);

	Path path;
	path.waypoints = {
	{ 120.0f, 120.0f },
	{ 200.0f, 200.0f },
	{ 300.0f, 100.0f },
	{ 400.0f, 300.0f },
	{ 500.0f, 200.0f },
	{ 700.0f, 300.0f}
	};
	path.ActivePath = true;
	path.radius = 30;
	path.FollowForce = 10.0f;
	path.ActiveLoop = false;

	Path loop;
	loop.waypoints = {
	{ 120.0f, 120.0f },
	{ 200.0f, 200.0f },
	{ 300.0f, 100.0f },
	{ 400.0f, 300.0f },
	{ 500.0f, 200.0f },
	{ 700.0f, 300.0f}
	};
	loop.ActivePath = true;
	loop.radius = 30;
	loop.FollowForce = 10.0f;
	loop.ActiveLoop = true;

	PathBoid.ActiveFollowPatch(path);

	LoopBoid.ActiveFollowPatch(loop);


	while (window.isOpen())
	{

		while (std::optional <sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

			seek.target = FleeingBoid.getShape().getPosition();
			SeekerBoid.SetSeekObjective(seek);

			flee.target = SeekerBoid.getShape().getPosition();
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
