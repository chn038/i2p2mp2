#ifndef __INST_3__
#define __INST_3__

#include "Instance/Instance.hpp"

class Instance3 final : public Instance
{
    float targetRotation;
    void CreateBullet() override;
    void SearchTarget() override;

public:
    Instance3(float x, float y, int team, int damageOffset,
              std::list<std::pair<bool, IObject *>> &GroundTarget,
              std::list<std::pair<bool, IObject *>> &SkyTarget);
};

#endif
