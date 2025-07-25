#include <iostream>
#include <SFML/Graphics.hpp>

#include "Boid.h"
#include "VectorFloat.h"


int main()
{
	srand(time(nullptr));

	sf::RenderWindow window(sf::VideoMode({ 1280,1000 }), "Steering behaviors");

	std::vector<Boid> BoidsVector;

	std::vector<Obstacle> ObstacleVector;

	ObstacleVector.resize(1);

	BoidsVector.resize(4);

	Boid& SeekerBoid = BoidsVector[0];
	Boid& FleeingBoid = BoidsVector[1];
	Boid& PathBoid = BoidsVector[2];
	Boid& LoopBoid = BoidsVector[3];

	//Set colors for the boids
	SeekerBoid.SetColor(sf::Color::White);

	FleeingBoid.SetColor(sf::Color::Blue);

	PathBoid.SetColor(sf::Color::Yellow);

	LoopBoid.SetColor(sf::Color::Green);


	//Set starting positions for the boids
	SeekerBoid.SetPosition({ 500.0f, 500.0f });

	FleeingBoid.SetPosition({ 300.0f, 300.0f });

	PathBoid.SetPosition({ 600.0f, 100.0f });

	LoopBoid.SetPosition({ 300.0f, 200.0f });


	//Set texture
	SeekerBoid.SetTexture("DespairFrog.png");

	//
	for (auto& boid : BoidsVector)
	{
		boid.SetPointer(&BoidsVector);
		boid.AddObstacles(&ObstacleVector);
	}

	//set mass for the boids 
	SeekerBoid.SetMass(1);

	SeekObjective seek;
	seek.isActive = true;
	seek.seekforce = 10.0f;
	seek.radius = 100.0f;
	seek.target = FleeingBoid.GetPosition();
	SeekerBoid.SetSeekObjective(seek);

	FleeObjective flee;
	flee.isActive = true;
	flee.fleeForce = 10.0f;
	flee.radius = 10.0f;
	flee.target = SeekerBoid.GetPosition();
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
	path.radius = 30.0f;
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
	loop.radius = 20.0f;
	loop.FollowForce = 10.0f;
	loop.ActiveLoop =true;

	PathBoid.ActiveFollowPatch(path);

	LoopBoid.ActiveFollowPatch(loop);


	//______obstacles

	for (auto& obstacle : ObstacleVector)
	{
		obstacle.position = sf::Vector2f(800.0f, 200.0f);

		obstacle.radius = 100.0f;

		obstacle.color = sf::Color::Magenta;
	}



	while (window.isOpen())
	{

		while (std::optional <sf::Event> event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}

			seek.target = FleeingBoid.GetPosition();
			SeekerBoid.SetSeekObjective(seek);

			flee.target = SeekerBoid.GetPosition();
			FleeingBoid.SetFleeObjective(flee);

			window.clear();

			for (auto& boid : BoidsVector)
			{
				sf::CircleShape circleShape;
				circleShape.setRadius(boid.GetRadius());
				circleShape.setFillColor(boid.GetColor());
				circleShape.setTexture(boid.GetTexture());
				boid.Update();
				circleShape.setPosition(boid.GetPosition());
				window.draw(circleShape);
			}

			for (auto& obst : ObstacleVector)
			{
				sf::CircleShape obstacleshape;
				obstacleshape.setRadius(obst.radius);
				obstacleshape.setOrigin(sf::Vector2f(obst.radius,obst.radius));

				obstacleshape.setPosition(obst.position);
				obstacleshape.setFillColor(obst.color);
				window.draw(obstacleshape);
			}

			window.display();
	}

	return 0;
}
