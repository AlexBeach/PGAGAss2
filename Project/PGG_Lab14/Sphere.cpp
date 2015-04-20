#include "Sphere.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Sphere::Sphere()
{
	position = glm::vec3(0, -5, -5);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(1, 1, 1);
}

Sphere::~Sphere(void)
{

}

void Sphere::Update(float deltaTs, input* input)
{
	rotation.y += deltaTs * 0.1f;
	while(rotation.y > (3.14159265358979323846 * 2.0))
	{
		rotation.y -= (3.14159265358979323846 * 2.0);
	}

	UpdateMatrix();
}