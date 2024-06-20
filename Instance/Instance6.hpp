#ifndef __INST_6__
#define __INST_6__

#include "Instance/Instance.hpp"

class Instance6 final : public Instance 
{
    void OnExplode() override;
    void CreateBullet() override;

public:
    Instance6(float x, float y, int team,
              std::list<std::pair<bool, IObject*>>& GroundTarget,
              std::list<std::pair<bool, IObject*>>& SkyTarget);
};

#endif
