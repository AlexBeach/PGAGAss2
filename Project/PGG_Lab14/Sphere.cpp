#include "Sphere.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Sphere::Sphere()
{
	position = glm::vec3(0, -2, -10);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(0.4f, 0.4f, 0.4f);
}

Sphere::~Sphere(void)
{

}

void Sphere::Update(float deltaTs, input* input)
{
	rotation.x -= deltaTs * 0.5f;
	while(rotation.x < (3.14159265358979323846 * 2.0))
	{
		rotation.x += (3.14159265358979323846 * 2.0);
	}

	if(input->isLeftDown()==true) {  position.x-=0.1; }
	if(input->isRightDown()==true) {  position.x+=0.1; }
	if(input->isUpDown()==true) {  position.y+=0.1; }
	if(input->isDownDown()==true) {  position.y-=0.1; }
}