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
