#include "Boid.h"

sf::Vector2f Boid::Seek(const sf::Vector2f& position, const sf::Vector2f& target, float seekforce)
{
	sf::Vector2f force (0,0);

	sf::Vector2f Desired = (target - position).normalized();

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

	sf::Vector2f wanderPosition(rand() % 1280, rand() % 720);

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

	sf::Vector2f NearestPointinLine = vector_A + (vector_B * escalar);

	if (distance < path.radius)
	{
		if ( currentWaypoint < path.waypoints.size() - 1)

			currentWaypoint++;
	}

	sf::Vector2f ForcetoTarget = Seek(position, target, FollowForce);

	sf::Vector2f ForcetoLine = Seek(position, NearestPointinLine, FollowForce);

	sf::Vector2f FinalForce = (ForcetoTarget + ForcetoLine).normalized() * FollowForce;

	return FinalForce;
	
}

void Boid::Update()
{
	//sf::Vector2f force(0, 0);
	m_desired = sf::Vector2f(0, 0);

	if (m_position.x < 0)
	{
		m_position.x = 1280;
	}

	if (m_position.y < 0)
	{
		m_position.y = 720;
	}

	if (m_position.x > 1280)
	{
		m_position.x = 0;
	}

	if (m_position.y > 720)
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
	if (m_desired.length()> 0)
	{
		m_direction += m_desired.normalized() * (1.0f / m_mass);
		m_direction = m_direction.normalized();
		m_position += m_direction * 0.3f;
	}
		m_shape.setPosition(m_position);
}

void Boid::SetSeekObjective(SeekObjective& seek)
{
	m_seekObjective.isActive = seek.isActive;
	m_seekObjective.target = seek.target;
	m_seekObjective.seekforce = seek.seekforce;
}

void Boid::SetFleeObjective(FleeObjective& flee)
{
	m_fleeObjective.isActive = flee.isActive;
	m_fleeObjective.target = flee.target;
	m_fleeObjective.fleeForce = flee.fleeForce;
}


void Boid::SetColor(sf::Color color) {
	m_shape.setFillColor(color);
}

void Boid::SetPosition(const sf::Vector2f& position)
{
	m_position = position;
	m_shape.setPosition(m_position);
}

sf::Vector2f Boid::ConvertToVector2f(const sf::Vector2f& vectorsfml)
{
	return { vectorsfml.x, vectorsfml.y };
}

sf::CircleShape Boid::getShape() const 
{
	return m_shape;
}

void Boid::SetMass(float newMass)
{
	m_mass = newMass;
}
