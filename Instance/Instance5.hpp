#ifndef __INST_5__
#define __INST_5__

#include "Instance/Instance.hpp"

class Instance5 final : public Instance 
{
    void OnExplode() override;
    void CreateBullet() override;

public:
    Instance5(float x, float y, int team,
              std::list<std::pair<bool, IObject*>>& GroundTarget,
              std::list<std::pair<bool, IObject*>>& SkyTarget);
};

#endif