#include "Cube.h"

#include <iostream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Cube::Cube()
{
	position = glm::vec3(0, 0, 0);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
	offScreen = false;
}

Cube::~Cube(void)
{

}

void Cube::Update(float deltaTs)
{
	//rotation.y += deltaTs * 0.5f;
	//while(rotation.y > (3.14159265358979323846 * 2.0))
	//{
	//	rotation.y -= (3.14159265358979323846 * 2.0);
	//}

	position.z += 1.5f;

	if(position.z > 10)
	{
		offScreen = true;
	}
	else
	{
		offScreen = false;
	}

	UpdateMatrix();
}