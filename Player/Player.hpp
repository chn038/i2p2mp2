#ifndef __PLAYERHPP__
#define __PLAYERHPP__

#include <vector>
#include "Engine/Group.hpp"

class PlayScene;
class Turret;
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
    std::vector<std::vector<Engine::TileType>>& getMapState();
	std::vector<std::vector<int>> mapDistance;
    int spawnCD;
public:
    static const int instanceTypes = 6;
    static const int spawnPeriod = 10;
    static const int initLives = 10;
    static const int initMoney = 500;
    int damageOffset;
    int lives;
    int money;
    Engine::Point startPoint;
    Engine::Point endPoint;
    Group* TowerGroup;
    Group* InstanceGroup;
    std::vector<int> waveData;
    void Initialize();
    void Terminate();
    void Update(float deltaTime);
    bool Hit();
    void SpawnInstances();
    void addTower(int objx, int objy, int type);
    bool deleteTower(int objx, int objy);
    ~Player();
};

#endif
