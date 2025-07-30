#include "world.h"
#include<iostream>

World::World(const std::string background) {

}

void World::AddBoid(const Boid& boid) {
    m_boidsVector.push_back(boid);
}

void World::AddObstacle(const Obstacles& obstacle) {
    m_obstaclesVector.push_back(obstacle);
}

void World::Update() {
    for (auto& obstacle : m_obstaclesVector) {
        obstacle.Update();
    }

    std::vector<Obstacle> obstacles;
    for (const auto& obstacle : m_obstaclesVector) {
        obstacles.push_back({obstacle.GetPosition(), obstacle.GetColor(), obstacle.GetRadius()});
    }

    for (auto& boid : m_boidsVector) {
        boid.AddObstacles(&obstacles);
        boid.Update();
    }
}

void World::Render(sf::RenderTarget* window) {
    window->draw(m_background);

    for (const auto& obstacle : m_obstaclesVector) {

        // window->draw(obstacle.getShape());
    }

    for (const auto& boid : m_boidsVector) {
        // window->draw(boid.getShape());
    }
}

void World::SetTexture (const std::string file)
{
	if (!m_texture.loadFromFile(file))
	{
		std::cerr << "Error loading image: " << file << std::endl;
		return;
	}
	m_background.setTexture(&m_texture);
}