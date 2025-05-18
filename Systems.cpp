#include "Systems.h"

//Systems::Systems() {}

void update_health_regeneration(unsigned int current_frame, Healths& healths)
{
    if(current_frame % 120 == 0)
    {
        for(auto& [id, health] : healths)
        {
            if(health.current < health.max)
                ++health.current;
        }
    }
}
