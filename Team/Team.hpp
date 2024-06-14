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

class Team final : public Engine::Group {
    PlayScene* getPlayScene();
    std::vector<std::vector<Engine::TileType>>& getMapState();
	std::vector<std::vector<int>> mapDistance;
    constexpr static const float shiftSec = 0.2;
    int startSpawn;
    float spawnCD;
    void UpdateDistance();
    Team* opponent;
public:
    static const int instanceTypes = 6;
    int damageOffset;
    int lives;
    int money;
    int spawnPeriod;
    Engine::Point startPoint;
    Engine::Point endPoint;
    Group* TowerGroup;
    Group* InstanceGroup;
    std::vector<int> waveData;
    void Initialize();
    void Terminate();
    void Update(float deltaTime) override;
    bool Hit();
    void SpawnInstances(int time);
    void addTower(int objx, int objy, int type);
    bool deleteTower(int objx, int objy);
    Team(Engine::Point startPoint, Engine::Point endPoint, Team* opponent, int initLives = 10, int initMoney = 500, int spawnPeriod = 10);
    ~Team();
};

#endif