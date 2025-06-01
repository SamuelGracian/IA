#pragma once
#include <vector>

#include "VectorFloat.h"

class SeekBehaviours
{
public:

	const void TwoDimensionSeeK(const std::vector<float>& PlayerPos,
        const std::vector<float>& EnemyPosition,
        std::vector<float>& Direction,
        float SF);

private:
	
};

