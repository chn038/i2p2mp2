#ifndef __PLAYERHPP__
#define __PLAYERHPP__

#include "Engine/Group.hpp"
#include "Engine/Point.hpp"

class Player final : public Engine::Group {
public:
    Engine::Point startPoint;
    Engine::Point endPoint;
};

#endif
