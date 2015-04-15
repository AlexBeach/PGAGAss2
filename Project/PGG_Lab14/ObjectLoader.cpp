#include "ObjectLoader.h"

#include <iostream>
#include <fstream>

#include <gtc/type_ptr.hpp>
#include <gtc/matrix_transform.hpp>

ObjectLoader::ObjectLoader(std::string filename)
{
	VAO = 0;
	numVertices = 0;

	LoadObject(filename);
	CreateVAO();

	position = glm::vec3(0, -5, -10);

	shader = new Shader();
}

ObjectLoader::~ObjectLoader(void)
{

}

void ObjectLoader::LoadObject(std::string filename)
{
    std::cout << "Loading file: '" << filename << "'" << std::endl;

    std::ifstream file(filename);
   
    // Check if the file is loaded
    if(file == NULL)
    {
            std::cout << "Cannot open file: '" << filename << "'" << std::endl;
            getchar();
            return;
    }

    // vectors to hold the index of the verts, uv and normals
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

    // some temporary vectors to hold the data before we commit it
    std::vector<glm::vec3> tempVertices;
    std::vector<glm::vec2> tempUVs;
    std::vector<glm::vec3> tempNormals;

    // while the file is open, loop through the contents
    while(!file.eof())
    {
            // read the file line by line
            char line[256];
            file.getline(line, 256);

            // if the line begins with a 'v', it is data we can use (vertex, normal or uv)
            if(line[0] == 'v')
            {
                    float a, b, c;

                    // if the next char is 'n', we have a Vertex Normal
                    if(line[1] == 'n')
                    {
                            sscanf(line, "vn %f %f %f", &a, &b, &c);
                            tempNormals.push_back(glm::vec3(a, b, c));     
                    }
                    // if the next char is 't', we have a Vertex Texture
                    else if(line[1] == 't')
                    {
                            sscanf(line, "vt %f %f", &a, &b);
                            tempUVs.push_back(glm::vec2(a, b));
                    }
                    // else we just have the vertex position
                    else
                    {                              
                            sscanf(line, "v %f %f %f", &a, &b, &c);
                            tempVertices.push_back(glm::vec3(a, b, c));
                    }
            }
            // else if the line begins with 'f', it is a face
            else if(line[0] == 'f')
            {
                    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                   
                    // obj have 3 ways to define a face: Vertex/UV/Normal, Vertex//Normal, and Vertex
                    // we need to test for each one

                    // first we test Vertex/UV/Normal
                    int input = sscanf(line, "f %d/%d/%d %d/%d/%d %d/%d/%d", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

                    // if the scan failed (because of unexpected character
                    if (input < 9)
                    {                              
                            // we try the next format: Vertex//Normal
                            input = sscanf(line, "f %d//%d %d//%d %d//%d", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);

                            // in this case there are no UV coords, so we set them to 0
                            uvIndex[0] = 0;
                            uvIndex[1] = 0;
                            uvIndex[2] = 0;
                           
                            // if the scan failed (because of unexpected character
                            if (input < 6)
                            {
                                    // in this case, there are no normals present, so we refuse to load the mesh

                                    std::cout << "Face cannot be read because there are no normals specified, cancelled loading" << std::endl;
                                    return;
                            }
                    }

                    // add the current vertex index to the vector
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                   
                    // add the current yv index to the vector
                    uvIndices.push_back(uvIndex[0]);
                    uvIndices.push_back(uvIndex[1]);
                    uvIndices.push_back(uvIndex[2]);
                   
                    // add the current normal index to the vector
                    normalIndices.push_back(normalIndex[0]);
                    normalIndices.push_back(normalIndex[1]);
                    normalIndices.push_back(normalIndex[2]);
            }
    }
           
    // allocate a piece of memory before for loop to stop multiple calls of the .size() function
    unsigned int arraySize = vertexIndices.size();
    for(unsigned int i = 0; i < arraySize; i++)
    {
            // Now we assign the verts to the actual vector in the order in which the faces tell us
            unsigned int vertexIndex = vertexIndices[i];
            unsigned int uvIndex = uvIndices[i];
            unsigned int normalIndex = normalIndices[i];
           
            // Get the attributes thanks to the index

            // firstly, make sure we aren't missing the vector
            if(vertexIndex > 0)
            {
                    // if the index is greater than 0, because OBJ starts at 1 (c++ starts at 0), we can safely remove 1 to translate the index
                    glm::vec3 vertex = tempVertices[vertexIndex - 1];

                    // and then add the vertex to the vector
                    vertices.push_back(vertex);
            }

            // and do the same for the uvs and normals

            if(uvIndex > 0)
            {
                    glm::vec2 uv = tempUVs[uvIndex - 1];
                    UVs.push_back(uv);
            }

            if(normalIndex > 0)
            {
                    glm::vec3 normal = tempNormals[normalIndex - 1];
                    normals.push_back(normal);     
            }
    }

    // variable to tell OpenGL how many vertices to draw
    numVertices = vertices.size();
}

void ObjectLoader::CreateVAO()
{
	// Creates one VAO
	glGenVertexArrays( 1, &VAO );
	// 'Binding' something makes it the current one we are using
	// This is like activating it, so that subsequent function calls will work on this item
	glBindVertexArray( VAO );
	
	// Variable for storing a VBO
	GLuint positionBuffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &positionBuffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 3, &vertices[0], GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	// (We will look at this properly in the lectures)
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray(0);

		// Variable for storing a VBO
	GLuint normalBuffer = 0;
	// Create a generic 'buffer'
	glGenBuffers(1, &normalBuffer);
	// Tell OpenGL that we want to activate the buffer and that it's a VBO
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	// With this buffer active, we can now send our data to OpenGL
	// We need to tell it how much data to send
	// We can also tell OpenGL how we intend to use this buffer - here we say GL_STATIC_DRAW because we're only writing it once
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * numVertices * 3, &normals[0], GL_STATIC_DRAW);

	// This tells OpenGL how we link the vertex data to the shader
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0 );
	glEnableVertexAttribArray(1);

	// Unbind for neatness, it just makes life easier
	// As a general tip, especially as you're still learning, for each function that needs to do something specific try to return OpenGL in the state you found it in
	// This means you will need to set the states at the beginning of your function and set them back at the end
	// If you don't do this, your function could rely on states being set elsewhere and it's easy to lose track of this as your project grows
	// If you then change the code from elsewhere, your current code could mysteriously stop working properly!
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray( 0 );

	// Technically we can do this, because the enabled / disabled state is stored in the VAO
	//glDisableVertexAttribArray(0);
}

void ObjectLoader::Update(glm::vec3 pos, glm::vec3 rot, float deltaTs)
{

}

void ObjectLoader::Draw(glm::mat4 viewMatrix, glm::mat4 projMatrix /*, Shader *shader */)
{
	// Ok, here I like to indent drawing calls - it's just a personal style, you may not like it and that's fine ;)
	// Generally you will need to be activating and deactivating OpenGL states
	// I just find it visually easier if the activations / deactivations happen at different tab depths
	// This can help when things get more complex

	// Activate the shader program
	glUseProgram( shader->Program() );

		// Activate the VAO
		glBindVertexArray( VAO );

			// Send matrices to the shader as uniforms like this:
		glUniformMatrix4fv( shader->ModelMat(), 1, GL_FALSE, glm::value_ptr(_modelMatrix) );
		glUniformMatrix4fv(shader->ViewMat(), 1, GL_FALSE, glm::value_ptr(viewMatrix) );
		glUniformMatrix4fv(shader->ProjMat(), 1, GL_FALSE, glm::value_ptr(projMatrix) );


			// Tell OpenGL to draw it
			// Must specify the type of geometry to draw and the number of vertices
			glDrawArrays(GL_TRIANGLES, 0, numVertices);
			
		// Unbind VAO
		glBindVertexArray( 0 );
	
	// Technically we can do this, but it makes no real sense because we must always have a valid shader program to draw geometry
	glUseProgram( 0 );
}