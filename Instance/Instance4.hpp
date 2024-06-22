#ifndef __INST_4__
#define __INST_4__

#include "Instance/Instance.hpp"

class Instance4 final : public Instance 
{
    void CreateBullet() override;
    void SearchTarget() override;

public:
    Instance4(float x, float y, int team, int damageOffset,
              std::list<std::pair<bool, IObject *>> &FlyTarget,
              std::list<std::pair<bool, IObject *>> &GroundTarget,
              ALLEGRO_COLOR teamColor);
};

#endif
