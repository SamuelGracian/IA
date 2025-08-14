#include "Boid.h"

void Boid::SetRandomDirection()
{
	float force;

	sf::Vector2f wanderPosition(rand() % 1280, rand() % 1000);

	m_direction = wanderPosition.normalized();
}

sf::Vector2f Boid::Seek(const sf::Vector2f& position, const sf::Vector2f& target, float seekforce)
{
	sf::Vector2f force (0,0);

	sf::Vector2f Desired = (target - position);


	if (Desired.length() == 0.0f)
	{
		return force;
	}
	Desired = Desired.normalized();

	force = Desired * seekforce;
	return force;
}

const sf::Vector2f Boid::Flee (const sf::Vector2f& position,
		const sf::Vector2f& target,
		float radius,
		float fleeForce)
{
	sf::Vector2f force(0, 0);
	sf::Vector2f diference = position - target;
	float distance = diference.length();
	if (distance > radius)
	{
		return force;
	}
	sf::Vector2f Desired = diference.normalized();
	force = Desired * fleeForce;
	return force;
}


sf::Vector2f Boid::Wander(float wanderForce)
{
	sf::Vector2f force = sf::Vector2f(0, 0);

	sf::Vector2f wanderPosition(rand() % 1280, rand() % 1000);

	return Seek(m_position, wanderPosition, wanderForce);
}

void Boid::Arrive(const sf::Vector2f& target, float slowRadius)
{
	sf::Vector2f Desired = (target - m_position).normalized();
	float distance = (target - m_position).length();
	if (distance < slowRadius)
	{
		Desired *= (distance / slowRadius);
	}
	else
	{
		Desired *= 1.0f; // Full speed
	}
	sf::Vector2f force = Desired - m_direction;
	m_direction += force;
	m_direction= m_direction.normalized();
	m_position += m_direction;
}

sf::Vector2f Boid::PatrolLoop(sf::Vector2f position, const Path& path, size_t & currentwaypoint, float followforce )
{
	if (path.waypoints.empty()) return sf::Vector2f(0.0f, 0.0f);
	sf::Vector2f target = path.waypoints[m_currentWaypoint];
	sf::Vector2f origin = position;
	
	if (currentwaypoint > 0)
	{
		origin = path.waypoints[currentwaypoint - 1];
	}

	float distance = (target - position).length();

	sf::Vector2f Vector_A = (target - origin);
	sf::Vector2f Vector_B = (position - origin);

	float escalar = (Vector_B.dot(Vector_A)) / (Vector_A.dot(Vector_A));
	escalar = std::clamp(escalar, 0.0f, 1.0f);

	sf::Vector2f NearestPointinLine = Vector_B + (Vector_A * escalar);

	if (distance < path.radius)
	{
		currentwaypoint = (currentwaypoint + 1) % path.waypoints.size();
	}
	sf::Vector2f ForcetoTarget = Seek(position, target, followforce);
	sf::Vector2f ForcetoLine = Seek(position, NearestPointinLine, followforce);


	sf::Vector2f FinalForce = (ForcetoTarget + ForcetoLine).normalized() * followforce;

	return FinalForce;

}

sf::Vector2f Boid::Direction(sf::Vector2f position,std::vector <Boid>* world, float distance, float DirectionForce)
{
	sf::Vector2f FinalDirection; 

	float BoidsDistance;

	for (int i = 0; i < world->size(); i++)
	{
		auto& pboid = world->at(i);

		BoidsDistance =( pboid.GetPosition() - position).length();

		if (BoidsDistance <= distance)
		{
			FinalDirection += pboid. GetDirection();
		}
	}

	FinalDirection = FinalDirection.normalized() * DirectionForce;

	return FinalDirection; 
}

sf::Vector2f Boid::Separation(std::vector<Boid>* world,float radius, float force)
{
	sf::Vector2f finalForce (0.0f,0.0f);

	for (auto& boid : *world)
	{
		sf::Vector2f difference = m_position - boid.GetPosition();

		float distance = difference.length();

		if (distance < radius && distance > 0.0f)
		{
			float inverseDistance = 1.0f - (distance / radius);

			difference = difference / distance;

			finalForce += difference * force * inverseDistance;
		}
	}
	return finalForce;
}

sf::Vector2f Boid::Cohesion(std::vector<Boid>* world, float radius, float force)
{
	sf::Vector2f massCenter(0.0f, 0.0f);

	int count = 0;
	for (auto& boid : *world)
	{
		sf::Vector2f difference = m_position - boid.GetPosition();

		float distance = difference.length();

		if (distance < radius && distance > 0.0f)
		{
			massCenter += boid.GetPosition();
			count++;
		}
	}
	if (count > 0)
	{
		massCenter /= static_cast<float> (count);
	}
	return Seek(m_position, massCenter, force);
}

sf::Vector2f Boid::ObstacleAvoidance(const std::vector<Obstacles>* obstacles, float radius, float force)
{
	sf::Vector2f avoidForce(0.0f, 0.0f);

	float closestDistance = radius;

	for (const auto& obstacle : *obstacles)
	{

		sf::Vector2f difference = m_position - obstacle.GetPosition();

		float distance = difference.length();

		float combinedRadius = radius + obstacle.GetRadius();

		if (distance > 0 && distance < combinedRadius)
		{

			sf::Vector2f desired = difference / distance;

			avoidForce = desired * force;
			
		}
	}

	return avoidForce;
}


sf::Vector2f Boid::FollowPath(sf::Vector2f position , const Path &path , size_t &currentWaypoint, float FollowForce )
{
	if (path.waypoints.empty()) return sf::Vector2f(0, 0);

	if (currentWaypoint >= path.waypoints.size()) return sf::Vector2f(0, 0);

	sf::Vector2f target = path.waypoints[currentWaypoint];

	sf::Vector2f origin = position;

	if (currentWaypoint > 0 )
		origin = path.waypoints[currentWaypoint - 1];

	float distance = (target - position).length();

	sf::Vector2f vector_B = (target - origin);

	sf::Vector2f vector_A = (position - origin);

	float escalar = (vector_A.dot(vector_B)) / (vector_B.dot(vector_B));

	escalar = std::clamp(escalar, 0.0f, 1.0f);

	sf::Vector2f NearestPointinLine = origin + (vector_B * escalar);

	if (distance < m_radius)
	{
		if (currentWaypoint < path.waypoints.size() - 1)
		{
			currentWaypoint++;
		}
		else if (path.ActiveLoop)
		{
			currentWaypoint = 0;
		}
	}

	sf::Vector2f ForcetoTarget = Seek(position, target, FollowForce);

	sf::Vector2f ForcetoLine = Seek(position, NearestPointinLine, FollowForce);

	sf::Vector2f Addition = (ForcetoTarget + ForcetoLine);

	if (Addition.length() > 0.0f)
	{
		Addition.normalized();
	}

	sf::Vector2f FinalForce = Addition * FollowForce;

	return FinalForce;
	
}

sf::Vector2f Boid::GetDirection()
{
	return m_direction;
}

sf::Vector2f Boid::GetPosition()
{
	return m_position;
}

void Boid::SetTexture(const std::string imageFile)
{
	if (!m_texture.loadFromFile(imageFile))
	{
		std::cerr << "Error loading image: " << imageFile << std::endl;
		return;
	}
}

void Boid::AddObstacles(std::vector<Obstacles>* obstpointer)
{
	m_obstacles = obstpointer;
}

float Boid::GetRadius()
{
	return m_radius;
}

sf::Color Boid::GetColor()
{
	return m_color;
}

sf::Texture* Boid::GetTexture()
{
	return &m_texture;
}

void Boid::Update()
{
	m_desired = sf::Vector2f(0, 0);

	if (m_position.x < 0)
	{
		m_position.x = 1280;
	}

	if (m_position.y < 0)
	{
		m_position.y = 1000;
	}

	if (m_position.x > 1280)
	{
		m_position.x = 0;
	}

	if (m_position.y > 1000)
	{
		m_position.y = 0;
	}

	if (m_seekObjective.isActive)
	{
		m_desired += Seek(m_position, m_seekObjective.target, m_seekObjective.seekforce);
	}

	if (m_fleeObjective.isActive)
	{
		m_desired += Flee(m_position, m_fleeObjective.target, 100, m_fleeObjective.fleeForce);
		m_desired += Wander(3);
	}

	if (!m_path.waypoints.empty() && m_path.ActivePath)
	{
		m_desired += FollowPath(m_position, m_path, m_currentWaypoint, m_path.FollowForce);
	}

	m_desired += Wander(50);

	m_desired += Direction(m_position, m_BoidVectorP ,50,100);

	m_desired += Separation(m_BoidVectorP, 50, 100);
	
	m_desired += Cohesion(m_BoidVectorP, m_radius, 100);

	if (!m_obstacles->empty())
	{
		m_desired += ObstacleAvoidance(m_obstacles, m_radius , 10000);
	}

	float desiredLenght = m_desired.length();

	if (desiredLenght > 0.0f)
	{
		if (desiredLenght > 20.0f)
		{
			m_desired /= desiredLenght;
			m_desired *= 20.0f * 0.16f;
		}

		if (m_speed < m_maxSpeed)
		{
			m_speed += 0.01f;
			m_speed = std::min(m_speed, m_maxSpeed);
		}
		
		m_direction += m_desired * (1.0f / m_mass);
		m_direction = m_direction.normalized();
		m_position += m_direction * m_speed * 0.16f;
	}


	if (m_direction.length() > 0.0f)
	{
		m_direction = m_direction.normalized();
	}
	//m_shape.setPosition(m_position);
}

void Boid::SetSeekObjective(SeekObjective& seek)
{
	m_seekObjective.isActive = seek.isActive;
	m_seekObjective.target = seek.target;
	m_seekObjective.seekforce = seek.seekforce;
	m_radius = seek.radius;
}

void Boid::SetFleeObjective(FleeObjective& flee)
{
	m_fleeObjective.isActive = flee.isActive;
	m_fleeObjective.target = flee.target;
	m_fleeObjective.fleeForce = flee.fleeForce;
	m_radius = flee.radius;
}

void Boid::ActiveFollowPatch(Path& path)
{
	m_path.ActivePath = path.ActivePath;
	m_radius = path.radius;
	m_path.waypoints = path.waypoints;
	m_currentWaypoint = 0;
	m_path.FollowForce = path.FollowForce;
	m_path.ActiveLoop = path.ActiveLoop;
}

void Boid::SetColor(sf::Color color) {
    m_color = color;
    //m_shape.setFillColor(color);
}

void Boid::SetPosition(const sf::Vector2f& position) {
    m_position = position;
    //m_shape.setPosition(m_position);
}

void Boid::SetPointer(std::vector<Boid>* pointervector)
{
	m_BoidVectorP = pointervector;
}

//sf::CircleShape Boid::getShape() const {
//    return m_shape;
//}

void Boid::SetMass(float newMass)
{
	m_mass = newMass;
}
