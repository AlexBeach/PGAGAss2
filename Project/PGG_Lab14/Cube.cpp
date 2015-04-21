#include "Cube.h"

#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Cube::Cube()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(0.2f, 0.2f, 0.2f);
	offScreen = false;
}

Cube::~Cube(void)
{

}

void Cube::Update(float deltaTs)
{
	position.z += 2.0f;

	if(position.z > 10)
	{
		offScreen = true;
	}
	else
	{
		offScreen = false;
	}
}