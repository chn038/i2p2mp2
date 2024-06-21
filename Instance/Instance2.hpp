#ifndef __INST_2__
#define __INST_2__

#include "Instance/Instance.hpp"

class Instance2 final : public Instance 
{
    void CreateBullet() override;
    void SearchTarget() override;

public:
    Instance2(float x, float y, int team, int damageOffset,
              std::list<std::pair<bool, IObject*>>& GroundTarget,
              std::list<std::pair<bool, IObject*>>& SkyTarget);
};

#endif
