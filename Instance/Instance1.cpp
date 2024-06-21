#include "Instance1.hpp"

Instance1::Instance1(float x, float y, int team, int damageOffset,
                     std::list<std::pair<bool, IObject *>> &GroundTarget,
                     std::list<std::pair<bool, IObject *>> &SkyTarget)
:Instance("play/enemy-1.png", x, y, 64 + 32, 1.5, 20, 5, team, true, 1, damageOffset, GroundTarget, SkyTarget) {
}

void Instance1::CreateBullet() {
}

void Instance1::SearchTarget() {
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
