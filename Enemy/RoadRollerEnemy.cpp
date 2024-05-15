#include <string>

#include "RoadRollerEnemy.hpp"

RoadRollerEnemy::RoadRollerEnemy(int x, int y) : Enemy("play/enemy-4.png", x, y, 25, 20, 150, 20) {
	// Use bounding circle to detect collision is for simplicity, pixel-perfect collision can be implemented quite easily,
	// and efficiently if we use AABB collision detection first, and then pixel-perfect collision.
}

