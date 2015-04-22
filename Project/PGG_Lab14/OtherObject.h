#pragma once

#include "GameEntity.h"

class OtherObject: public GameEntity
{
public:
	OtherObject(void);
	~OtherObject(void);

	void Update(float deltaTs);
};