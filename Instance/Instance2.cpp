#include "Instance2.hpp"

Instance2::Instance2(float x, float y, int team, int damageOffset,
                     std::list<std::pair<bool, IObject *>> &GroundTarget,
                     std::list<std::pair<bool, IObject *>> &SkyTarget)
:Instance("play/enemy-12.png", x, y, 64*3 + 32, 0.5, 10, 5, team, true, 1, damageOffset, GroundTarget, SkyTarget) {
}

void Instance2::CreateBullet() {
}

void Instance2::SearchTarget() {
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

    if (Target) return;

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
