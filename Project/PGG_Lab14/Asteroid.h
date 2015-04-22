#pragma once

#include "gameentity.h"

class Asteroid: public GameEntity
{
public:
	Asteroid(void);
	~Asteroid(void);

	void Update(float deltaTs);

	inline bool isOffScreen() { return offScreen; }
	void SetPosition(glm::vec3 pos) { position = pos; }

private:

	bool offScreen;
};
