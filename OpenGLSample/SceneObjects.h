//////////////////////////////////////////////////////////////////////////////////////////////
// Name: SceneObjects.h                                                                     //
// Author: Michael Gagujas                                                                  //
//                                                                                          //
// Description: Transforms and renders different 3D objects for a scene while               //
// applying textures that tile, overlap, and blend. Scene objects are reusable              //
// by passing in global transformation data.                                                //
//////////////////////////////////////////////////////////////////////////////////////////////

#pragma once
#include "MeshCreator.h"
#include "Textures.h"
#include "shader.h"

// GLM Math Header inclusions
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Stores default data for global transformations
struct Transform
{
	glm::mat4 scale = glm::scale(glm::vec3(1.0f, 1.0f, 1.0f));
	glm::mat4 rotation = glm::rotate(glm::radians(0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	glm::mat4 translation = glm::translate(glm::vec3(0.0f, 0.0f, 0.0f));
};

class SceneObjects
{

public:
	void createScene(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData) {
		renderHammer(gMesh, gTexture, lightingShader, transformData);
		renderFireFlower(gMesh, gTexture, lightingShader, transformData);
		renderBucket(gMesh, gTexture, lightingShader, transformData);
		renderDrinkBox(gMesh, gTexture, lightingShader, transformData);
		renderRoom(gMesh, gTexture, lightingShader, transformData);
	}
	// Creates the ball-peen hammer
	void renderHammer(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData);
	// Creates the fire flower souvenir cup
	void renderFireFlower(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData);
	// Creates the popcorn music bucket
	void renderBucket(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData);
	// Creates the Japanese drink box
	void renderDrinkBox(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData);
	// Creates walled fence, ground, and table
	void renderRoom(MeshCreator gMesh, Textures gTexture, Shader lightingShader, Transform transformData);
};

