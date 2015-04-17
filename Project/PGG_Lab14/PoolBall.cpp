#include "PoolBall.h"

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

PoolBall::PoolBall(std::string filename/*, glm::vec3 Pos*/)
{
	Object = new ObjectLoader(filename);
	position = glm::vec3(5, 0, -20);
}

PoolBall::~PoolBall(void)
{

}

void PoolBall::Update(float deltaTs)
{
	// Update the model, to make it rotate
	// update the rotation angle of our cube
	rotation.y += deltaTs * 0.5f;
	while(rotation.y > (3.14159265358979323846 * 2.0))
	{
		rotation.y -= (3.14159265358979323846 * 2.0);
	}

	// Build the model matrix!
	// First we start with an identity matrix
	// This is created with the command: glm::mat4(1.0f)
	// Next, we translate this matrix according to the object's _position vector:
	modelMatrix = glm::translate(glm::mat4(1.0f), position);
	// Next, we rotate this matrix in the y-axis by the object's y-rotation:
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0,1,0));
	// And there we go, model matrix is ready
	
	Object->setMat(modelMatrix);
}

void PoolBall::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix)
{
	// Draw the object using the given view (which contains the camera orientation) and projection (which contains information about the camera 'lense')
	Object->Draw(viewMatrix, projMatrix);
}