#ifndef __INST_1__
#define __INST_1__

#include "Instance/Instance.hpp"

class Instance1 final : public Instance 
{
    void CreateBullet() override;
    void SearchTarget() override;

public:
    Instance1(float x, float y, int team, int damageOffset,
              std::list<std::pair<bool, IObject *>> &GroundTarget,
              std::list<std::pair<bool, IObject *>> &SkyTarget);
};

#endif
