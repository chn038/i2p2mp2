#ifndef __INST_2__
#define __INST_2__

#include "Instance/Instance.hpp"

class Instance2 final : public Instance 
{
    void OnExplode() override;
    void CreateBullet() override;

public:
    Instance2(float x, float y, int team,
              std::list<std::pair<bool, IObject*>>& GroundTarget,
              std::list<std::pair<bool, IObject*>>& SkyTarget);
};

#endif
