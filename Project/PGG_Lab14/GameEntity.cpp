#include "GameEntity.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

void GameEntity::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	UpdateMatrix(position, rotation, scale);

	// Draw the object using the given view (which contains the camera orientation) and projection (which contains information about the camera 'lense')
	Object->Draw(viewMatrix, projMatrix);
}

void GameEntity::AttachMesh(Mesh* mesh)
{
	Object = mesh;
}

void GameEntity::UpdateMatrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 s)
{
	Object->Update(pos, rot, s);
}