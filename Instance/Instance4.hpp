#ifndef __INST_4__
#define __INST_4__

#include "Instance/Instance.hpp"

class Instance4 final : public Instance 
{
    void OnExplode() override;
    void CreateBullet() override;

public:
    Instance4(float x, float y, int team,
              std::list<std::pair<bool, IObject*>>& GroundTarget,
              std::list<std::pair<bool, IObject*>>& SkyTarget);
};

#endif
