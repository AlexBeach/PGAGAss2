#include "Asteroid.h"

#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Asteroid::Asteroid()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scaler = 1;
	scale = glm::vec3(scaler, scaler, scaler);
	offScreen = false;
	Speed = (1.0f + rand() % 10)/5;
}

Asteroid::~Asteroid(void)
{

}

void Asteroid::Update(float deltaTs)
{
	rotation.x += deltaTs * 0.2f;
	while(rotation.x > (3.14159265358979323846 * 2.0))
	{
		rotation.x -= (3.14159265358979323846 * 2.0);
	}
	
	position.z += Speed;

	if(position.z > 10)
	{
		offScreen = true;
	}
	else
	{
		offScreen = false;
	}
}