#pragma once

#include "GameEntity.h"

class Player: public GameEntity
{
public:
	Player(void);
	~Player(void);

	void Update(float deltaTs, input *input);
};