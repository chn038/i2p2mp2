#include "Instance5.hpp"

Instance5::Instance5(float x, float y, int team, int damageOffset,
                     std::list<std::pair<bool, IObject *>> &GroundTarget,
                     std::list<std::pair<bool, IObject *>> &SkyTarget)
:Instance("play/enemy-5.png", x, y, 64 + 32, 1, 100, 20, team, true, 1, damageOffset, GroundTarget, SkyTarget) {
}

void Instance5::CreateBullet() {
}

void Instance5::SearchTarget() {
    // Lock first seen target.
    // Can be improved by Spatial Hash, Quad Tree, ...
    // However simply loop through all enemies is enough for this program.
    for (auto &it : GroundTarget) {
        Engine::Point diff = it.second->Position - Position;
        if (diff.Magnitude() <= CollisionRadius) {
            Target = dynamic_cast<Instance *>(it.second);
            Target->lockedTowers.push_back(this);
            lockedTowerIterator = std::prev(Target->lockedTowers.end());
            break;
        }
    }
}
