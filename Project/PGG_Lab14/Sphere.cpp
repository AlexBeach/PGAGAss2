#include "Sphere.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Sphere::Sphere()
{
	position = glm::vec3(0, -5, -10);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(0.2f, 0.2f, 0.2f);
}

Sphere::~Sphere(void)
{

}

void Sphere::Update(float deltaTs, input* input)
{
	rotation.y += deltaTs * 0.5f;
	while(rotation.y > (3.14159265358979323846 * 2.0))
	{
		rotation.y -= (3.14159265358979323846 * 2.0);
	}

	if(input->isLeftDown()==true) {  position.x--; }
	if(input->isRightDown()==true) {  position.x++; }
	if(input->isUpDown()==true) {  position.y++; }
	if(input->isDownDown()==true) {  position.y--; }
}