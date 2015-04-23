#include "Bullet.h"

#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Bullet::Bullet(void)
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scaler = 1;
	scale = glm::vec3(scaler, scaler, scaler);
	offScreen = false;
}

Bullet::~Bullet(void)
{

}

void Bullet::Update(float deltaTs)
{
	position.z -= 0.5f;

	if(position.z <= -100)
	{
		offScreen = true;
	}
	else
	{
		offScreen = false;
	}
}