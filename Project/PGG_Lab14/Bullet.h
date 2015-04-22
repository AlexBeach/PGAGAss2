#pragma once

#include "GameEntity.h"

class Bullet: public GameEntity
{
public:
	Bullet(void);
	~Bullet(void);

	void Update(float deltaTs);

	inline bool isOffScreen() { return offScreen; }
	void SetPosition(glm::vec3 pos) { position = pos; }

	void setFire(bool fire) { Fire = fire; }
	bool getFire(void) { return Fire; }

private:

	bool offScreen;
	bool Fire;
};