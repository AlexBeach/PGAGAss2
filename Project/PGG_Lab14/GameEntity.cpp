#include "GameEntity.h"

GameEntity::GameEntity(void)
{
	Object = new ObjectLoader("Sphere.obj");
}

GameEntity::~GameEntity(void)
{

}

void GameEntity::Update(glm::vec3 pos, glm::vec3 rot, float deltaTs)
{

}

void GameEntity::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	// Draw the object using the given view (which contains the camera orientation) and projection (which contains information about the camera 'lense')
	Object->Draw(viewMatrix, projMatrix);
}