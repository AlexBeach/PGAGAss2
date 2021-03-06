#include "Mesh.h"
#include <iostream>
#include <fstream>
#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

/// Check to see if the shader has compiled
bool checkShaderCompiled( GLint shader )
{
	GLint compiled;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &compiled );
	if ( !compiled )
	{
		GLsizei len;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &len );

		// OpenGL will store an error message as a string that we can retrieve and print
		GLchar* log = new GLchar[len+1];
		glGetShaderInfoLog( shader, len, &len, log );
		std::cerr << "ERROR: Shader compilation failed: " << log << std::endl;
		delete [] log;

		return false;
	}
	return true;
}

/// Constructor loads in a mesh file
Mesh::Mesh(std::string objFileName)
{
	// Initialise variables
	VAO = 0;
	shader = 0;

	objLoader.Load(objFileName);

	// Create the model
	InitialiseVAO();
	
	// Create the shaders
	InitialiseShaders();

	BoundingBoxCoords();
}

Mesh::~Mesh()
{
	// TODO: destroy VAO, shaders etc
}

void Mesh::InitialiseVAO()
{
	// Creates one VAO
	glGenVertexArrays( 1, &VAO );
	glBindVertexArray( VAO );
	numVertices = objLoader.GetMeshVertices().size();

	// stores data in the position buffer
	positionBuffer = 0;
	glGenBuffers(1, &positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &objLoader.GetMeshVertices()[0], GL_STATIC_DRAW);
	
	// stores data in the normal buffer
	normalBuffer = 0;
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec3), &objLoader.GetMeshNormals()[0], GL_STATIC_DRAW);
	
	// stores data in the texture Coordinate buffer
	texCoordBuffer = 0;
	glGenBuffers(1, &texCoordBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(glm::vec2), &objLoader.GetMeshTexCoords()[0], GL_STATIC_DRAW);

	// Unbind for neatness, it just makes life easier
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray( 0 );

	// Technically we can do this, because the enabled / disabled state is stored in the VAO
	glDisableVertexAttribArray(0);
}

void Mesh::InitialiseShaders()
{	
	// This is the vertex shader being loaded from file
	std::string VertexShaderCode = ReadFile("Shaders/basicLight.vert");
	
	// This is the fragment shader
	std::string FragShaderCode = ReadFile("Shaders/basicLight.frag");

	// The 'program' stores the shaders
	shader = glCreateProgram();

	// Create the vertex shader
	GLuint vShader = glCreateShader( GL_VERTEX_SHADER );
	// Give GL the source for it
	char const* VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource( vShader, 1, &VertexSourcePointer, NULL );
	// Compile the shader
	glCompileShader( vShader );
	// Check it compiled and give useful output if it didn't work!
	if( !checkShaderCompiled( vShader ) )
	{
		return;
	}
	// This links the shader to the program
	glAttachShader( shader, vShader );

	// Same for the fragment shader
	GLuint fShader = glCreateShader( GL_FRAGMENT_SHADER );
	char const* FragSourcePointer = FragShaderCode.c_str();
	glShaderSource( fShader, 1, &FragSourcePointer, NULL );
	glCompileShader( fShader );
	if( !checkShaderCompiled( fShader ) )
	{
		return ;
	}
	glAttachShader( shader, fShader );

	// This makes sure the vertex and fragment shaders connect together
	glLinkProgram( shader );
	// Check this worked
	GLint linked;
	glGetProgramiv( shader, GL_LINK_STATUS, &linked );
	if ( !linked )
	{
		GLsizei len;
		glGetProgramiv( shader, GL_INFO_LOG_LENGTH, &len );

		GLchar* log = new GLchar[len+1];
		glGetProgramInfoLog( shader, len, &len, log );
		std::cerr << "ERROR: Shader linking failed: " << log << std::endl;
		delete [] log;

		return;
	}
	
	// We need to setup our ID so they can work with our shaders
	MatrixID = glGetUniformLocation(shader, "MVP");
	ViewMatrixID = glGetUniformLocation(shader, "V");
	ModelMatrixID = glGetUniformLocation(shader, "M");

}

void Mesh::Update(glm::vec3 position, glm::vec3 rotation, glm::vec3 scale)
{
	modelMatrix = glm::translate(glm::mat4(1.0f), position);
	modelMatrix = glm::scale(modelMatrix, scale);
	modelMatrix = glm::rotate(modelMatrix, rotation.x, glm::vec3(1,0,0));
	modelMatrix = glm::rotate(modelMatrix, rotation.y, glm::vec3(0,1,0));
	modelMatrix = glm::rotate(modelMatrix, rotation.z, glm::vec3(0,0,1));
}

void Mesh::Draw(glm::mat4& viewMatrix, glm::mat4& projMatrix, glm::vec3 light)
{
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);

	// Activate the shader program
	glUseProgram( shader );

		// Activate the VAO
		glBindVertexArray( VAO );

			
			glm::mat4 MVP = projMatrix * viewMatrix * modelMatrix;

			// Send our transformation to the currently bound shader, 
			// in the "MVP" uniform
			glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
			glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &modelMatrix[0][0]);
			glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &viewMatrix[0][0]);
			
			GLuint LightID = glGetUniformLocation(shader, "LightPosition_worldspace");
			glUniform3f(LightID, light.x, light.y, light.z);

			//send the diffuse texture to the shader
			int diffuseSampler = glGetUniformLocation(shader, "texSampler");
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, diffuseTexID);
			glUniform1i(diffuseSampler, 0);

			//vertex position data read in from obj file
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			//vertex normal data read in from obj file
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

			//vertex texture coordinate data read in from obj file
			glEnableVertexAttribArray(2);
			glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

			// Tell OpenGL to draw it
			// Must specify the type of geometry to draw and the number of vertices
			glDrawArrays(GL_TRIANGLES, 0, numVertices);

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
			glDisableVertexAttribArray(2);

		// Unbind VAO
		glBindVertexArray( 0 );
	
	// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
	glUseProgram( 0 );
}

void Mesh::LoadTexture(const char* filename)
{	
	// load bmp through SDL
	SDL_Surface* image = SDL_LoadBMP(filename);
	
	// check if it has loaded
	if (!image)
	{
		std::cout << "FAILED : Cannot open file:"  << std::endl;
		return;
	}

	std::cout << "SUCCESS : Texture loaded" << std::endl;
	
	// use the SDL imported data to generate a texture through glew
	glGenTextures(1, &diffuseTexID);
	glBindTexture(GL_TEXTURE_2D, diffuseTexID);

	// BMP files are loaded in with the colour channels backwards, so we need to process it as a BGR instead of RGB
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_BGR, GL_UNSIGNED_BYTE, image->pixels);

	// OpenGL now has our image data, so we can free the loaded image
	SDL_FreeSurface(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST); 
}

std::string Mesh::ReadFile(std::string fileName) {
	
	std::string result;

	std::ifstream stream(fileName, std::ios::in);
	if (stream.is_open()){
		std::string Line = "";
		while (getline(stream, Line))
			result += "\n" + Line;
		stream.close();
	}

	return result;
}

void Mesh::BoundingBoxCoords(void)
{
	for(int i=0; i<numVertices; i++)
	{
		if(objLoader.GetMeshVertices()[i].x < Min.x)
		{
			Min.x = objLoader.GetMeshVertices()[i].x;
		}
		else if(objLoader.GetMeshVertices()[i].x > Max.x)
		{
			Max.x = objLoader.GetMeshVertices()[i].x;
		}

		if(objLoader.GetMeshVertices()[i].y < Min.y)
		{
			Min.y = objLoader.GetMeshVertices()[i].y;
		}
		else if(objLoader.GetMeshVertices()[i].y > Max.y)
		{
			Max.y = objLoader.GetMeshVertices()[i].y;
		}

		if(objLoader.GetMeshVertices()[i].z < Min.z)
		{
			Min.z = objLoader.GetMeshVertices()[i].z;
		}
		else if(objLoader.GetMeshVertices()[i].z > Max.z)
		{
			Max.z = objLoader.GetMeshVertices()[i].z;
		}
	}
}

glm::vec3 Mesh::getDistance(void)
{
	glm::vec3 d;

	d.x = Max.x - Min.x;
	d.y = Max.y - Min.y;
	d.z = Max.z - Min.z;

	return d;
}