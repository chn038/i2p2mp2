#ifndef __PLAYERHPP__
#define __PLAYERHPP__

#include "Engine/Group.hpp"

class PlayScene;
namespace Engine {
    class Point;
    enum TileType {
        TILE_DIRT,
        TILE_FLOOR,
        TILE_OCCUPIED,
    };
};

class Player final : public Engine::Group {
    PlayScene* getPlayScene();
public:
    int damageOffset;
    int lives;
    int money;
    Engine::Point startPoint;
    Engine::Point endPoint;
    Group* TowerGroup;
    Group* InstanceGroup;
    int* waveData;
    void Initialize();
    void Terminate();
    void Update(float deltaTime);
    void Hit();
    void SpawnInstances();
};

#endif
