#ifndef PLAYER_STRUCTS_H
#define PLAYER_STRUCTS_H

#include "Utility/utility.hpp"

class PlayerData {
	public:
    vec2 size;
    vec2 maxVelocity;
    vec2 maxAccel;
    float health;
    int maxJumps;
    float jumpVelocity;
    PlayerData();
		PlayerData(vec2 _size, vec2 _maxVelocity, vec2 _maxAccel, float _health, int maxJumps, float jumpVelocity);
};

#endif
