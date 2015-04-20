#pragma once

#include "GameEntity.h"

class Sphere: public GameEntity
{
public:
	Sphere(void);
	~Sphere(void);

	/// Currently just updates rotation to make the model rotate
	void Update(float deltaTs, input *input);
};