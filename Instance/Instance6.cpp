#include "Instance6.hpp"

Instance6::Instance6(float x, float y, int team, int damageOffset,
                     std::list<std::pair<bool, IObject *>> &GroundTarget,
                     std::list<std::pair<bool, IObject *>> &SkyTarget)
:Instance("play/enemy-22.png", x, y, 64*5 + 32, 0.5, 50, 20, team, false, 2, damageOffset, GroundTarget, SkyTarget) {
}

void Instance6::CreateBullet() {
}

void Instance6::SearchTarget() {
    // Lock first seen target.
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    for (auto &it : FlyTarget) {
        Engine::Point diff = it.second->Position - Position;
        if (diff.Magnitude() <= CollisionRadius) {
            Target = dynamic_cast<Instance *>(it.second);
            Target->lockedTowers.push_back(this);
            lockedTowerIterator = std::prev(Target->lockedTowers.end());
            break;
        }
    }
}
