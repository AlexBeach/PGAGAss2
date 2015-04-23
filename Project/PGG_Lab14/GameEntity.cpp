#include "GameEntity.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

void GameEntity::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix, glm::vec3 light)
{
	UpdateMatrix(position, rotation, scale);

	// Draw the object using the given view (which contains the camera orientation) and projection (which contains information about the camera 'lense')
	Object->Draw(viewMatrix, projMatrix, light);
}

void GameEntity::AttachMesh(Mesh* mesh)
{
	Object = mesh;
}

void GameEntity::UpdateMatrix(glm::vec3 pos, glm::vec3 rot, glm::vec3 s)
{
	Object->Update(pos, rot, s);
}

bool GameEntity::Collision(glm::vec3 MinPos, glm::vec3 MaxPos, glm::vec3 Pos, glm::vec3 OtherMinPos, glm::vec3 OtherMaxPos, glm::vec3 OtherPos)
{
	if( ( Pos.x + MaxPos.x > OtherPos.x + OtherMinPos.x) 
		&& (Pos.x + MinPos.x < OtherPos.x + OtherMaxPos.x) )
	{
		if( ( Pos.y + MaxPos.y > OtherPos.y + OtherMinPos.y) 
			&& (Pos.y + MinPos.y < OtherPos.y + OtherMaxPos.y) )
		{
			if( ( Pos.z + MaxPos.z > OtherPos.z + OtherMinPos.z) 
				&& (Pos.z + MinPos.z < OtherPos.z + OtherMaxPos.z) )
			{
				return true;
			}
		}
	}

	return false;
}