#include "Boid.h"

Vector2f Boid::Seek(const Vector2f& position, const Vector3f& target, float seekforce)
{
    Vector2f Force;
    Force[0] = 0.0f;
	Force[1] = 0.0f;

	Vector2f Desired = target - position;

	float Distance = Desired.Length();

	if (Distance > 0.0f)
	{
		Force = (Desired / Distance) * seekforce;
	}

	return Force;
}
