#include "GameEntity.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

void GameEntity::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	// Draw the object using the given view (which contains the camera orientation) and projection (which contains information about the camera 'lense')
	Object->Draw(viewMatrix, projMatrix);
}

void GameEntity::setPos(glm::vec3 Pos)
{
	position=Pos;
}

glm::vec3 GameEntity::getPos(void)
{
	return position;
}

void GameEntity::AttachMesh(ObjectLoader* mesh)
{
	Object = mesh;
}

void GameEntity::UpdateMatrix(glm::vec3 pos, glm::vec3 rot, float scale)
{
	Object->Update(pos, rot, scale);
}