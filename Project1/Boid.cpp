#include "Boid.h"

Vector2f Boid::Seek(const Vector2f& position, const Vector2f& target, float seekforce)
{
	Vector2f force;
	force[0] = 0.0f;
	force[1] = 0.0f;

	Vector2f Desired = (target - position).GetNormalized();

	force = Desired * seekforce;
	return force;
}

const Vector2f Boid::Flee(const Vector2f& position,
		const Vector2f& target, 
		float fleeForce)
{
	Vector2f force;
	force[0] = 0.0f;
	force[1] = 0.0f;
	Vector2f Desired = (position - target).GetNormalized();
	force = Desired * fleeForce;
	return force;

}


void Boid::Wander(float wanderForce)
{
	
}

void Boid::Arrive(const Vector2f& target, float slowRadius)
{
	Vector2f Desired = (target - m_position).GetNormalized();
	float distance = (target - m_position).Length();
	if (distance < slowRadius)
	{
		Desired *= (distance / slowRadius);
	}
	else
	{
		Desired *= 1.0f; // Full speed
	}
	Vector2f force = Desired - m_direction;
	m_direction += force;
	m_direction.Normalize();
	m_position += m_direction;
}

void Boid::Update()
{
	Vector2f force; force[0] = 0; force[1] = 0;

	if (m_seekObjective.isActive)
	{
		Vector2f force = Seek(m_position, m_seekObjective.target, m_seekObjective.seekforce);
	}
	if (m_fleeObjective.isActive)
	{
		force = Flee(m_position, m_fleeObjective.target, m_fleeObjective.fleeForce);
	}
		m_direction += force;
		m_direction.Normalize();
		m_position += m_direction;
		m_shape.setPosition(sf::Vector2f(m_position[0], m_position[1]));
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

void Boid::SetPosition(const Vector2f& position)
{
	m_position = position;
	m_shape.setPosition(sf::Vector2f(m_position[0], m_position[1]));
}

Vector2f Boid::ConvertToVector2f(const sf::Vector2f& vectorsfml)
{
	return { vectorsfml.x, vectorsfml.y };
}

sf::CircleShape Boid::getShape() const 
{
	return m_shape;
}
