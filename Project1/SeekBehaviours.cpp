#include "SeekBehaviours.h"


const void SeekBehaviours::TwoDimensionSeeK
    (
        const std::vector<float>& PlayerPos,
        const std::vector<float>& EnemyPosition,
        std::vector<float>& Direction,
        //cambiar nombre seekforce
        float SF
    )
{
    float DistanceX = PlayerPos[0] - EnemyPosition[0];
    float DistanceY = PlayerPos[1] - EnemyPosition[1];


    float Length = sqrt(DistanceX * DistanceX + DistanceY * DistanceY);

    if (Length != 0.0f) {
        Direction[0] = (DistanceX / Length) * SF;
        Direction[1] = (DistanceY / Length) * SF;
    }
    else {
        Direction[0] = 0.0f;
        Direction[1] = 0.0f;
    }
}
