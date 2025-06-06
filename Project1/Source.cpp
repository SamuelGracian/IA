#include <iostream>

#include "Boid.h"
#include "VectorFloat.h"

int main()
{
	Boid boid;
	SeekObjective seek;
	seek.isActive = true;
	seek.target = Vector2f(10.0f, 10.0f);

	return 0;
}