#include "OtherObject.h"

OtherObject::OtherObject(void)
{
	position = glm::vec3(0, -30, -400);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(15.0f, 15.0f, 15.0f);
}

OtherObject::~OtherObject(void)
{

}

void OtherObject::Update(float deltaTs)
{

}