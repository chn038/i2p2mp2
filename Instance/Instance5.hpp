#ifndef __INST_5__
#define __INST_5__

#include "Instance/Instance.hpp"

class Instance5 final : public Instance 
{
    void CreateBullet() override;
    void SearchTarget() override;

public:
    Instance5(float x, float y, int team, int damageOffset,
              std::list<std::pair<bool, IObject *>> &FlyTarget,
              std::list<std::pair<bool, IObject *>> &GroundTarget,
              ALLEGRO_COLOR teamColor);
};

#endif
