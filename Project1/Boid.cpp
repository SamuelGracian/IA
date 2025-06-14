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
