#include "Player.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

Player::Player()
{
	position = glm::vec3(0, -2, -5);
	rotation = glm::vec3(0, 0, 0);
	scale = glm::vec3(0.003f, 0.003f, 0.005f);
}

Player::~Player(void)
{

}

void Player::Update(float deltaTs, input* input)
{
	if(position.x >= -5.0f)
	{
		if(input->isLeftDown()==true)
		{
			position.x-=0.1;

			rotation.z += deltaTs * 0.025f;
			while(rotation.z > (3.14159265358979323846 * 2.0))
			{
				rotation.z -= (3.14159265358979323846 * 2.0);
			}
		}
	}

	if(position.x <= 5.0f)
	{
		if(input->isRightDown()==true)
		{
			position.x+=0.1;
			
			rotation.z -= deltaTs * 0.025f;
			while(rotation.z < (3.14159265358979323846 * 2.0))
			{
				rotation.z += (3.14159265358979323846 * 2.0);
			}
		}
	}

	if(position.y >= -2.3f)
	{
		if(input->isDownDown()==true)
		{
			position.y-=0.1;
		}
	}

	if(position.y <= 2.3f)
	{
		if(input->isUpDown()==true)
		{
			position.y+=0.1;
		}
	}
}