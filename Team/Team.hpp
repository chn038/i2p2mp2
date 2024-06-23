#ifndef __PLAYERHPP__
#define __PLAYERHPP__

#include <allegro5/color.h>
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
    std::vector<std::vector<int>> UpdateDistance(bool isGround);
    Team* opponent;
    void UpdatePath();
public:
    ALLEGRO_COLOR teamColor;
	std::vector<std::vector<int>> groundMap;
    std::vector<std::vector<int>> flyMap;
    int ID;
    int damageOffset;
    int lives;
    int money;
    Engine::Point startPoint;
    Engine::Point endPoint;
    Group* TowerGroup;
    Group* GroundGroup;
    Group* FlyGroup;
    std::vector<int> waveData;
    void Initialize();
    void Update(float deltaTime) override;
    void Hit();
    void addTower(int objx, int objy, int type);
    bool deleteTower(int objx, int objy);
    void SetOpponent(Team *);
    Team* GetOpponent();
    int getCountDown();
    Team(Engine::Point startPoint, Engine::Point endPoint, int ID, ALLEGRO_COLOR teamColor, int initLives = 10, int initMoney = 500);
};

#endif
