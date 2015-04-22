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

bool GameEntity::Collision(glm::vec3 OtherMinPos, glm::vec3 OtherMaxPos, glm::vec3 OtherPos)
{
	if( ( this->position.x + this->getMax().x > OtherPos.x - OtherMinPos.x) 
		&& (this->position.x - this->getMin().x < OtherPos.x + OtherMaxPos.x) )
	{
		if( ( this->position.y + this->getMax().y > OtherPos.y - OtherMinPos.y) 
			&& (this->position.y - this->getMin().y < OtherPos.y + OtherMaxPos.y) )
		{
			if( ( this->position.z + this->getMax().z > OtherPos.z - OtherMinPos.z) 
				&& (this->position.z - this->getMin().z < OtherPos.z + OtherMaxPos.z) )
			{
				return true;
			}
		}
	}

	return false;
}