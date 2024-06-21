#include "Instance4.hpp"

Instance4::Instance4(float x, float y, int team, int damageOffset,
                     std::list<std::pair<bool, IObject *>> &GroundTarget,
                     std::list<std::pair<bool, IObject *>> &SkyTarget)
:Instance("play/enemy-2.png", x, y, 64*3 + 32, 1, 20, 10, team, false, 0.25, damageOffset, GroundTarget, SkyTarget) {
}

void Instance4::CreateBullet() {
}

void Instance4::SearchTarget() {
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
