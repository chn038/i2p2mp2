#ifndef DELETETURRET_HPP
#define DELETETURRET_HPP
#include "Turret.hpp"

class DeleteTurret: public Turret {
public:
    static const int Price;
    DeleteTurret(float x, float y, int damageOffset);
    void CreateBullet() override;
};
#endif //  DELETETURRET_HPP
